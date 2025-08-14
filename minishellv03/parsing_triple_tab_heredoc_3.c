/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_triple_tab_heredoc_3.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 13:30:11 by kevwang           #+#    #+#             */
/*   Updated: 2025/08/14 13:30:11 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fonction pour traiter la sortie du processus heredoc
int	ft_process_heredoc_exit(t_commande *t_cmd, int i, int *prev_infd)
{
	close(t_cmd->cmd_tab[i].infd);
	t_cmd->cmd_tab[i].infd = open("temp", O_RDONLY, 0644);
	if (t_cmd->cmd_tab[i].infd < 0)
	{
		perror("temp");
		t_cmd->cmd_tab[i].input_failed = 1;
	}
	else
		*prev_infd = t_cmd->cmd_tab[i].infd;
	return (0);
}

// Fonction pour traiter les signaux du processus heredoc
int	ft_handle_heredoc_signals(t_all *all, int status)
{
	int	sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
		{
			write(1, "^C\n", 3);
			all->exit_status = 128 + sig;
			return (-1);
		}
	}
	return (0);
}
