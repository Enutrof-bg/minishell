/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_triple_tab_init.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 13:12:43 by kevwang           #+#    #+#             */
/*   Updated: 2025/08/14 13:12:44 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_set_triple_tab_null(t_commande *t_cmd)
{
	int	i;

	i = 0;
	while (i < t_cmd->nbr_cmd)
	{
		t_cmd->cmd_tab[i].cmd_args = NULL;
		t_cmd->cmd_tab[i].input_failed = 0;
		t_cmd->cmd_tab[i].output_failed = 0;
		t_cmd->cmd_tab[i].id1 = -1;
		t_cmd->cmd_tab[i].infd = -1;
		t_cmd->cmd_tab[i].outfd = -1;
		t_cmd->cmd_tab[i].in_str = NULL;
		t_cmd->cmd_tab[i].out_str = NULL;
		i++;
	}
	return (0);
}

// Initialisation des variables pour ft_create_triple_tab
void	ft_init_triple_tab_vars(t_commande *t_cmd,
		int *prev_infd, int *prev_outfd, int i)
{
	*prev_infd = -1;
	*prev_outfd = -1;
	t_cmd->cmd_tab[i].infd = -1;
	t_cmd->cmd_tab[i].outfd = -1;
	t_cmd->cmd_tab[i].heredoc = 0;
}
