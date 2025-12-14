/* ************************************************************************** */
/*                                                                            */
/*   PROGRAMME PÉDAGOGIQUE : COMPRENDRE LES PIPES EN C                        */
/*                                                                            */
/*   Ce programme explique comment exécuter plusieurs commandes reliées       */
/*   par des pipes, comme dans un shell : ls | grep txt | wc -l               */
/*                                                                            */
/*   Compile avec : gcc -Wall -Wextra -Werror pipe.c -o pipe_demo             */
/*   Execute avec : ./pipe_demo                                               */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

/*
** ═══════════════════════════════════════════════════════════════════════════
** PARTIE 1 : COMPRENDRE CE QU'EST UN PIPE
** ═══════════════════════════════════════════════════════════════════════════
**
** Un PIPE (tube) est un mécanisme de communication entre processus.
** 
** Imagine un tuyau d'eau :
**   - Un côté pour ÉCRIRE (verser l'eau)     → pipe[1]
**   - Un côté pour LIRE (récupérer l'eau)    → pipe[0]
**
**   ┌─────────────────────────────────────────────────────┐
**   │                                                     │
**   │  Processus 1                    Processus 2         │
**   │  (ls)                           (grep)              │
**   │      │                              ▲               │
**   │      │ stdout                 stdin │               │
**   │      ▼                              │               │
**   │   ┌──────────────────────────────┐  │               │
**   │   │     PIPE (tuyau)             │  │               │
**   │   │                              │  │               │
**   │   │  [1] ÉCRITURE ───► [0] LECTURE                  │
**   │   │                              │                  │
**   │   └──────────────────────────────┘                  │
**   │                                                     │
**   └─────────────────────────────────────────────────────┘
**
** Quand on fait "ls | grep txt" :
**   1. ls écrit dans pipe[1] (au lieu de l'écran)
**   2. grep lit depuis pipe[0] (au lieu du clavier)
**
*/

/*
** ═══════════════════════════════════════════════════════════════════════════
** PARTIE 2 : STRUCTURE POUR STOCKER UNE COMMANDE
** ═══════════════════════════════════════════════════════════════════════════
*/

/* 
** Structure représentant une commande à exécuter
** Exemple : "ls -la /home" 
**   → cmd = "/bin/ls"
**   → args = ["ls", "-la", "/home", NULL]
*/
typedef struct s_command
{
	char	*cmd;		/* Chemin complet de la commande (ex: /bin/ls) */
	char	**args;		/* Arguments [nom_cmd, arg1, arg2, ..., NULL] */
}	t_command;

/*
** ═══════════════════════════════════════════════════════════════════════════
** PARTIE 3 : FONCTIONS UTILITAIRES
** ═══════════════════════════════════════════════════════════════════════════
*/

/*
** Affiche un message d'erreur et quitte le programme
*/
void	error_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

/*
** Ferme un file descriptor et vérifie les erreurs
** ⚠️ IMPORTANT : Toujours fermer les fd inutilisés pour éviter les blocages !
*/
void	close_fd(int fd)
{
	if (close(fd) == -1)
		error_exit("close");
}

/*
** ═══════════════════════════════════════════════════════════════════════════
** PARTIE 4 : EXÉCUTER UNE SEULE COMMANDE (rappel)
** ═══════════════════════════════════════════════════════════════════════════
**
** Avant de gérer les pipes, rappelons comment exécuter UNE commande :
**
**   1. fork()   → Créer un processus enfant
**   2. execve() → L'enfant devient la commande (dans l'enfant)
**   3. wait()   → Le parent attend la fin de l'enfant
**
**   ┌─────────────────────────────────────────┐
**   │  Parent (shell)                         │
**   │      │                                  │
**   │      │ fork()                           │
**   │      ├──────────────┐                   │
**   │      │              │                   │
**   │      ▼              ▼                   │
**   │   Parent         Enfant                 │
**   │   (attend)       │                      │
**   │      │           │ execve("ls")         │
**   │      │           ▼                      │
**   │      │        ls s'exécute              │
**   │      │           │                      │
**   │      │           ▼                      │
**   │      │        ls termine                │
**   │      │◄──────────┘                      │
**   │      │                                  │
**   │   Continue...                           │
**   └─────────────────────────────────────────┘
*/

/*
** ═══════════════════════════════════════════════════════════════════════════
** PARTIE 5 : EXÉCUTER DEUX COMMANDES AVEC UN PIPE
** ═══════════════════════════════════════════════════════════════════════════
**
** Pour "cmd1 | cmd2" :
**
**   1. Créer un pipe
**   2. fork() pour cmd1
**      → L'enfant redirige stdout vers pipe[1]
**      → L'enfant exécute cmd1
**   3. fork() pour cmd2
**      → L'enfant redirige stdin depuis pipe[0]
**      → L'enfant exécute cmd2
**   4. Parent ferme le pipe et attend les deux enfants
**
**   ┌────────────────────────────────────────────────────────────────┐
**   │                                                                │
**   │  ┌──────────┐         PIPE           ┌──────────┐              │
**   │  │  cmd1    │    ┌───────────┐       │  cmd2    │              │
**   │  │  (ls)    │    │           │       │  (grep)  │              │
**   │  │          │    │ [1]   [0] │       │          │              │
**   │  │  stdout ─┼───►│  W     R  │──────►┼─ stdin   │              │
**   │  │          │    │           │       │          │              │
**   │  └──────────┘    └───────────┘       └──────────┘              │
**   │                                                                │
**   │  ls écrit dans le pipe, grep lit depuis le pipe                │
**   │                                                                │
**   └────────────────────────────────────────────────────────────────┘
*/

/*
** Exécute deux commandes reliées par un pipe : cmd1 | cmd2
** Exemple : execute_two_cmds("ls", "grep txt")
*/
void	execute_two_cmds(t_command cmd1, t_command cmd2, char **envp)
{
	int		pipefd[2];	/* [0] = lecture, [1] = écriture */
	pid_t	pid1;
	pid_t	pid2;

	/* 
	** ÉTAPE 1 : Créer le pipe
	** pipe() remplit pipefd avec deux file descriptors connectés
	*/
	printf("📍 Création du pipe...\n");
	if (pipe(pipefd) == -1)
		error_exit("pipe");
	printf("   ✓ pipe[0] (lecture) = fd %d\n", pipefd[0]);
	printf("   ✓ pipe[1] (écriture) = fd %d\n", pipefd[1]);

	/*
	** ÉTAPE 2 : Fork pour la première commande (cmd1)
	*/
	printf("\n📍 Fork pour cmd1 (%s)...\n", cmd1.args[0]);
	pid1 = fork();
	if (pid1 == -1)
		error_exit("fork");

	if (pid1 == 0)
	{
		/* ══════════════════════════════════════════════════════════════
		** 👶 ENFANT 1 : Exécute cmd1
		** ══════════════════════════════════════════════════════════════
		** On veut que la SORTIE de cmd1 aille dans le pipe
		** Donc on redirige stdout (fd 1) vers pipe[1] (écriture)
		*/
		printf("   [Enfant 1] Je vais exécuter : %s\n", cmd1.args[0]);
		
		/* Fermer le côté lecture du pipe (on n'en a pas besoin) */
		close_fd(pipefd[0]);
		
		/* 
		** Rediriger stdout vers le pipe
		** dup2(pipefd[1], STDOUT_FILENO) signifie :
		** "Quand j'écris sur stdout, ça va dans pipefd[1]"
		*/
		printf("   [Enfant 1] Redirection stdout → pipe[1]\n");
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			error_exit("dup2");
		
		/* Fermer l'ancien fd (maintenant dupliqué) */
		close_fd(pipefd[1]);
		
		/* Exécuter la commande */
		printf("   [Enfant 1] execve(%s)...\n", cmd1.cmd);
		execve(cmd1.cmd, cmd1.args, envp);
		error_exit("execve cmd1");  /* Si on arrive ici, c'est une erreur */
	}

	/*
	** ÉTAPE 3 : Fork pour la deuxième commande (cmd2)
	*/
	printf("\n📍 Fork pour cmd2 (%s)...\n", cmd2.args[0]);
	pid2 = fork();
	if (pid2 == -1)
		error_exit("fork");

	if (pid2 == 0)
	{
		/* ══════════════════════════════════════════════════════════════
		** 👶 ENFANT 2 : Exécute cmd2
		** ══════════════════════════════════════════════════════════════
		** On veut que l'ENTRÉE de cmd2 vienne du pipe
		** Donc on redirige stdin (fd 0) depuis pipe[0] (lecture)
		*/
		printf("   [Enfant 2] Je vais exécuter : %s\n", cmd2.args[0]);
		
		/* Fermer le côté écriture du pipe (on n'en a pas besoin) */
		close_fd(pipefd[1]);
		
		/* 
		** Rediriger stdin depuis le pipe
		** dup2(pipefd[0], STDIN_FILENO) signifie :
		** "Quand je lis depuis stdin, ça vient de pipefd[0]"
		*/
		printf("   [Enfant 2] Redirection stdin ← pipe[0]\n");
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			error_exit("dup2");
		
		/* Fermer l'ancien fd (maintenant dupliqué) */
		close_fd(pipefd[0]);
		
		/* Exécuter la commande */
		printf("   [Enfant 2] execve(%s)...\n", cmd2.cmd);
		execve(cmd2.cmd, cmd2.args, envp);
		error_exit("execve cmd2");  /* Si on arrive ici, c'est une erreur */
	}

	/* ══════════════════════════════════════════════════════════════════
	** 👨 PARENT : Ferme le pipe et attend les enfants
	** ══════════════════════════════════════════════════════════════════
	** 
	** ⚠️ TRÈS IMPORTANT : Le parent DOIT fermer les deux côtés du pipe !
	** Sinon cmd2 attendra indéfiniment (le pipe ne sera jamais "fermé")
	*/
	printf("\n📍 [Parent] Fermeture du pipe...\n");
	close_fd(pipefd[0]);
	close_fd(pipefd[1]);

	/* Attendre les deux enfants */
	printf("📍 [Parent] Attente des enfants...\n");
	waitpid(pid1, NULL, 0);
	printf("   ✓ Enfant 1 terminé\n");
	waitpid(pid2, NULL, 0);
	printf("   ✓ Enfant 2 terminé\n");
}

/*
** ═══════════════════════════════════════════════════════════════════════════
** PARTIE 6 : EXÉCUTER N COMMANDES AVEC N-1 PIPES (VERSION GÉNÉRALE)
** ═══════════════════════════════════════════════════════════════════════════
**
** Pour "cmd1 | cmd2 | cmd3 | ... | cmdN" :
**
** On a besoin de N-1 pipes pour N commandes
**
**   ┌───────┐    PIPE 0    ┌───────┐    PIPE 1    ┌───────┐
**   │ cmd1  │───────────►│ cmd2  │───────────►│ cmd3  │
**   └───────┘             └───────┘             └───────┘
**          stdout→[1]  [0]→stdin
**                      stdout→[1]  [0]→stdin
**
** L'astuce : Chaque commande (sauf la première) lit depuis le pipe précédent
**            Chaque commande (sauf la dernière) écrit dans le pipe suivant
**
** Pour éviter de stocker tous les pipes, on peut n'en utiliser que 2 à la fois
** et passer l'entrée de l'un à l'autre.
*/

/*
** Exécute une chaîne de N commandes reliées par des pipes
** commands = tableau de commandes
** nb_cmds = nombre de commandes
*/
void	execute_pipeline(t_command *commands, int nb_cmds, char **envp)
{
	int		pipefd[2];		/* Pipe actuel */
	int		prev_pipe_read;	/* fd de lecture du pipe précédent */
	pid_t	pid;
	int		i;

	prev_pipe_read = -1;  /* Pas de pipe précédent pour la première commande */
	i = 0;

	printf("\n");
	printf("══════════════════════════════════════════════════════════════\n");
	printf("  EXÉCUTION DU PIPELINE : %d commandes\n", nb_cmds);
	printf("══════════════════════════════════════════════════════════════\n");

	while (i < nb_cmds)
	{
		printf("\n┌─────────────────────────────────────────────────────────┐\n");
		printf("│ Commande %d/%d : %s\n", i + 1, nb_cmds, commands[i].args[0]);
		printf("└─────────────────────────────────────────────────────────┘\n");

		/*
		** Créer un pipe SAUF pour la dernière commande
		** (la dernière commande écrit sur le vrai stdout)
		*/
		if (i < nb_cmds - 1)
		{
			printf("   📍 Création du pipe %d...\n", i);
			if (pipe(pipefd) == -1)
				error_exit("pipe");
			printf("      pipe[0]=%d (lecture), pipe[1]=%d (écriture)\n", 
				   pipefd[0], pipefd[1]);
		}

		/* Fork pour exécuter cette commande */
		pid = fork();
		if (pid == -1)
			error_exit("fork");

		if (pid == 0)
		{
			/* ═══════════════════════════════════════════════════════════
			** 👶 ENFANT : Configuration des redirections
			** ═══════════════════════════════════════════════════════════
			*/
			
			/*
			** Si ce n'est PAS la première commande :
			** → Rediriger stdin depuis le pipe précédent
			*/
			if (prev_pipe_read != -1)
			{
				printf("   [Enfant %d] stdin ← pipe précédent (fd %d)\n", 
					   i + 1, prev_pipe_read);
				if (dup2(prev_pipe_read, STDIN_FILENO) == -1)
					error_exit("dup2 stdin");
				close_fd(prev_pipe_read);
			}

			/*
			** Si ce n'est PAS la dernière commande :
			** → Rediriger stdout vers le pipe actuel
			*/
			if (i < nb_cmds - 1)
			{
				printf("   [Enfant %d] stdout → pipe actuel (fd %d)\n", 
					   i + 1, pipefd[1]);
				close_fd(pipefd[0]);  /* Fermer lecture (pas utilisé) */
				if (dup2(pipefd[1], STDOUT_FILENO) == -1)
					error_exit("dup2 stdout");
				close_fd(pipefd[1]);
			}

			/* Exécuter la commande */
			printf("   [Enfant %d] execve(%s)\n", i + 1, commands[i].cmd);
			execve(commands[i].cmd, commands[i].args, envp);
			error_exit("execve");
		}

		/* ═══════════════════════════════════════════════════════════════
		** 👨 PARENT : Préparer pour la prochaine itération
		** ═══════════════════════════════════════════════════════════════
		*/
		
		/* Fermer le pipe précédent (plus besoin) */
		if (prev_pipe_read != -1)
		{
			printf("   [Parent] Fermeture ancien pipe lecture (fd %d)\n", 
				   prev_pipe_read);
			close_fd(prev_pipe_read);
		}

		/* 
		** Si on a créé un nouveau pipe :
		** - Fermer le côté écriture (le parent n'écrit pas)
		** - Sauvegarder le côté lecture pour la prochaine commande
		*/
		if (i < nb_cmds - 1)
		{
			printf("   [Parent] Fermeture pipe écriture (fd %d)\n", pipefd[1]);
			close_fd(pipefd[1]);
			prev_pipe_read = pipefd[0];  /* Garder pour la prochaine commande */
			printf("   [Parent] Sauvegarde pipe lecture (fd %d) pour cmd suivante\n", 
				   prev_pipe_read);
		}

		i++;
	}

	/* Attendre tous les enfants */
	printf("\n📍 [Parent] Attente de tous les enfants...\n");
	i = 0;
	while (i < nb_cmds)
	{
		wait(NULL);
		printf("   ✓ Un enfant terminé\n");
		i++;
	}
	printf("\n✅ Pipeline terminé !\n\n");
}

/*
** ═══════════════════════════════════════════════════════════════════════════
** PARTIE 7 : PROGRAMME PRINCIPAL - DÉMONSTRATION
** ═══════════════════════════════════════════════════════════════════════════
*/

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	printf("\n");
	printf("╔══════════════════════════════════════════════════════════════╗\n");
	printf("║     DÉMONSTRATION : EXÉCUTION DE COMMANDES AVEC PIPES        ║\n");
	printf("╚══════════════════════════════════════════════════════════════╝\n");

	/* ═══════════════════════════════════════════════════════════════════
	** DÉMO 1 : Deux commandes avec un pipe
	** Équivalent de : ls -la | grep ".c"
	** ═══════════════════════════════════════════════════════════════════
	*/
	printf("\n");
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("┃ DÉMO 1 : ls -la | grep \".c\"                                 ┃\n");
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	
	t_command cmd1;
	t_command cmd2;
	
	cmd1.cmd = "/bin/ls";
	cmd1.args = (char *[]){"/bin/ls", "-la", NULL};
	
	cmd2.cmd = "/bin/grep";
	cmd2.args = (char *[]){"/bin/grep", ".c", NULL};
	
	execute_two_cmds(cmd1, cmd2, envp);

	/* ═══════════════════════════════════════════════════════════════════
	** DÉMO 2 : Trois commandes avec deux pipes
	** Équivalent de : ls -la | grep ".c" | wc -l
	** ═══════════════════════════════════════════════════════════════════
	*/
	printf("\n");
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("┃ DÉMO 2 : ls | grep \".c\" | wc -l                             ┃\n");
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");

	t_command commands[3];
	
	commands[0].cmd = "/bin/ls";
	commands[0].args = (char *[]){"/bin/ls", NULL};
	
	commands[1].cmd = "/bin/grep";
	commands[1].args = (char *[]){"/bin/grep", ".c", NULL};
	
	commands[2].cmd = "/usr/bin/wc";
	commands[2].args = (char *[]){"/usr/bin/wc", "-l", NULL};
	
	execute_pipeline(commands, 3, envp);

	/* ═══════════════════════════════════════════════════════════════════
	** DÉMO 3 : Quatre commandes
	** Équivalent de : cat /etc/passwd | grep "root" | head -1 | wc -c
	** ═══════════════════════════════════════════════════════════════════
	*/
	printf("\n");
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("┃ DÉMO 3 : cat /etc/passwd | grep root | head -1 | wc -c      ┃\n");
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");

	t_command commands2[4];
	
	commands2[0].cmd = "/bin/cat";
	commands2[0].args = (char *[]){"/bin/cat", "/etc/passwd", NULL};
	
	commands2[1].cmd = "/bin/grep";
	commands2[1].args = (char *[]){"/bin/grep", "root", NULL};
	
	commands2[2].cmd = "/usr/bin/head";
	commands2[2].args = (char *[]){"/usr/bin/head", "-1", NULL};
	
	commands2[3].cmd = "/usr/bin/wc";
	commands2[3].args = (char *[]){"/usr/bin/wc", "-c", NULL};
	
	execute_pipeline(commands2, 4, envp);

	printf("\n");
	printf("╔══════════════════════════════════════════════════════════════╗\n");
	printf("║                    FIN DE LA DÉMONSTRATION                   ║\n");
	printf("╚══════════════════════════════════════════════════════════════╝\n");
	printf("\n");

	return (0);
}

/*
** ═══════════════════════════════════════════════════════════════════════════
** RÉSUMÉ - CE QU'IL FAUT RETENIR
** ═══════════════════════════════════════════════════════════════════════════
**
** 1️⃣  Un PIPE a deux extrémités : 
**     - pipe[0] pour LIRE
**     - pipe[1] pour ÉCRIRE
**
** 2️⃣  Pour rediriger stdout vers un pipe :
**     dup2(pipefd[1], STDOUT_FILENO);
**
** 3️⃣  Pour rediriger stdin depuis un pipe :
**     dup2(pipefd[0], STDIN_FILENO);
**
** 4️⃣  TOUJOURS fermer les fd inutilisés !
**     - L'enfant qui écrit ferme pipefd[0]
**     - L'enfant qui lit ferme pipefd[1]
**     - Le parent ferme LES DEUX côtés
**
** 5️⃣  Pour N commandes, on a besoin de N-1 pipes
**
** 6️⃣  Ordre des opérations :
**     1. pipe()           → Créer le pipe
**     2. fork()           → Créer l'enfant
**     3. dup2()           → Rediriger (dans l'enfant)
**     4. close()          → Fermer les fd inutiles
**     5. execve()         → Exécuter la commande
**     6. wait()/waitpid() → Le parent attend
**
** ⚠️  ERREURS COURANTES :
**     - Oublier de fermer un fd → Le programme bloque
**     - Fermer un fd trop tôt → Perte de données
**     - Ne pas attendre les enfants → Processus zombies
**
** ═══════════════════════════════════════════════════════════════════════════
*/
