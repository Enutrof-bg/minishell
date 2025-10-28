/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_delete_quote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 12:45:51 by kevwang           #+#    #+#             */
/*   Updated: 2025/08/14 12:45:51 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_dollar_test2(char *str)
{
	int		i;
	char	*result;
	int		indoublequote;
	int		insinglequote;

	indoublequote = 0;
	insinglequote = 0;
	result = malloc(sizeof(char) * 1);
	if (!result)
		return (NULL);
	result[0] = '\0';
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' && !insinglequote)
			result = ft_handle_double_quote(result, &indoublequote);
		else if (str[i] == '\'' && !indoublequote)
			result = ft_handle_single_quote_test2(result, &insinglequote);
		else
			result = ft_append_char(result, str[i]);
		if (!result)
			return (NULL);
		i++;
	}
	return (result);
}
