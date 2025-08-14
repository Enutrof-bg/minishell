/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 13:50:09 by kevwang           #+#    #+#             */
/*   Updated: 2025/08/14 13:50:10 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redirection(t_all *all, int i)
{
	if (all->t_cmd->cmd_tab[i].infd >= 0)
		dup2(all->t_cmd->cmd_tab[i].infd, 0);
	else if (i > 0)
		dup2(all->t_cmd->cmd_tab[i - 1].fd[0], 0);
	if (all->t_cmd->cmd_tab[i].outfd >= 0)
		dup2(all->t_cmd->cmd_tab[i].outfd, 1);
	else if (i < all->t_cmd->nbr_cmd - 1)
		dup2(all->t_cmd->cmd_tab[i].fd[1], 1);
	return (0);
}
