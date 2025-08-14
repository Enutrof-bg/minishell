/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dollar_handle.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 12:47:44 by kevwang           #+#    #+#             */
/*   Updated: 2025/08/14 12:47:45 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_append_char(char *result, char c);
char	*ft_handle_exit_status(char *result, t_all *all, int *i);
char	*ft_handle_env_var(char *result, char *str, t_all *all, int *i);

// Ajoute un caractère au résultat
char	*ft_append_char(char *result, char c)
{
	int		len;
	char	*temp;

	len = ft_strlen(result);
	temp = malloc(sizeof(char) * (len + 2));
	if (!temp)
		return (NULL);
	ft_strcpy(temp, result);
	temp[len] = c;
	temp[len + 1] = '\0';
	free(result);
	return (temp);
}

// Traite $? (exit status)
char	*ft_handle_exit_status(char *result, t_all *all, int *i)
{
	char	*temp;

	all->exit_status_char = ft_itoa(all->exit_status);
	if (!all->exit_status_char)
		return (NULL);
	temp = ft_strjoin(result, all->exit_status_char);
	free(all->exit_status_char);
	if (!temp)
		return (NULL);
	free(result);
	*i += 2;
	return (temp);
}

// Traite les variables d'environnement
char	*ft_handle_env_var(char *result, char *str, t_all *all, int *i)
{
	char	*env_name;
	char	*env_var;
	char	*temp;

	env_name = get_env_name(str, *i + 1);
	if (env_name)
	{
		env_var = get_env_var(env_name, all->env);
		if (env_var)
		{
			temp = ft_strjoin(result, env_var);
			if (!temp)
				return (free(env_name), NULL);
			free(result);
			result = temp;
		}
		*i = *i + ft_strlen(env_name) + 1;
		free(env_name);
		return (result);
	}
	else
		return (ft_append_char(result, str[(*i)++]));
}
