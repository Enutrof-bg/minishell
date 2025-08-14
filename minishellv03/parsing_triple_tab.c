/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_triple_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:31:45 by kevwang           #+#    #+#             */
/*   Updated: 2025/07/31 12:31:45 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	ft_print_triple_tab(t_commande *t_cmd)
// {
// 	int	j;

// 	j = 0;
// 	while (j < t_cmd->nbr_cmd)
// 	{
// 		if (t_cmd->cmd_tab[j].cmd_args)
// 		{
// 			printf("tab:%d\n", j);
// 			ft_print_tab(t_cmd->cmd_tab[j].cmd_args);
// 			printf("infd:%d\n", t_cmd->cmd_tab[j].infd);
// 			printf("outfd:%d\n", t_cmd->cmd_tab[j].outfd);
// 		}
// 		j++;
// 	}
// 	return (0);
// }

//juste initialise a NULL les char**
// int	ft_set_triple_tab_null(t_commande *t_cmd)
// {
// 	int	i;

// 	i = 0;
// 	while (i < t_cmd->nbr_cmd)
// 	{
// 		t_cmd->cmd_tab[i].cmd_args = NULL;
// 		t_cmd->cmd_tab[i].input_failed = 0;
// 		t_cmd->cmd_tab[i].output_failed = 0;
// 		t_cmd->cmd_tab[i].id1 = -1;
// 		t_cmd->cmd_tab[i].infd = -1;
// 		t_cmd->cmd_tab[i].outfd = -1;
// 		t_cmd->cmd_tab[i].in_str = NULL;
// 		t_cmd->cmd_tab[i].out_str = NULL;
// 		i++;
// 	}
// 	return (0);
// }

// Fonction pour gérer les arguments de commande
// int	ft_handle_cmd_arg(t_list *shell, t_commande *t_cmd, int i)
// {
// 	t_cmd->cmd_tab[i].cmd_args = ft_add_double_tab(shell->str,
// 			t_cmd->cmd_tab[i].cmd_args);
// 	if (!t_cmd->cmd_tab[i].cmd_args)
// 		return (-2);
// 	return (0);
// }

// // Fonction pour gérer les redirections d'entrée (fichiers)
// int	ft_handle_infile(t_list *shell,
// 		t_all *all, int i, int *prev_infd)
// {
// 	if (*prev_infd != -1)
// 		close(*prev_infd);
// 	all->t_cmd->cmd_tab[i].infd = open(shell->str, O_RDONLY, 0644);
// 	if (all->t_cmd->cmd_tab[i].infd < 0)
// 	{
// 		if (all->t_cmd->cmd_tab[i].input_failed == 0
// 			&& all->t_cmd->cmd_tab[i].output_failed == 0)
// 			perror(shell->str);
// 		all->exit_status = 1;
// 		all->t_cmd->cmd_tab[i].infd = -1;
// 		all->t_cmd->cmd_tab[i].input_failed = 1;
// 	}
// 	else
// 		*prev_infd = all->t_cmd->cmd_tab[i].infd;
// 	return (0);
// }

// // Configuration des signaux et terminal pour heredoc
// void	ft_setup_heredoc_env(t_all *all)
// {
// 	signal(SIGINT, SIG_DFL);
// 	signal(SIGQUIT, SIG_IGN);
// 	if (tcgetattr(STDIN_FILENO, &all->term) == 0)
// 	{
// 		all->term.c_lflag &= ~0001000;
// 		tcsetattr(STDIN_FILENO, TCSANOW, &all->term);
// 	}
// }

// // Préparation du fichier temporaire pour heredoc
// void	ft_prepare_temp_file(t_commande *t_cmd, int i)
// {
// 	if (access("temp", F_OK) == 0)
// 	{
// 		close(t_cmd->cmd_tab[i].infd);
// 		unlink("temp");
// 	}
// 	t_cmd->cmd_tab[i].infd = open("temp", O_WRONLY | O_CREAT | O_APPEND, 0644);
// }

// // Lecture et écriture des lignes heredoc
// void	ft_process_heredoc_lines(t_list *shell, t_commande *t_cmd, int i)
// {
// 	char	*line;

// 	line = get_next_line(0);
// 	while (line && g_sigvaleur == 0)
// 	{
// 		if (ft_strncmp(line, shell->str, ft_strlen(shell->str)) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		write(t_cmd->cmd_tab[i].infd, line, ft_strlen(line));
// 		free(line);
// 		line = get_next_line(0);
// 	}
// }

// // Gestion du processus enfant heredoc
// int	ft_handle_heredoc_child(t_list *shell,
// 			t_commande *t_cmd, t_all *all, int i)
// {
// 	ft_setup_heredoc_env(all);
// 	t_cmd->cmd_tab[i].heredoc++;
// 	ft_prepare_temp_file(t_cmd, i);
// 	ft_process_heredoc_lines(shell, t_cmd, i);
// 	close(t_cmd->cmd_tab[i].infd);
// 	exit(0);
// }

// // Fonction pour traiter la sortie du processus heredoc
// int	ft_process_heredoc_exit(t_commande *t_cmd, int i, int *prev_infd)
// {
// 	close(t_cmd->cmd_tab[i].infd);
// 	t_cmd->cmd_tab[i].infd = open("temp", O_RDONLY, 0644);
// 	if (t_cmd->cmd_tab[i].infd < 0)
// 	{
// 		perror("temp");
// 		t_cmd->cmd_tab[i].input_failed = 1;
// 	}
// 	else
// 		*prev_infd = t_cmd->cmd_tab[i].infd;
// 	return (0);
// }

// // Fonction pour traiter les signaux du processus heredoc
// int	ft_handle_heredoc_signals(t_all *all, int status)
// {
// 	int	sig;

// 	if (WIFSIGNALED(status))
// 	{
// 		sig = WTERMSIG(status);
// 		if (sig == SIGINT)
// 		{
// 			write(1, "^C\n", 3);
// 			all->exit_status = 128 + sig;
// 			return (-1);
// 		}
// 	}
// 	return (0);
// }

// // Fonction pour préparer le fichier temporaire heredoc
// int	ft_prepare_heredoc_file(t_list *shell,
// 		t_all *all, int i, int *prev_infd)
// {
// 	if (*prev_infd != -1)
// 		close(*prev_infd);
// 	all->t_cmd->cmd_tab[i].infd = open("temp",
// 			O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	if (all->t_cmd->cmd_tab[i].infd < 0)
// 	{
// 		if (all->t_cmd->cmd_tab[i].input_failed == 0
// 			&& all->t_cmd->cmd_tab[i].output_failed == 0)
// 			perror(shell->str);
// 		all->exit_status = 1;
// 		all->t_cmd->cmd_tab[i].infd = -1;
// 		all->t_cmd->cmd_tab[i].input_failed = 1;
// 		return (-1);
// 	}
// 	return (0);
// }

// Fonction pour gérer les redirections d'entrée via heredoc
// Préparer le fichier temporaire
// Configurer les signaux et fork
	// Processus enfant
// Processus parent
// Attendre la fin du heredoc
// Traiter la sortie
// int	ft_handle_limiter(t_list *shell,
// 		t_all *all, int i, int *prev_infd)
// {
// 	int	status;
// 	int	result;

// 	if (ft_prepare_heredoc_file(shell, all, i, prev_infd) < 0)
// 		return (0);
// 	signal(SIGINT, SIG_IGN);
// 	all->t_cmd->cmd_tab[i].id_here_doc = fork();
// 	if (all->t_cmd->cmd_tab[i].id_here_doc == 0)
// 		ft_handle_heredoc_child(shell, all->t_cmd, all, i);
// 	else
// 	{
// 		waitpid(all->t_cmd->cmd_tab[i].id_here_doc, &status, 0);
// 		signal(SIGINT, ft_test);
// 		result = ft_handle_heredoc_signals(all, status);
// 		if (result < 0)
// 			return (-1);
// 		ft_process_heredoc_exit(all->t_cmd, i, prev_infd);
// 	}
// 	return (0);
// }

// // Fonction pour gérer les redirections de sortie (fichiers)
// int	ft_handle_outfile(t_list *shell,
// 		t_all *all, int i, int *prev_outfd)
// {
// 	if (*prev_outfd != -1)
// 		close(*prev_outfd);
// 	all->t_cmd->cmd_tab[i].outfd = open(shell->str,
// 			O_WRONLY | O_TRUNC | O_CREAT, 0644);
// 	if (all->t_cmd->cmd_tab[i].outfd < 0)
// 	{
// 		if (all->t_cmd->cmd_tab[i].output_failed == 0
// 			&& all->t_cmd->cmd_tab[i].input_failed == 0)
// 			perror(shell->str);
// 		all->exit_status = 1;
// 		all->t_cmd->cmd_tab[i].outfd = -1;
// 		all->t_cmd->cmd_tab[i].output_failed = 1;
// 	}
// 	else
// 		*prev_outfd = all->t_cmd->cmd_tab[i].outfd;
// 	return (0);
// }

// // Fonction pour gérer les redirections de sortie en mode append
// int	ft_handle_append(t_list *shell,
// 		t_all *all, int i, int *prev_outfd)
// {
// 	if (*prev_outfd != -1)
// 		close(*prev_outfd);
// 	all->t_cmd->cmd_tab[i].outfd = open(shell->str,
// 			O_WRONLY | O_APPEND | O_CREAT, 0644);
// 	if (all->t_cmd->cmd_tab[i].outfd < 0)
// 	{
// 		if (all->t_cmd->cmd_tab[i].output_failed == 0
// 			&& all->t_cmd->cmd_tab[i].input_failed == 0)
// 			perror(shell->str);
// 		all->exit_status = 1;
// 		all->t_cmd->cmd_tab[i].outfd = -1;
// 		all->t_cmd->cmd_tab[i].output_failed = 1;
// 	}
// 	else
// 		*prev_outfd = all->t_cmd->cmd_tab[i].outfd;
// 	return (0);
// }

// // Fonction pour gérer les pipes
// int	ft_handle_pipe(t_commande *t_cmd,
// 			int *i, int *prev_infd, int *prev_outfd)
// {
// 	(*i)++;
// 	t_cmd->cmd_tab[*i].infd = -1;
// 	t_cmd->cmd_tab[*i].outfd = -1;
// 	t_cmd->cmd_tab[*i].input_failed = 0;
// 	t_cmd->cmd_tab[*i].output_failed = 0;
// 	t_cmd->cmd_tab[*i].in_str = NULL;
// 	t_cmd->cmd_tab[*i].out_str = NULL;
// 	*prev_infd = -1;
// 	*prev_outfd = -1;
// 	return (0);
// }

// // Initialisation des variables pour ft_create_triple_tab
// void	ft_init_triple_tab_vars(t_commande *t_cmd,
// 		int *prev_infd, int *prev_outfd, int i)
// {
// 	*prev_infd = -1;
// 	*prev_outfd = -1;
// 	t_cmd->cmd_tab[i].infd = -1;
// 	t_cmd->cmd_tab[i].outfd = -1;
// 	t_cmd->cmd_tab[i].heredoc = 0;
// }

// // Traitement des états de texte normal
// int	ft_process_text_states(t_list *shell, t_commande *t_cmd, int i)
// {
// 	int	result;

// 	if (shell->state == NORMAL || shell->state == DOUBLEQUOTE
// 		|| shell->state == SINGLEQUOTE)
// 	{
// 		result = ft_handle_cmd_arg(shell, t_cmd, i);
// 		if (result == -2)
// 			return (-2);
// 	}
// 	return (0);
// }

// // Traitement des redirections d'entrée
// int	ft_process_input_redirections(t_list *shell,
// 		t_all *all, int i, int *prev_infd)
// {
// 	int	result;

// 	if (shell->state == INFILE && all->t_cmd->cmd_tab[i].input_failed == 0)
// 		ft_handle_infile(shell, all, i, prev_infd);
// 	else if (shell->state == LIMITER
// 		&& all->t_cmd->cmd_tab[i].input_failed == 0)
// 	{
// 		result = ft_handle_limiter(shell, all, i, prev_infd);
// 		if (result == -1)
// 			return (-1);
// 	}
// 	return (0);
// }

// // Traitement des redirections de sortie
// void	ft_process_output_redirections(t_list *shell,
// 		t_all *all, int i, int *prev_outfd)
// {
// 	if (shell->state == OUTFILE && all->t_cmd->cmd_tab[i].output_failed == 0
// 		&& all->t_cmd->cmd_tab[i].input_failed == 0)
// 		ft_handle_outfile(shell, all, i, prev_outfd);
// 	else if (shell->state == OUTFILEAPPEND
// 		&& all->t_cmd->cmd_tab[i].output_failed == 0
// 		&& all->t_cmd->cmd_tab[i].input_failed == 0)
// 		ft_handle_append(shell, all, i, prev_outfd);
// }

// Fonction principale refactorisée
int	ft_create_triple_tab(t_list **shell, t_commande **t_cmd, t_all **all)
{
	t_list	*temp;
	int		i;
	int		prev_infd;
	int		prev_outfd;
	int		result;

	i = 0;
	temp = *shell;
	ft_init_triple_tab_vars(*t_cmd, &prev_infd, &prev_outfd, i);
	while (*shell != NULL)
	{
		result = ft_process_text_states(*shell, *t_cmd, i);
		if (result == -2)
			return (*shell = temp, -2);
		result = ft_process_input_redirections(*shell, *all, i, &prev_infd);
		if (result == -1)
			return (*shell = temp, -1);
		ft_process_output_redirections(*shell, *all, i, &prev_outfd);
		if ((*shell)->state == PIPE)
			ft_handle_pipe(*t_cmd, &i, &prev_infd, &prev_outfd);
		(*shell) = (*shell)->next;
	}
	(*shell) = temp;
	return (0);
}
