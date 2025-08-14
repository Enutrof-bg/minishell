/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_triple_tab_heredoc.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 13:12:48 by kevwang           #+#    #+#             */
/*   Updated: 2025/08/14 13:12:49 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fonction pour préparer le fichier temporaire heredoc
int	ft_prepare_heredoc_file(t_list *shell,
		t_all *all, int i, int *prev_infd)
{
	if (*prev_infd != -1)
		close(*prev_infd);
	all->t_cmd->cmd_tab[i].infd = open("temp",
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (all->t_cmd->cmd_tab[i].infd < 0)
	{
		if (all->t_cmd->cmd_tab[i].input_failed == 0
			&& all->t_cmd->cmd_tab[i].output_failed == 0)
			perror(shell->str);
		all->exit_status = 1;
		all->t_cmd->cmd_tab[i].infd = -1;
		all->t_cmd->cmd_tab[i].input_failed = 1;
		return (-1);
	}
	return (0);
}

int	ft_handle_limiter(t_list *shell,
		t_all *all, int i, int *prev_infd)
{
	int	status;
	int	result;

	if (ft_prepare_heredoc_file(shell, all, i, prev_infd) < 0)
		return (0);
	signal(SIGINT, SIG_IGN);
	all->t_cmd->cmd_tab[i].id_here_doc = fork();
	if (all->t_cmd->cmd_tab[i].id_here_doc == 0)
		ft_handle_heredoc_child(shell, all->t_cmd, all, i);
	else
	{
		waitpid(all->t_cmd->cmd_tab[i].id_here_doc, &status, 0);
		signal(SIGINT, ft_test);
		result = ft_handle_heredoc_signals(all, status);
		if (result < 0)
			return (-1);
		ft_process_heredoc_exit(all->t_cmd, i, prev_infd);
	}
	return (0);
}
