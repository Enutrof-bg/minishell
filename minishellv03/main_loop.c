/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:19:46 by kevwang           #+#    #+#             */
/*   Updated: 2025/08/14 16:19:47 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Désactiver ECHOCTL pour ne pas afficher les caractères de contrôle
void	ft_setup_term(t_all *all)
{
	if (tcgetattr(STDIN_FILENO, &all->term) == 0)
	{
		all->term.c_lflag |= 0001000;
		tcsetattr(STDIN_FILENO, TCSANOW, &all->term);
	}
}

int	ft_handle_read_input(t_all *all, int result)
{
	int	temp;

	if (result == -1)
	{
		ft_free_double_tab(all->env);
		temp = all->exit_status;
		free(all);
		exit(temp);
	}
	if (result == -2)
	{
		if (g_sigvaleur == 1)
		{
			all->exit_status = 130;
			g_sigvaleur = 0;
		}
		return (1);
	}
	return (0);
}

int	ft_handle_parse(t_all *all, int result)
{
	if (result == -1)
		return (-1);
	else if (result == -2)
		return (ft_free_double_tab(all->env), free(all), exit(1), -2);
	return (0);
}

void	ft_execute_cmd(t_all *all)
{
	signal(SIGINT, SIG_IGN);
	ft_exec_commande(all->t_cmd, &all, all->env);
	ft_waitpid(all->t_cmd);
	signal(SIGINT, ft_test);
	ft_close_pipe(all->t_cmd);
	ft_check_exit_status(&all);
	ft_free_all(all);
}

// // Boucle principale du shell
// void	ft_main_loop(t_all *all)
// {
// 	int	result;

// 	while (1)
// 	{
// 		all->shell = NULL;
// 		ft_setup_term(all);
// 		result = ft_read_input(&all);
// 		if (ft_handle_exit(all, result))
// 			continue ;
// 		// ft_handle_signal_input(all, result)
// 		// 	continue ;
// 		result = ft_parse(&all);
// 		if (ft_handle_parse_result(all, result))
// 			continue ;
// 		if (ft_handle_pipe_error(all))
// 			continue ;
// 		ft_execute_command_sequence(all);
// 	}
// }
