/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 13:46:43 by kevwang           #+#    #+#             */
/*   Updated: 2025/08/14 13:46:44 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Vérifier si la commande existe et a des arguments
int	ft_check_arg_empty(t_all *all, int *i)
{
	if (!all->t_cmd->cmd_tab[*i].cmd_args
		|| !all->t_cmd->cmd_tab[*i].cmd_args[0])
	{
		all->t_cmd->cmd_tab[*i].id1 = -1;
		(*i)++;
		return (1);
	}
	return (0);
}

// Vérifier si la commande a des redirections d'entrée qui ont échoué
// Ne pas exécuter la commande si redirection d'entrée a échoué
int	ft_check_input_failed(t_all *all, int *i)
{
	if (all->t_cmd->cmd_tab[*i].input_failed == 1
		|| all->t_cmd->cmd_tab[*i].output_failed == 1)
	{
		all->t_cmd->cmd_tab[*i].id1 = -1;
		(*i)++;
		return (1);
	}
	return (0);
}

int	ft_check_builtin_cmd_1(t_all **all, int i)
{
	if (ft_strcmp((*all)->t_cmd->cmd_tab[i].cmd_args[0], "echo") == 0
		|| ft_strcmp((*all)->t_cmd->cmd_tab[i].cmd_args[0], "pwd") == 0
		|| ft_strcmp((*all)->t_cmd->cmd_tab[i].cmd_args[0], "env") == 0
		|| (ft_strcmp((*all)->t_cmd->cmd_tab[i].cmd_args[0], "export") == 0
			&& (*all)->t_cmd->nbr_cmd > 1)
		|| (ft_strcmp((*all)->t_cmd->cmd_tab[i].cmd_args[0], "exit") == 0
			&& (*all)->t_cmd->nbr_cmd > 1))
		return (0);
	else
		return (1);
}

int	ft_check_builtin_cmd_2(t_all **all, int i)
{
	if (ft_strcmp((*all)->t_cmd->cmd_tab[i].cmd_args[0], "export") == 0
		|| ft_strcmp((*all)->t_cmd->cmd_tab[i].cmd_args[0], "unset") == 0
		|| ft_strcmp((*all)->t_cmd->cmd_tab[i].cmd_args[0], "cd") == 0
		// || ft_strcmp((*all)->t_cmd->cmd_tab[i].cmd_args[0], "pwd") == 0
		// || ft_strcmp((*all)->t_cmd->cmd_tab[i].cmd_args[0], "exit") == 0
		// || ft_strcmp((*all)->t_cmd->cmd_tab[i].cmd_args[0], "env") == 0
	)
		return (0);
	else
		return (1);
}
