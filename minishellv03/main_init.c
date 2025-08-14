/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:19:24 by kevwang           #+#    #+#             */
/*   Updated: 2025/08/14 16:19:25 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init_value(t_all **all)
{
	*all = malloc(sizeof(t_all));
	if (!(*all))
		return (1);
	(*all)->str = NULL;
	(*all)->shell = NULL;
	(*all)->t_cmd = NULL;
	(*all)->env = NULL;
	(*all)->exit_status_char = NULL;
	g_sigvaleur = 0;
	set_exit(&((*all))->exit_status);
	(*all)->exit_status = 0;
	return (0);
}

// Configuration initiale des signaux
void	ft_setup_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_test);
	signal(SIGTSTP, SIG_IGN);
}

int	ft_initialize_minishell(t_all **all, char **env)
{
	if (ft_init_value(all) == 1)
		return (1);
	if (ft_init_env(all, env) == 1)
		return (1);
	ft_setup_signals();
	return (0);
}
