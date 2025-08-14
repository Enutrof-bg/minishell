/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 12:38:40 by kevwang           #+#    #+#             */
/*   Updated: 2025/08/14 12:38:42 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sigvaleur;

// // Vérifier si la commande existe et a des arguments
// int	ft_check_arg_empty(t_all *all, int *i)
// {
// 	if (!all->t_cmd->cmd_tab[*i].cmd_args
// 		|| !all->t_cmd->cmd_tab[*i].cmd_args[0])
// 	{
// 		all->t_cmd->cmd_tab[*i].id1 = -1;
// 		(*i)++;
// 		return (1);
// 	}
// 	return (0);
// }

// // Vérifier si la commande a des redirections d'entrée qui ont échoué
// // Ne pas exécuter la commande si redirection d'entrée a échoué
// int	ft_check_input_failed(t_all *all, int *i)
// {
// 	if (all->t_cmd->cmd_tab[*i].input_failed == 1
// 		|| all->t_cmd->cmd_tab[*i].output_failed == 1)
// 	{
// 		all->t_cmd->cmd_tab[*i].id1 = -1;
// 		(*i)++;
// 		return (1);
// 	}
// 	return (0);
// }

// // Restaurer les signaux par défaut pour les processus enfants
// // Comportement par défaut pour SIGINT
// // Comportement par défaut pour SIGQUT
// void	ft_set_signal(void)
// {
// 	signal(SIGINT, SIG_DFL);
// 	signal(SIGQUIT, SIG_DFL);
// }

// Si pas de redirection d'entrée, utiliser le pipe précédent
// Gestion des redirections de sortie pour toutes les commandes
// Si pas de redirection de sortie, utiliser le pipe suivant
// Sinon, la sortie reste stdout (cas de la dernière commande sans redirection)
// int	ft_redirection(t_all *all, int i)
// {
// 	if (all->t_cmd->cmd_tab[i].infd >= 0)
// 		dup2(all->t_cmd->cmd_tab[i].infd, 0);
// 	else if (i > 0)
// 		dup2(all->t_cmd->cmd_tab[i - 1].fd[0], 0);
// 	if (all->t_cmd->cmd_tab[i].outfd >= 0)
// 		dup2(all->t_cmd->cmd_tab[i].outfd, 1);
// 	else if (i < all->t_cmd->nbr_cmd - 1)
// 		dup2(all->t_cmd->cmd_tab[i].fd[1], 1);
// 	return (0);
// }

// int	ft_exit_no_arg(t_all **all)
// {
// 	int	temp_exit_status;

// 	write(1, "exit\n", 5);
// 	temp_exit_status = (*all)->exit_status;
// 	ft_free_all(*all);
// 	ft_free_double_tab((*all)->env);
// 	free(*all);
// 	exit(temp_exit_status);
// }

// int	ft_exit_wrong_arg(t_all **all, int i)
// {
// 	write(1, "exit\n", 5);
// 	ft_err((*all)->t_cmd->cmd_tab[i].cmd_args[1], "numeric argument required");
// 	ft_free_all(*all);
// 	ft_free_double_tab((*all)->env);
// 	free(*all);
// 	exit(2);
// }

// int	ft_exit_two_arg(t_all **all, int i)
// {
// 	write(1, "exit\n", 5);
// 	ft_err((*all)->t_cmd->cmd_tab[i].cmd_args[1], "too many arguments");
// 	(*all)->exit_status = 1;
// 	(*all)->t_cmd->cmd_tab[i].id1 = fork();
// 	if ((*all)->t_cmd->cmd_tab[i].id1 == 0)
// 	{
// 		ft_close_pipe((*all)->t_cmd);
// 		ft_close_fd(all);
// 		exit(1);
// 	}
// 	return (1);
// }

// int	ft_exit_normal(t_all **all, int i)
// {
// 	int	temp_exit_status;

// 	write(1, "exit\n", 5);
// 	temp_exit_status = ft_atoi((*all)->t_cmd->cmd_tab[i].cmd_args[1]) % 256;
// 	ft_free_all(*all);
// 	ft_free_double_tab((*all)->env);
// 	free(*all);
// 	exit(temp_exit_status);
// }

// int	ft_exit_monstre(t_all **all, t_commande *t_cmd, int i)
// {
// 	int	temp_exit_status;

// 	temp_exit_status = 0;
// 	if (!t_cmd->cmd_tab[i].cmd_args[1])
// 		ft_exit_no_arg(all);
// 	if (!ft_is_digit(t_cmd->cmd_tab[i].cmd_args[1])
// 		|| t_cmd->cmd_tab[i].cmd_args[1][0] == '\0'
// 		|| (long long)ft_long_atoi(t_cmd->cmd_tab[i].cmd_args[1]) > LLONG_MAX
// 		|| (long long)ft_long_atoi(t_cmd->cmd_tab[i].cmd_args[1]) < LLONG_MIN)
// 		ft_exit_wrong_arg(all, i);
// 	if (t_cmd->cmd_tab[i].cmd_args[2])
// 		ft_exit_two_arg(all, i);
// 	if ((*all)->t_cmd->nbr_cmd == 1 && !t_cmd->cmd_tab[i].cmd_args[2])
// 		ft_exit_normal(all, i);
// 	return (0);
// }

// int	ft_lauch_exec(t_all **all, int i)
// {
// 	(*all)->t_cmd->cmd_tab[i].id1 = fork();
// 	if ((*all)->t_cmd->cmd_tab[i].id1 == 0)
// 	{
// 		ft_set_signal();
// 		ft_redirection(*all, i);
// 		ft_close_pipe((*all)->t_cmd);
// 		ft_close_fd(all);
// 		if (exec((*all)->t_cmd->cmd_tab[i].cmd_args, (*all)->env) == -1)
// 			exit(127);
// 		exit(0);
// 	}
// 	return (0);
// }

// int	ft_launch_builtin_in_child(t_all **all, int i)
// {
// 	int	temp_exit_status;

// 	(*all)->t_cmd->cmd_tab[i].id1 = fork();
// 	if ((*all)->t_cmd->cmd_tab[i].id1 == 0)
// 	{
// 		ft_set_signal();
// 		ft_redirection(*all, i);
// 		ft_close_pipe((*all)->t_cmd);
// 		ft_close_fd(all);
// 		if (is_builtin_3((*all)->t_cmd->cmd_tab[i].cmd_args, all) == 1)
// 		{
// 		}
// 		(*all)->t_cmd->cmd_tab[i].id1 = -1;
// 		temp_exit_status = (*all)->exit_status;
// 		if (ft_strcmp((*all)->t_cmd->cmd_tab[i].cmd_args[0], "exit") == 0)
// 			temp_exit_status = ft_atoi((*all)->t_cmd->cmd_tab[i].cmd_args[1])
// 				% 256;
// 		exit(temp_exit_status);
// 	}
// 	return (0);
// }

// int	ft_launch_builtin_in_parent(t_all **all, int i)
// {
// 	int	temp_exit;

// 	if (is_builtin_3((*all)->t_cmd->cmd_tab[i].cmd_args, all) == 1)
// 	{
// 		(*all)->t_cmd->cmd_tab[i].id1 = fork();
// 		if ((*all)->t_cmd->cmd_tab[i].id1 == 0)
// 		{
// 			ft_set_signal();
// 			ft_close_pipe((*all)->t_cmd);
// 			ft_close_fd(all);
// 			temp_exit = (*all)->exit_status;
// 			if (ft_strncmp((*all)->t_cmd->cmd_tab[i].cmd_args[0],
// 					"exit", 4) == 0)
// 				temp_exit = ft_atoi((*all)->t_cmd->cmd_tab[i].cmd_args[1])
// 					% 256;
// 			exit(temp_exit);
// 		}
// 	}
// 	return (0);
// }

// int	ft_check_builtin_cmd_1(t_all **all, int i)
// {
// 	if (ft_strcmp((*all)->t_cmd->cmd_tab[i].cmd_args[0], "echo") == 0
// 		|| ft_strcmp((*all)->t_cmd->cmd_tab[i].cmd_args[0], "pwd") == 0
// 		|| ft_strcmp((*all)->t_cmd->cmd_tab[i].cmd_args[0], "env") == 0
// 		|| (ft_strcmp((*all)->t_cmd->cmd_tab[i].cmd_args[0], "export") == 0
// 			&& (*all)->t_cmd->nbr_cmd > 1)
// 		|| (ft_strcmp((*all)->t_cmd->cmd_tab[i].cmd_args[0], "exit") == 0
// 			&& (*all)->t_cmd->nbr_cmd > 1))
// 		return (0);
// 	else
// 		return (1);
// }

// int	ft_check_builtin_cmd_2(t_all **all, int i)
// {
// 	if (ft_strcmp((*all)->t_cmd->cmd_tab[i].cmd_args[0], "export") == 0
// 		|| ft_strcmp((*all)->t_cmd->cmd_tab[i].cmd_args[0], "unset") == 0
// 		|| ft_strcmp((*all)->t_cmd->cmd_tab[i].cmd_args[0], "cd") == 0
// 		// || ft_strcmp((*all)->t_cmd->cmd_tab[i].cmd_args[0], "pwd") == 0
// 		// || ft_strcmp((*all)->t_cmd->cmd_tab[i].cmd_args[0], "exit") == 0
// 		// || ft_strcmp((*all)->t_cmd->cmd_tab[i].cmd_args[0], "env") == 0
// 	)
// 		return (0);
// 	else
// 		return (1);
// }

// //execute les commandes 
// //condition pour verifier uniquement si les builtin existent
// //puis dup2
// //puis executer les fonctions
// int	ft_exec_commande(t_commande *t_cmd, t_all **all, char **env)
// {
// 	int	i;

// 	(void)env;
// 	i = 0;
// 	while (i < t_cmd->nbr_cmd)
// 	{
// 		if (ft_check_arg_empty(*all, &i) == 1)
// 			continue ;
// 		if (ft_check_input_failed(*all, &i) == 1)
// 			continue ;
// 		if (ft_check_builtin_cmd_1(all, i) == 0)
// 			ft_launch_builtin_in_child(all, i);
// 		else if (ft_check_builtin_cmd_2(all, i) == 0)
// 			ft_launch_builtin_in_parent(all, i);
// 		else if (ft_strcmp(t_cmd->cmd_tab[i].cmd_args[0], "exit") == 0
// 			&& t_cmd->nbr_cmd == 1)
// 			ft_exit_monstre(all, t_cmd, i);
// 		else
// 			ft_lauch_exec(all, i);
// 		i++;
// 	}
// 	ft_close_pipe(t_cmd);
// 	ft_close_fd(all);
// 	return (0);
// }

//pas encore utiliser
//attribue les state CMD ou ARG sur les token
void	ft_assign_cmd_arg_states(t_list **lst)
{
	t_list	*temp;
	int		first_cmd;

	if (!lst || !*lst)
		return ;
	temp = *lst;
	first_cmd = 1;
	while (*lst)
	{
		if ((*lst)->state == PIPE)
			first_cmd = 1;
		else if ((*lst)->state == NORMAL
			|| (*lst)->state == DOUBLEQUOTE || (*lst)->state == SINGLEQUOTE)
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

// Chemin par défaut plus complet pour fonctionner
//même en cas d'utilisation de env -i
char	**create_default_env(void)
{
	char	**tab;
	char	*str;
	char	cwd[PATH_MAX];
	char	*path;

	tab = NULL;
	str = NULL;
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
	path = "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
	tab = ft_add_double_tab(path, tab);
	if (!tab)
		return (NULL);
	return (tab);
}

int	ft_init_value(t_all **all)
{
	*all = malloc(sizeof(t_all));
	if (!(*all))
		return (1);
	(*all)->str = NULL;
	(*all)->shell = NULL;
	(*all)->t_cmd = NULL;
	(*all)->env = NULL;
	(*all)->exit_status_char = NULL;
	g_sigvaleur = 0;
	set_exit(&((*all))->exit_status);
	(*all)->exit_status = 0;
	return (0);
}

int	ft_init_env(t_all **all, char **env)
{
	if (env[0])
	{
		(*all)->env = ft_copy_double_tab(env);
		if (!(*all)->env)
		{
			ft_free_all(*all);
			free(*all);
			return (1);
		}
		ft_shlvl(all);
	}
	else
	{
		(*all)->env = create_default_env();
		if (!(*all)->env)
		{
			ft_err("minishell", "malloc failed");
			ft_free_all(*all);
			free(*all);
			return (1);
		}
	}
	return (0);
}

// Initialiser tous les pointeurs à NULL pour ft_free_all
// Configuration de l'environnement
// Configuration des signaux avec signal() au lieu de sigaction()
// Désactiver ECHOCTL pour ne pas afficher les caractères de contrôle
int	main(int argc, char **argv, char **env)
{
	t_all	*all;
	int		temp;
	int		result;

	(void)argv;
	if (argc == 1)
	{
		if (ft_init_value(&all) == 1)
			return (1);
		if (ft_init_env(&all, env) == 1)
			return (1);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, ft_test);
		while (1)
		{
			all->shell = NULL;
			if (tcgetattr(STDIN_FILENO, &all->term) == 0)
			{
				all->term.c_lflag |= 0001000;
				tcsetattr(STDIN_FILENO, TCSANOW, &all->term);
			}
			result = ft_read_input(&all);
			if (result == -1)
			{
				ft_free_double_tab(all->env);
				temp = all->exit_status;
				free(all);
				exit(temp);
			}
			else if (result == -2)
			{
				if (g_sigvaleur == 1)
				{
					all->exit_status = 130;
					g_sigvaleur = 0;
				}
				continue ;
			}
			result = ft_parse(&all);
			if (result == -1)
				continue ;
			else if (result == -2)
				return (ft_free_double_tab(all->env), free(all), 1);
			if (ft_open_pipe(all->t_cmd, &all) == 1)
			{
				printf("Erreur lors de la création des pipes\n");
				ft_free_all(all);
				continue ;
			}
			signal(SIGINT, SIG_IGN);
			ft_exec_commande(all->t_cmd, &all, all->env);
			ft_waitpid(all->t_cmd);
			signal(SIGINT, ft_test);
			ft_close_pipe(all->t_cmd);
			ft_check_exit_status(&all);
			ft_free_all(all);
		}
		ft_free_double_tab(all->env);
		free(all);
	}
	return (0);
}
