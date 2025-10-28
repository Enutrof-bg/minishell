/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 13:47:09 by kevwang           #+#    #+#             */
/*   Updated: 2025/08/14 13:47:10 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lauch_exec(t_all **all, int i)
{
	(*all)->t_cmd->cmd_tab[i].id1 = fork();
	if ((*all)->t_cmd->cmd_tab[i].id1 == 0)
	{
		ft_set_signal();
		ft_redirection(*all, i);
		ft_close_pipe((*all)->t_cmd);
		ft_close_fd(all);
		if (exec((*all)->t_cmd->cmd_tab[i].cmd_args, (*all)->env) == -1)
			exit(127);
		exit(0);
	}
	return (0);
}

int	ft_launch_builtin_in_child(t_all **all, int i)
{
	int	temp_exit_status;

	(*all)->t_cmd->cmd_tab[i].id1 = fork();
	if ((*all)->t_cmd->cmd_tab[i].id1 == 0)
	{
		ft_set_signal();
		ft_redirection(*all, i);
		ft_close_pipe((*all)->t_cmd);
		ft_close_fd(all);
		if (is_builtin_3((*all)->t_cmd->cmd_tab[i].cmd_args, all) == 1)
		{
		}
		(*all)->t_cmd->cmd_tab[i].id1 = -1;
		temp_exit_status = (*all)->exit_status;
		if (ft_strcmp((*all)->t_cmd->cmd_tab[i].cmd_args[0], "exit") == 0)
			temp_exit_status = ft_atoi((*all)->t_cmd->cmd_tab[i].cmd_args[1])
				% 256;
		exit(temp_exit_status);
	}
	return (0);
}

int	ft_launch_builtin_in_parent(t_all **all, int i)
{
	int	temp_exit;

	if (is_builtin_3((*all)->t_cmd->cmd_tab[i].cmd_args, all) == 1)
	{
		(*all)->t_cmd->cmd_tab[i].id1 = fork();
		if ((*all)->t_cmd->cmd_tab[i].id1 == 0)
		{
			ft_set_signal();
			ft_close_pipe((*all)->t_cmd);
			ft_close_fd(all);
			temp_exit = (*all)->exit_status;
			if (ft_strncmp((*all)->t_cmd->cmd_tab[i].cmd_args[0],
					"exit", 4) == 0)
				temp_exit = ft_atoi((*all)->t_cmd->cmd_tab[i].cmd_args[1])
					% 256;
			exit(temp_exit);
		}
	}
	return (0);
}
