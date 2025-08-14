/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 13:56:14 by kevwang           #+#    #+#             */
/*   Updated: 2025/08/14 13:56:16 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//execute les commandes 
//condition pour verifier uniquement si les builtin existent
//puis dup2
//puis executer les fonctions
int	ft_exec_commande(t_commande *t_cmd, t_all **all, char **env)
{
	int	i;

	(void)env;
	i = 0;
	while (i < t_cmd->nbr_cmd)
	{
		if (ft_check_arg_empty(*all, &i) == 1)
			continue ;
		if (ft_check_input_failed(*all, &i) == 1)
			continue ;
		if (ft_check_builtin_cmd_1(all, i) == 0)
			ft_launch_builtin_in_child(all, i);
		else if (ft_check_builtin_cmd_2(all, i) == 0)
			ft_launch_builtin_in_parent(all, i);
		else if (ft_strcmp(t_cmd->cmd_tab[i].cmd_args[0], "exit") == 0
			&& t_cmd->nbr_cmd == 1)
			ft_exit_monstre(all, t_cmd, i);
		else
			ft_lauch_exec(all, i);
		i++;
	}
	ft_close_pipe(t_cmd);
	ft_close_fd(all);
	return (0);
}
