/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_parsing_2_space.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 13:01:42 by kevwang           #+#    #+#             */
/*   Updated: 2025/08/14 13:01:43 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parse_add_list_space(char *str, int *i, int j, t_list **shell)
{
	char	*temp;
	char	*temp3;

	temp = ft_substr(str, *i, j);
	if (!temp)
		return (-2);
	temp3 = replace_dollar_test2(temp);
	if (!temp3)
		return (free(temp), -2);
	if (ft_add(shell, temp3, NORMAL) == -2)
		return (free(temp), free(temp3), -2);
	free(temp);
	free(temp3);
	return (0);
}

int	ft_parse_space(char *str, t_list **shell, int *i, t_all *all)
{
	int		j;
	int		insingle;
	int		indouble;
	int		result;

	(void)all;
	insingle = 0;
	indouble = 0;
	j = 0;
	while ((str[*i + j] != ' ' && str[*i + j] != '|' && str[*i + j] != '>'
			&& str[*i + j] != '<' && str[*i + j] != '\0')
		|| (indouble == 1 || insingle == 1))
	{
		if (ft_parse_general(&str[*i], &j, &indouble, &insingle) == -1)
			return (-1);
		j++;
	}
	if (j > 0)
	{
		result = ft_parse_add_list_space(str, i, j, shell);
		if (result == -2)
			return (-2);
	}
	*i = *i + j;
	return (0);
}
