/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:19:14 by kevwang           #+#    #+#             */
/*   Updated: 2025/08/14 16:19:15 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sigvaleur;

// Initialiser tous les pointeurs à NULL pour ft_free_all
// Configuration de l'environnement
// Configuration des signaux avec signal() au lieu de sigaction()
int	main(int argc, char **argv, char **env)
{
	t_all	*all;
	int		result;

	(void)argv;
	if (argc != 1)
		return (1);
	if (ft_initialize_minishell(&all, env) == 1)
		return (1);
	while (1)
	{
		all->shell = NULL;
		ft_setup_term(all);
		result = ft_read_input(&all);
		if (ft_handle_read_input(all, result) == 1)
			continue ;
		result = ft_parse(&all);
		if (ft_handle_parse(all, result) == -1)
			continue ;
		if (ft_open_pipe(all->t_cmd, &all) == 1)
			continue ;
		ft_execute_cmd(all);
	}
	ft_free_double_tab(all->env);
	free(all);
	return (0);
}
