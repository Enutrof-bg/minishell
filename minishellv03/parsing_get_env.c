/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_get_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 12:43:48 by kevwang           #+#    #+#             */
/*   Updated: 2025/08/14 12:43:50 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_var(char *str, char **env)
{
	int	i;
	int	len;

	i = 0;
	if (!str || !env)
		return (NULL);
	len = ft_strlen(str);
	while (env[i])
	{
		if (ft_strncmp(str, env[i], len) == 0 && env[i][len] == '=')
		{
			return (&env[i][len + 1]);
		}
		i++;
	}
	return (NULL);
}

char	*get_env_name(char *str, int start)
{
	int	i;
	int	len;

	len = 0;
	i = start;
	if (!str)
		return (NULL);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		i++;
		len++;
	}
	if (len == 0)
		return (NULL);
	return (ft_substr(str, start, len));
}
