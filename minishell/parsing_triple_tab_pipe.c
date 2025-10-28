/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_triple_tab_pipe.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 13:15:03 by kevwang           #+#    #+#             */
/*   Updated: 2025/08/14 13:15:04 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fonction pour gérer les pipes
int	ft_handle_pipe(t_commande *t_cmd, int *i, int *prev_infd, int *prev_outfd)
{
	(*i)++;
	t_cmd->cmd_tab[*i].infd = -1;
	t_cmd->cmd_tab[*i].outfd = -1;
	t_cmd->cmd_tab[*i].input_failed = 0;
	t_cmd->cmd_tab[*i].output_failed = 0;
	t_cmd->cmd_tab[*i].in_str = NULL;
	t_cmd->cmd_tab[*i].out_str = NULL;
	*prev_infd = -1;
	*prev_outfd = -1;
	return (0);
}
