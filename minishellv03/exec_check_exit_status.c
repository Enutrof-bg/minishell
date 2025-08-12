/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_check_exit_status.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:05:44 by kevwang           #+#    #+#             */
/*   Updated: 2025/08/11 13:05:46 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Seulement mettre à jour l'exit status 
//si un processus a réellement été exécuté
//Si aucun processus n'a été exécuté 
//mais qu'aucune erreur n'a été détectée, exit_status = 0
//Si aucun processus n'a été exécuté à cause d'erreurs, 
//garder l'exit_status précédent

int	ft_check_process_executed(t_all *all)
{
	int	i;

	if (!all || !all->t_cmd || !all->t_cmd->cmd_tab)
		return (0);
	i = 0;
	while (i < all->t_cmd->nbr_cmd)
	{
		if (all->t_cmd->cmd_tab[i].id1 > 0)
			return (1);
		i++;
	}
	return (0);
}

void	ft_check_signal(t_all **all)
{
	int	sig;

	sig = WTERMSIG((*all)->t_cmd->status);
	if (sig == SIGQUIT)
		write(1, "Quit (core dumped)\n", 20);
	else if (sig == SIGINT)
		write(1, "\n", 1);
	if (sig != SIGPIPE)
		(*all)->exit_status = 128 + sig;
}

void	ft_check_no_process(t_all **all)
{
	int	has_error;
	int	j;

	has_error = 0;
	j = 0;
	while (j < (*all)->t_cmd->nbr_cmd)
	{
		if ((*all)->t_cmd->cmd_tab[j].input_failed == 1
			|| (*all)->t_cmd->cmd_tab[j].output_failed == 1)
		{
			has_error = 1;
			break ;
		}
		j++;
	}
	if (has_error == 0)
		(*all)->exit_status = 0;
}

void	ft_check_exit_status(t_all **all)
{
	int	process_executed;
	int	j;
	int	has_error;

	process_executed = ft_check_process_executed(*all);
	j = 0;
	has_error = 0;
	if (process_executed && WIFEXITED((*all)->t_cmd->status))
		(*all)->exit_status = WEXITSTATUS((*all)->t_cmd->status);
	else if (process_executed && WIFSIGNALED((*all)->t_cmd->status))
	{
		ft_check_signal(all);
	}
	else if (process_executed == 0)
	{
		ft_check_no_process(all);
	}
}
