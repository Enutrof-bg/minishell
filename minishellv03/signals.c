/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:56:26 by kevwang           #+#    #+#             */
/*   Updated: 2025/08/11 12:56:28 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_exit(int *exit2)
{
	static int	*new_exit = NULL;

	if (new_exit == NULL)
		new_exit = exit2;
	*new_exit = 130;
}

void	ft_test(int signum)
{
	(void)signum;
	g_sigvaleur = 1;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	set_exit(&g_sigvaleur);
}

void	ft_sigquit(int signum)
{
	(void)signum;
}
