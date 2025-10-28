/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_triple_tab_input.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 13:12:24 by kevwang           #+#    #+#             */
/*   Updated: 2025/08/14 13:12:25 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fonction pour gérer les redirections d'entrée (fichiers)
int	ft_handle_infile(t_list *shell,
		t_all *all, int i, int *prev_infd)
{
	if (*prev_infd != -1)
		close(*prev_infd);
	all->t_cmd->cmd_tab[i].infd = open(shell->str, O_RDONLY, 0644);
	if (all->t_cmd->cmd_tab[i].infd < 0)
	{
		if (all->t_cmd->cmd_tab[i].input_failed == 0
			&& all->t_cmd->cmd_tab[i].output_failed == 0)
			perror(shell->str);
		all->exit_status = 1;
		all->t_cmd->cmd_tab[i].infd = -1;
		all->t_cmd->cmd_tab[i].input_failed = 1;
	}
	else
		*prev_infd = all->t_cmd->cmd_tab[i].infd;
	return (0);
}

// Traitement des redirections d'entrée
int	ft_process_input_redirections(t_list *shell,
		t_all *all, int i, int *prev_infd)
{
	int	result;

	if (shell->state == INFILE && all->t_cmd->cmd_tab[i].input_failed == 0)
		ft_handle_infile(shell, all, i, prev_infd);
	else if (shell->state == LIMITER
		&& all->t_cmd->cmd_tab[i].input_failed == 0)
	{
		result = ft_handle_limiter(shell, all, i, prev_infd);
		if (result == -1)
			return (-1);
	}
	return (0);
}
