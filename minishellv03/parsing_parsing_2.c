/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_parsing_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:37:57 by kevwang           #+#    #+#             */
/*   Updated: 2025/07/31 12:37:59 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_parse_double_quote(char *str, t_list **shell, int *i);
int		ft_parse_singlequote(char *str, t_list **shell, int *i);
char	*ft_remove_quote(char *str);
int		ft_parse_space(char *str, t_list **shell, int *i, t_all *all);

// char	*ft_remove_quote(char *str)
// {
// 	int		i;
// 	int		j;
// 	char	*new;
// 	int		insinglequote;
// 	int		indoublequote;

// 	i = 0;
// 	j = 0;
// 	insinglequote = 0;
// 	indoublequote = 0;
// 	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
// 	if (!new)
// 		return (NULL);
// 	while (str[i])
// 	{
// 		if (str[i] == '"' && !insinglequote)
// 		{
// 			indoublequote = !indoublequote;
// 		}
// 		else if (str[i] == '\'' && !indoublequote)
// 		{
// 			insinglequote = !insinglequote;
// 		}
// 		else if (insinglequote == 1 && str[i] == '"')
// 		{
// 			new[j] = str[i];
// 			j++;
// 		}
// 		else if (indoublequote == 1 && str[i] == '\'')
// 		{
// 			new[j] = str[i];
// 			j++;
// 		}
// 		else
// 		{
// 			new[j] = str[i];
// 			j++;
// 		}
// 		i++;
// 	}
// 	new[j] = '\0';
// 	return (new);
// }

int	ft_parse_add_list_double(char *str, int *i, int j, t_list **shell)
{
	char	*temp;
	char	*temp3;

	temp = ft_substr(str, *i, j);
	if (!temp)
		return (-2);
	temp3 = replace_dollar_test2(temp);
	if (!temp3)
		return (free(temp), -2);
	if (ft_add(shell, temp3, DOUBLEQUOTE) == -2)
		return (free(temp), free(temp3), -2);
	free(temp);
	free(temp3);
	return (0);
}

int	ft_parse_general(char *str, int *j, int *indoublequote, int *insinglequote)
{
	if (str[*j] == '\0' && (*indoublequote == 1 || *insinglequote == 1))
		return (ft_err("minishell: syntax error: unclosed quote\n", NULL), -1);
	if (str[*j] == '\\' && *indoublequote == 0 && *insinglequote == 0)
			j++;
	else if (str[*j] == '"' && !(*insinglequote))
		*indoublequote = !(*indoublequote);
	else if (str[*j] == '\'' && !(*indoublequote))
		*insinglequote = !(*insinglequote);
	return (0);
}

int	ft_parse_double_quote(char *str, t_list **shell, int *i)
{
	int		j;
	int		insingle;
	int		indouble;
	int		result;

	insingle = 0;
	indouble = 0;
	j = 0;
	while ((str[*i + j] != ' ' && str[*i + j] != '|' && str[*i + j] != '\0')
		|| (indouble == 1 || insingle == 1))
	{
		if (ft_parse_general(&str[*i], &j, &indouble, &insingle) == -1)
			return (-1);
		j++;
	}
	if (j > 0)
	{
		result = ft_parse_add_list_double(str, i, j, shell);
		if (result == -2)
			return (-2);
	}
	*i = *i + j;
	if (str[*i] == '"')
		(*i)++;
	return (0);
}

int	ft_parse_add_list_single(char *str, int *i, int j, t_list **shell)
{
	char	*temp;
	char	*temp3;

	temp = ft_substr(str, *i, j);
	if (!temp)
		return (-2);
	temp3 = replace_dollar_test2(temp);
	if (!temp3)
		return (free(temp), -2);
	if (ft_add(shell, temp3, SINGLEQUOTE) == -2)
		return (free(temp), free(temp3), -2);
	free(temp);
	free(temp3);
	return (0);
}

int	ft_parse_singlequote(char *str, t_list **shell, int *i)
{
	int		j;
	int		insingle;
	int		indouble;
	int		result;

	insingle = 0;
	indouble = 0;
	j = 0;
	while ((str[*i + j] != ' ' && str[*i + j] != '|' && str[*i + j] != '\0')
		|| (indouble == 1 || insingle == 1))
	{
		if (ft_parse_general(&str[*i], &j, &indouble, &insingle) == -1)
			return (-1);
		j++;
	}
	if (j > 0)
	{
		result = ft_parse_add_list_single(str, i, j, shell);
		if (result == -2)
			return (-2);
	}
	*i = *i + j;
	if (str[*i] == '\'')
		(*i)++;
	return (0);
}

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
