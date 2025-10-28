/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_triple_tab_normal.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 13:12:36 by kevwang           #+#    #+#             */
/*   Updated: 2025/08/14 13:12:37 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_cmd_arg(t_list *shell, t_commande *t_cmd, int i)
{
	t_cmd->cmd_tab[i].cmd_args = ft_add_double_tab(shell->str,
			t_cmd->cmd_tab[i].cmd_args);
	if (!t_cmd->cmd_tab[i].cmd_args)
		return (-2);
	return (0);
}

// Traitement des états de texte normal
int	ft_process_text_states(t_list *shell, t_commande *t_cmd, int i)
{
	int	result;

	if (shell->state == NORMAL || shell->state == DOUBLEQUOTE
		|| shell->state == SINGLEQUOTE)
	{
		result = ft_handle_cmd_arg(shell, t_cmd, i);
		if (result == -2)
			return (-2);
	}
	return (0);
}
