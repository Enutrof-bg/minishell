/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_parsing_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:38:02 by kevwang           #+#    #+#             */
/*   Updated: 2025/07/31 12:38:03 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parse_pipe(char *str, t_list **shell, int *i);
int	ft_parse_out(char *str, t_list **shell, int *i);
int	ft_parse_in(char *str, t_list **shell, int *i);

int	ft_parse_pipe(char *str, t_list **shell, int *i)
{
	int		j;
	char	*temp;

	j = 1;
	while (str[*i + j] == '|' && str[*i + j] != '\0')
		j++;
	temp = ft_substr(str, *i, j);
	if (!temp)
		return (-2);
	if (ft_strlen(temp) == 1)
	{
		if (ft_add(shell, temp, PIPE) == -2)
			return (free(temp), -2);
	}
	else if (ft_strlen(temp) == 2)
		return (free(temp),
			ft_err("syntax error near unexpected token `||'\n", NULL), -1);
	else
		return (free(temp),
			ft_err("syntax error near unexpected token `||'\n", NULL), -1);
	*i = *i + j;
	if (str[*i] == '|')
		(*i)++;
	return (free(temp), 0);
}

int	ft_check_output_chevron(char *temp, t_list **shell)
{
	if (ft_strlen(temp) == 1)
	{
		if (ft_add(shell, temp, OUTPUT) == -2)
			return (-2);
	}
	else if (ft_strlen(temp) == 2)
	{
		if (ft_add(shell, temp, APPEND) == -2)
			return (-2);
	}
	else if (ft_strlen(temp) == 3)
		return (ft_err("syntax error near unexpected token `>'\n", NULL), -1);
	else
		return (ft_err("syntax error near unexpected token `>>'\n", NULL), -1);
	return (0);
}

int	ft_parse_out(char *str, t_list **shell, int *i)
{
	int		j;
	char	*temp;
	int		result;

	j = 1;
	while (str[*i + j] == '>' && str[*i + j] != '\0')
		j++;
	temp = ft_substr(str, *i, j);
	if (!temp)
		return (-2);
	result = ft_check_output_chevron(temp, shell);
	if (result == -2)
		return (free(temp), -2);
	if (result == -1)
		return (free(temp), -1);
	*i = *i + j;
	if (str[*i] == '>')
		(*i)++;
	return (free(temp), 0);
}

int	ft_check_input_chevron(char *temp, t_list **shell)
{
	if (ft_strlen(temp) == 1)
	{
		if (ft_add(shell, temp, INPUT) == -2)
			return (-2);
	}
	else if (ft_strlen(temp) == 2)
	{
		if (ft_add(shell, temp, HEREDOC) == -2)
			return (-2);
	}
	else if (ft_strlen(temp) == 3)
		return (ft_err("syntax error near unexpected token `<'\n", NULL), -1);
	else
		return (ft_err("syntax error near unexpected token `<<'\n", NULL), -1);
	return (0);
}

int	ft_parse_in(char *str, t_list **shell, int *i)
{
	int		j;
	char	*temp;
	int		result;

	j = 1;
	while (str[*i + j] == '<' && str[*i + j] != '\0')
		j++;
	temp = ft_substr(str, *i, j);
	if (!temp)
		return (-2);
	result = ft_check_input_chevron(temp, shell);
	if (result == -2)
		return (free(temp), -2);
	if (result == -1)
		return (free(temp), -1);
	*i = *i + j;
	if (str[*i] == '<')
		(*i)++;
	return (free(temp), 0);
}
