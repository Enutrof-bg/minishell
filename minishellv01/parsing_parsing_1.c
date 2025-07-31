/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_parsing_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:35:20 by kevwang           #+#    #+#             */
/*   Updated: 2025/07/31 12:35:21 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_parse_decoupe(char *str, t_list **shell);

int ft_parse_decoupe(char *str, t_list **shell)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		if (str[i] == '"')
		{
			// i++;
			ft_parse_double_quote(str, shell, &i);
		}
		else if (str[i] == '\'')
		{
			// i++;
			ft_parse_singlequote(str, shell, &i);
		}
		else if (str[i] == '|')
		{
			ft_parse_pipe(str, shell, &i);
		}
		else if (str[i] == '>')
		{
			ft_parse_out(str, shell, &i);
		}
		else if (str[i] == '<')
		{
			ft_parse_in(str, shell, &i);
		}
		else
		{
			ft_parse_space(str, shell, &i);
		}
	}
	return (0);
}
