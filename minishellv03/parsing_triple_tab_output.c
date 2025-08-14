/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_triple_tab_output.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 13:12:28 by kevwang           #+#    #+#             */
/*   Updated: 2025/08/14 13:12:29 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fonction pour gérer les redirections de sortie (fichiers)
int	ft_handle_outfile(t_list *shell,
		t_all *all, int i, int *prev_outfd)
{
	if (*prev_outfd != -1)
		close(*prev_outfd);
	all->t_cmd->cmd_tab[i].outfd = open(shell->str,
			O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (all->t_cmd->cmd_tab[i].outfd < 0)
	{
		if (all->t_cmd->cmd_tab[i].output_failed == 0
			&& all->t_cmd->cmd_tab[i].input_failed == 0)
			perror(shell->str);
		all->exit_status = 1;
		all->t_cmd->cmd_tab[i].outfd = -1;
		all->t_cmd->cmd_tab[i].output_failed = 1;
	}
	else
		*prev_outfd = all->t_cmd->cmd_tab[i].outfd;
	return (0);
}

// Fonction pour gérer les redirections de sortie en mode append
int	ft_handle_append(t_list *shell,
		t_all *all, int i, int *prev_outfd)
{
	if (*prev_outfd != -1)
		close(*prev_outfd);
	all->t_cmd->cmd_tab[i].outfd = open(shell->str,
			O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (all->t_cmd->cmd_tab[i].outfd < 0)
	{
		if (all->t_cmd->cmd_tab[i].output_failed == 0
			&& all->t_cmd->cmd_tab[i].input_failed == 0)
			perror(shell->str);
		all->exit_status = 1;
		all->t_cmd->cmd_tab[i].outfd = -1;
		all->t_cmd->cmd_tab[i].output_failed = 1;
	}
	else
		*prev_outfd = all->t_cmd->cmd_tab[i].outfd;
	return (0);
}

// Traitement des redirections de sortie
void	ft_process_output_redirections(t_list *shell,
		t_all *all, int i, int *prev_outfd)
{
	if (shell->state == OUTFILE && all->t_cmd->cmd_tab[i].output_failed == 0
		&& all->t_cmd->cmd_tab[i].input_failed == 0)
		ft_handle_outfile(shell, all, i, prev_outfd);
	else if (shell->state == OUTFILEAPPEND
		&& all->t_cmd->cmd_tab[i].output_failed == 0
		&& all->t_cmd->cmd_tab[i].input_failed == 0)
		ft_handle_append(shell, all, i, prev_outfd);
}
