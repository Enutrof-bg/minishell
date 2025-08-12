/* ************************************************************************** */
/*                                                                            */
/*		                                                  :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07														  */
/*   Updated: 2025/07/18 11:38:32 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_sigvaleur;

// int ft_close_fd(t_all **all)
// {
// 	int i;

// 	i = 0;
// 	while (i < (*all)->t_cmd->nbr_cmd)
// 	{
// 		if ((*all)->t_cmd->cmd_tab[i].infd != -1)
// 			close((*all)->t_cmd->cmd_tab[i].infd);
// 		if ((*all)->t_cmd->cmd_tab[i].outfd != -1)
// 			close((*all)->t_cmd->cmd_tab[i].outfd);
// 		i++;
// 	}
// 	// if (access("temp", F_OK) == 0)
// 	// {
// 		// unlink("temp");
// 	// }
// 	return (0);
// }

//execute les commandes 
int ft_exec_commande(t_commande *t_cmd, t_redir *t_red, t_all **all, char **env)
{
	int i;
	(void)t_red;
	(void)all;
	i = 0;
	while (i < t_cmd->nbr_cmd)
	{
		// Vérifier si la commande existe et a des arguments
		if (!t_cmd->cmd_tab[i].cmd_args || !t_cmd->cmd_tab[i].cmd_args[0])
		{
			t_cmd->cmd_tab[i].id1 = -1;
			i++;
			continue;
		}
		
		// Vérifier si la commande a des redirections d'entrée qui ont échoué
		if (t_cmd->cmd_tab[i].input_failed == 1 || t_cmd->cmd_tab[i].output_failed == 1)
		{
			// if (t_cmd->cmd_tab[i].input_failed == 1)
			// {
			// 	perror(t_cmd->cmd_tab[i].in_str);
			// }
			// if (t_cmd->cmd_tab[i].output_failed == 1)
			// {
			// 	perror(t_cmd->cmd_tab[i].out_str);
			// 	// ft_err(t_cmd->cmd_tab[i].out_str, "Permission denied");
			// }
			// Ne pas exécuter la commande si redirection d'entrée a échoué
			t_cmd->cmd_tab[i].id1 = -1; // Marquer comme non créé
			i++;
			continue ;
		}

		//condition pour verifier uniquement si les builtin existent
		//puis dup2
		//puis executer les fonctions
		if (ft_strcmp(t_cmd->cmd_tab[i].cmd_args[0], "echo") == 0
			|| ft_strcmp(t_cmd->cmd_tab[i].cmd_args[0], "pwd") == 0
			|| ft_strcmp(t_cmd->cmd_tab[i].cmd_args[0], "env") == 0
			|| (ft_strcmp(t_cmd->cmd_tab[i].cmd_args[0], "export") == 0 &&  t_cmd->nbr_cmd > 1)
			|| (ft_strcmp(t_cmd->cmd_tab[i].cmd_args[0], "exit") == 0 && t_cmd->nbr_cmd > 1))
		{

			// printf("builtin\n");
			t_cmd->cmd_tab[i].id1 = fork();
			if (t_cmd->cmd_tab[i].id1 == 0)
			{
				// Restaurer les signaux par défaut pour les processus enfants
				signal(SIGINT, SIG_DFL);   // Comportement par défaut pour SIGINT
				signal(SIGQUIT, SIG_DFL);  // Comportement par défaut pour SIGQUIT
				
				if (t_cmd->cmd_tab[i].infd >= 0)
					dup2(t_cmd->cmd_tab[i].infd, 0);
				else if (i > 0)  // Si pas de redirection d'entrée, utiliser le pipe précédent
					dup2(t_cmd->cmd_tab[i - 1].fd[0], 0);
				
				// Gestion des redirections de sortie pour toutes les commandes
				if (t_cmd->cmd_tab[i].outfd >= 0)
				{
					// printf("redirection sortie pour commande %d\n", i);
					dup2(t_cmd->cmd_tab[i].outfd, 1);
				}
				else if (i < t_cmd->nbr_cmd - 1)  // Si pas de redirection de sortie, utiliser le pipe suivant
					dup2(t_cmd->cmd_tab[i].fd[1], 1);
				// Sinon, la sortie reste stdout (cas de la dernière commande sans redirection)
				
				ft_close_pipe(t_cmd);
				ft_close_fd(all);
				if (is_builtin_3(t_cmd->cmd_tab[i].cmd_args, all) == 1)
				{
					// (*all)->exit_status = 0;
				}
				// else
				// {
				// 	(*all)->exit_status = 1;
				// }
				// ft_close_pipe(t_cmd);
				t_cmd->cmd_tab[i].id1 = -1; // Les builtins n'ont pas de processus fils
				int temp_exit_status = (*all)->exit_status;
				if (ft_strncmp(t_cmd->cmd_tab[i].cmd_args[0], "exit", 4) == 0)
				{
					temp_exit_status = ft_atoi(t_cmd->cmd_tab[i].cmd_args[1]) % 256;
				}
				// ft_free_double_tab((*all)->env);
				// free(all);
				exit(temp_exit_status);
			}
		}
		else if (
			ft_strcmp(t_cmd->cmd_tab[i].cmd_args[0], "export") == 0
			|| ft_strcmp(t_cmd->cmd_tab[i].cmd_args[0], "unset") == 0
			|| ft_strcmp(t_cmd->cmd_tab[i].cmd_args[0], "cd") == 0
			// || ft_strcmp(t_cmd->cmd_tab[i].cmd_args[0], "pwd") == 0
			// || ft_strcmp(t_cmd->cmd_tab[i].cmd_args[0], "exit") == 0
			// || ft_strcmp(t_cmd->cmd_tab[i].cmd_args[0], "env") == 0
			)
		{
            if (is_builtin_3(t_cmd->cmd_tab[i].cmd_args, all) == 1)
            {
                // printf("je suis la\n");
                // printf("exit1:%d\n", (*all)->exit_status);
                // (*all)->exit_status = homemade_cd(t_cmd->cmd_tab[i].cmd_args, all);
                // printf("exit2:%d\n", (*all)->exit_status);
                t_cmd->cmd_tab[i].id1 = fork();
                if (t_cmd->cmd_tab[i].id1 == 0)
                {
                    // Restaurer les signaux par défaut pour les processus enfants
                    signal(SIGINT, SIG_DFL);   // Comportement par défaut pour SIGINT
                    signal(SIGQUIT, SIG_DFL);  // Comportement par défaut pour SIGQUIT
                    
                    ft_close_pipe(t_cmd);
                    ft_close_fd(all);
                    int temp_exit_status = (*all)->exit_status;
					if (ft_strncmp(t_cmd->cmd_tab[i].cmd_args[0], "exit", 4) == 0)
					{
						temp_exit_status = ft_atoi(t_cmd->cmd_tab[i].cmd_args[1]) % 256;
					}
					// ft_free_double_tab((*all)->env);
					// free(all);
					exit(temp_exit_status);
                }
            }
		}
		else if (ft_strncmp(t_cmd->cmd_tab[i].cmd_args[0], "exit", 4) == 0 && t_cmd->nbr_cmd == 1)
		{
			// ft_exit()
			int temp_exit_status = 0;
			if (!t_cmd->cmd_tab[i].cmd_args[1])
			{
				write(1, "exit\n", 5); //sortie ou 2 
				temp_exit_status = (*all)->exit_status;
				ft_free_all(*all);
				ft_free_double_tab((*all)->env);
				free(*all);
				exit(temp_exit_status);
			}
			if (!ft_is_digit(t_cmd->cmd_tab[i].cmd_args[1])
				|| t_cmd->cmd_tab[i].cmd_args[1][0] == '\0'
				|| (long long)ft_long_atoi(t_cmd->cmd_tab[i].cmd_args[1]) > LLONG_MAX
				|| (long long)ft_long_atoi(t_cmd->cmd_tab[i].cmd_args[1]) < LLONG_MIN)
            {
                write(1, "exit\n", 5); //sortie 1 ou 2 
                ft_err(t_cmd->cmd_tab[i].cmd_args[1], "numeric argument required");
				ft_free_all(*all);
				ft_free_double_tab((*all)->env);
				free(*all);
                exit(2);
            }
			if (t_cmd->cmd_tab[i].cmd_args[2])
			{
				write(1, "exit\n", 5); //sortie 1 ou 2 
				ft_err(t_cmd->cmd_tab[i].cmd_args[1], "too many arguments");
				(*all)->exit_status = 1;
				t_cmd->cmd_tab[i].id1 = fork();
				if (t_cmd->cmd_tab[i].id1 == 0)
				{
					// Restaurer les signaux par défaut pour les processus enfants
					// setup_child_signals();
					
					ft_close_pipe(t_cmd);
					ft_close_fd(all);
					exit(1);
				}
				// return (1);
			}
			if ((*all)->t_cmd->nbr_cmd == 1 && t_cmd->cmd_tab[i].cmd_args[2] == NULL)
			{
				printf("exit\n");
				temp_exit_status = ft_atoi(t_cmd->cmd_tab[i].cmd_args[1]) % 256;
				ft_free_all(*all);
				ft_free_double_tab((*all)->env);
				free(*all);
				exit(temp_exit_status);
			}
				// ft_free_double_tab((*all)->env);
				// free(all);
				
			// return (0);
		}
		else
		{	
			t_cmd->cmd_tab[i].id1 = fork();
			if (t_cmd->cmd_tab[i].id1 == 0)
			{
				 // Restaurer les signaux par défaut pour les processus enfants
               // if  (signal(SIGINT, SIG_DFL))
               // {
               // 	g_sigvaleur = 1;
               // } 
               // 	// Comportement par défaut pour SIGINT
               	signal(SIGINT, SIG_DFL);
                signal(SIGQUIT, SIG_DFL);  // Comportement par défaut pour SIGQUIT
				
				// printf("J'arrive la \n");
				// Gestion des redirections d'entrée pour toutes les commandes
				// printf("infd:%d\n", (*t_cmd).cmd_tab[i].infd);
				if (t_cmd->cmd_tab[i].infd >= 0)
					dup2(t_cmd->cmd_tab[i].infd, 0);
				else if (i > 0)  // Si pas de redirection d'entrée, utiliser le pipe précédent
					dup2(t_cmd->cmd_tab[i - 1].fd[0], 0);
				
				// Gestion des redirections de sortie pour toutes les commandes
				if (t_cmd->cmd_tab[i].outfd >= 0)
				{
					// printf("redirection sortie pour commande %d\n", i);
					dup2(t_cmd->cmd_tab[i].outfd, 1);
				}
				else if (i < t_cmd->nbr_cmd - 1)  // Si pas de redirection de sortie, utiliser le pipe suivant
					dup2(t_cmd->cmd_tab[i].fd[1], 1);
				// Sinon, la sortie reste stdout (cas de la dernière commande sans redirection)
				
				ft_close_pipe(t_cmd);
				ft_close_fd(all);
				if (exec(t_cmd->cmd_tab[i].cmd_args, env) == -1)
					exit(127);
				// ft_close_fd(all);
				exit(0);
			}
			// printf("J'arrive la \n");
			// close((*t_cmd).cmd_tab[i].infd);
			// unlink("temp");
		}
		// printf("J'arrive la \n");
		// close((*t_cmd).cmd_tab[i].infd);
		// unlink("temp");
		i++;
	}
	ft_close_pipe(t_cmd);
	ft_close_fd(all);
	return (0);
}

//pas encore utiliser
//attribue les state CMD ou ARG sur les token
void ft_assign_cmd_arg_states(t_list **lst)
{
	t_list *temp;
	int first_cmd;

	if (!lst || !*lst)
		return;
	temp = *lst;
	first_cmd = 1;
	while (*lst)
	{
		if ((*lst)->state == PIPE)
			first_cmd = 1;
		else if ((*lst)->state == NORMAL || (*lst)->state == DOUBLEQUOTE || (*lst)->state == SINGLEQUOTE)
		{
			if (first_cmd)
			{
				(*lst)->state = CMD;
				first_cmd = 0;
			}
			else
				(*lst)->state = ARG;
		}
		*lst = (*lst)->next;
	}
	*lst = temp;
}

// Chemin par défaut plus complet pour fonctionner même en cas d'utilisation de env -i
char **create_default_env(void)
{
	char **tab = NULL;
	char    *str = NULL;
	char    cwd[PATH_MAX];

	if (!getcwd(cwd, sizeof(cwd)))
		return (NULL);
	str = ft_strjoin("PWD=", cwd);
	if (!str)
		return (NULL);
	tab = ft_add_double_tab(str, tab);
	if (!tab)
		return (free(str), NULL);
	free(str);
	tab = ft_add_double_tab("_=/usr/bin/env", tab);
	if (!tab)
		return (NULL);
	tab = ft_add_double_tab("SHLVL=1", tab);
	if (!tab)
		return (NULL);
	tab = ft_add_double_tab("PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin", tab);
	if (!tab)
		return (NULL);
	return (tab);
}
//caca parsing_test.c pipex_path.c parsing_dollar.c minishell_utils.c ft_strjoin.c ft_split.c ft_itoa.c -lreadline -o minishell
int main(int argc, char **argv, char **env)
{
	(void)argv;
	(void)env;
	t_all *all;

	if (argc == 1)
	{
		all = malloc(sizeof(t_all));
		if (!all)
			return (1);
		
		// Initialiser tous les pointeurs à NULL pour ft_free_all
		all->str = NULL;
		all->shell = NULL;
		all->t_cmd = NULL;
		all->env = NULL;
		all->exit_status_char = NULL;
		all->exit_status = 0;
		
		// Configuration de l'environnement
		if (env[0])
		{
        	all->env = ft_copy_double_tab(env);
        	if (!all->env)
			{
				ft_free_all(all);
				free(all);
				return (1);
			}
			ft_shlvl(&all);
		}
		else
		{
			all->env = create_default_env();
			if (!all->env)
			{
				ft_err("minishell", "malloc failed");
				ft_free_all(all);
				free(all);
				return (1);
			}
		}
		g_sigvaleur = 0;
		set_exit(&(all)->exit_status);

		// Configuration des signaux avec signal() au lieu de sigaction()
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, ft_test);
		
		all->exit_status = 0; // Initialiser l'exit status à 0 au début du programme

		while (1)
		{
			all->shell = NULL;

			if (tcgetattr(STDIN_FILENO, &all->term) == 0)
            {
                all->term.c_lflag |= 0001000; // Désactiver ECHOCTL pour ne pas afficher les caractères de contrôle
                tcsetattr(STDIN_FILENO, TCSANOW, &all->term);
            }

	
			int read_result = ft_read_input(&all);
			if (read_result == -1)
			{
				// ft_free_all(all);
				ft_free_double_tab(all->env);
				int temp = all->exit_status;
				free(all);
				exit(temp);
			}
			else if (read_result == -2)
			{
				// Si c'est à cause d'un signal, mettre à jour l'exit status
				if (g_sigvaleur == 1)
				{
					all->exit_status = 130;  // Code pour SIGINT
					g_sigvaleur = 0;         // Reset après traitement
				}
				continue; // Continue if empty string is detected or signal received
				// return (0); // Continue if empty string is detected
			}

			// if (tcgetattr(STDIN_FILENO, &all->term) == 0)
            // {
            //     all->term.c_lflag |= ECHOCTL;
            //     tcsetattr(STDIN_FILENO, TCSANOW, &all->term);
            // }



			int parse_result = ft_parse(&all);
			if (parse_result == -1)
			{
				continue; // ft_parse a déjà libéré shell et str en cas d'erreur
			}
			else if (parse_result == -2)
				return (ft_free_double_tab(all->env), free(all), 1); // Malloc failure - exit program



			if (ft_open_pipe(all->t_cmd, &all) == 1)
			{
				printf("Erreur lors de la création des pipes\n");
				// Libérer toutes les ressources allouées par ft_parse
				ft_free_all(all);
				continue;
			}

			// Ignorer SIGINT pendant l'exécution des commandes enfants
			signal(SIGINT, SIG_IGN);
			// printf("test1\n");
			ft_exec_commande(all->t_cmd, all->t_red, &all, all->env);
			ft_waitpid(all->t_cmd);
			
			// Restaurer le handler SIGINT après l'exécution
			signal(SIGINT, ft_test);
			
			ft_close_pipe(all->t_cmd);
			ft_check_exit_status(&all);
			// printf("test\n");
			ft_free_all(all);
		}
		ft_free_double_tab(all->env);
		free(all);
	}
	return (0);
}
