/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:27:19 by kevwang           #+#    #+#             */
/*   Updated: 2025/08/11 13:27:20 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_read_input(t_all **all)
{
	(*all)->str = readline("CacaTest > ");
	if (!(*all)->str)
	{
		write(1, "exit\n", 5);
		return (-1);
	}
	if (!(*all)->str[0])
	{
		free((*all)->str);
		return (-2);
	}
	g_sigvaleur = 0;
	add_history((*all)->str);
	return (0);
}
