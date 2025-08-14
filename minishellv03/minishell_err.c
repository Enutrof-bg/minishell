/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 13:08:27 by kevwang           #+#    #+#             */
/*   Updated: 2025/08/14 13:08:28 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_err(char *msg1, char *msg2)
{
	write(2, msg1, ft_strlen(msg1));
	if (msg2)
	{
		write(2, ": ", 2);
		write(2, msg2, ft_strlen(msg2));
		write(2, "\n", 1);
	}
}

void	ft_err_2(char *msg1, char *msg2)
{
	write(2, msg1, ft_strlen(msg1));
	if (msg2)
	{
		write(2, "`", 1);
		write(2, msg2, ft_strlen(msg2));
		write(2, "'\n", 2);
	}
}
