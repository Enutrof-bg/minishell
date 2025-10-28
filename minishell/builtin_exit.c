/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 13:41:29 by kevwang           #+#    #+#             */
/*   Updated: 2025/08/14 13:41:32 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit_no_arg(t_all **all)
{
	int	temp_exit_status;

	write(1, "exit\n", 5);
	temp_exit_status = (*all)->exit_status;
	ft_free_all(*all);
	ft_free_double_tab((*all)->env);
	free(*all);
	exit(temp_exit_status);
}

int	ft_exit_wrong_arg(t_all **all, int i)
{
	write(1, "exit\n", 5);
	ft_err((*all)->t_cmd->cmd_tab[i].cmd_args[1], "numeric argument required");
	ft_free_all(*all);
	ft_free_double_tab((*all)->env);
	free(*all);
	exit(2);
}

int	ft_exit_two_arg(t_all **all, int i)
{
	write(1, "exit\n", 5);
	ft_err((*all)->t_cmd->cmd_tab[i].cmd_args[1], "too many arguments");
	(*all)->exit_status = 1;
	(*all)->t_cmd->cmd_tab[i].id1 = fork();
	if ((*all)->t_cmd->cmd_tab[i].id1 == 0)
	{
		ft_close_pipe((*all)->t_cmd);
		ft_close_fd(all);
		exit(1);
	}
	return (1);
}

int	ft_exit_normal(t_all **all, int i)
{
	int	temp_exit_status;

	write(1, "exit\n", 5);
	temp_exit_status = ft_atoi((*all)->t_cmd->cmd_tab[i].cmd_args[1]) % 256;
	ft_free_all(*all);
	ft_free_double_tab((*all)->env);
	free(*all);
	exit(temp_exit_status);
}

int	ft_exit_monstre(t_all **all, t_commande *t_cmd, int i)
{
	int	temp_exit_status;

	temp_exit_status = 0;
	if (!t_cmd->cmd_tab[i].cmd_args[1])
		ft_exit_no_arg(all);
	if (!ft_is_digit(t_cmd->cmd_tab[i].cmd_args[1])
		|| t_cmd->cmd_tab[i].cmd_args[1][0] == '\0'
		|| (long long)ft_long_atoi(t_cmd->cmd_tab[i].cmd_args[1]) > LLONG_MAX
		|| (long long)ft_long_atoi(t_cmd->cmd_tab[i].cmd_args[1]) < LLONG_MIN)
		ft_exit_wrong_arg(all, i);
	if (t_cmd->cmd_tab[i].cmd_args[2])
		ft_exit_two_arg(all, i);
	if ((*all)->t_cmd->nbr_cmd == 1 && !t_cmd->cmd_tab[i].cmd_args[2])
		ft_exit_normal(all, i);
	return (0);
}
