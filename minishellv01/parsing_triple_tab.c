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

int ft_print_triple_tab(t_commande *t_cmd);
int ft_set_triple_tab_null(t_commande *t_cmd);
int ft_create_triple_tab(t_list **shell ,t_commande **t_cmd);

int ft_print_triple_tab(t_commande *t_cmd)
{
	int j;

	j = 0;
	while (j < t_cmd->nbr_cmd)
	{
		if (t_cmd->cmd_tab[j].cmd_args)
		{
			printf("tab:%d\n", j);
			ft_print_tab(t_cmd->cmd_tab[j].cmd_args);
		}
		j++;
	}
	return (0);
}

//juste initialise a NULL les char**
int ft_set_triple_tab_null(t_commande *t_cmd)
{
	int i = 0;
	while (i < t_cmd->nbr_cmd)
	{
		t_cmd->cmd_tab[i].cmd_args = NULL;
		i++;
	}
	return (0);
}

int ft_create_triple_tab(t_list **shell ,t_commande **t_cmd)
{
	int i = 0;

	t_list *temp = *shell;
	while (*shell != NULL)
	{
		if ((*shell)->state == NORMAL || (*shell)->state == DOUBLEQUOTE || (*shell)->state == SINGLEQUOTE)
			(*t_cmd)->cmd_tab[i].cmd_args = ft_add_double_tab((*shell)->str, (*t_cmd)->cmd_tab[i].cmd_args);
		if ((*shell)->state == PIPE)
			i++;
		(*shell) = (*shell)->next;
	}
	(*shell) = temp;
	return (0);
}
