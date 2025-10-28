/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:58:42 by kevwang           #+#    #+#             */
/*   Updated: 2025/07/26 14:58:44 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcpy(char *dest, char *src);
int		ft_isalnum(char c);
char	*get_env_var(char *str, char **env);
char	*get_env_name(char *str, int start);
char	*replace_dollar_vars(char *str, char **env, t_all *all);

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_isalnum(char c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'));
}

// char	*get_env_var(char *str, char **env)
// {
// 	int	i;
// 	int	len;

// 	i = 0;
// 	if (!str || !env)
// 		return (NULL);
// 	len = ft_strlen(str);
// 	while (env[i])
// 	{
// 		if (ft_strncmp(str, env[i], len) == 0 && env[i][len] == '=')
// 		{
// 			return (&env[i][len + 1]);
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

// char	*get_env_name(char *str, int start)
// {
// 	int	i;
// 	int	len;

// 	len = 0;
// 	i = start;
// 	if (!str)
// 		return (NULL);
// 	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
// 	{
// 		i++;
// 		len++;
// 	}
// 	if (len == 0)
// 		return (NULL);
// 	return (ft_substr(str, start, len));
// }

// // Ajoute un caractère au résultat
// char	*ft_append_char(char *result, char c)
// {
// 	int		len;
// 	char	*temp;

// 	len = ft_strlen(result);
// 	temp = malloc(sizeof(char) * (len + 2));
// 	if (!temp)
// 		return (NULL);
// 	ft_strcpy(temp, result);
// 	temp[len] = c;
// 	temp[len + 1] = '\0';
// 	free(result);
// 	return (temp);
// }

// // Traite les guillemets simples
// char	*ft_handle_single_quote(char *result, int *insinglequote, char c)
// {
// 	*insinglequote = !(*insinglequote);
// 	return (ft_append_char(result, c));
// }

// // Traite $? (exit status)
// char	*ft_handle_exit_status(char *result, t_all *all, int *i)
// {
// 	char	*temp;

// 	all->exit_status_char = ft_itoa(all->exit_status);
// 	if (!all->exit_status_char)
// 		return (NULL);
// 	temp = ft_strjoin(result, all->exit_status_char);
// 	free(all->exit_status_char);
// 	if (!temp)
// 		return (NULL);
// 	free(result);
// 	*i += 2;
// 	return (temp);
// }

// // Traite les variables d'environnement
// char	*ft_handle_env_var(char *result, char *str, t_all *all, int *i)
// {
// 	char	*env_name;
// 	char	*env_var;
// 	char	*temp;

// 	env_name = get_env_name(str, *i + 1);
// 	if (env_name)
// 	{
// 		env_var = get_env_var(env_name, all->env);
// 		if (env_var)
// 		{
// 			temp = ft_strjoin(result, env_var);
// 			if (!temp)
// 				return (free(env_name), NULL);
// 			free(result);
// 			result = temp;
// 		}
// 		*i = *i + ft_strlen(env_name) + 1;
// 		free(env_name);
// 		return (result);
// 	}
// 	else
// 		return (ft_append_char(result, str[(*i)++]));
// }

//c'est vraiment que pour la norminette cette fonction 
//parce que ca faisait 27 lignes
int	ft_init_dollar(char **result, int *i, int *insinglequote)
{
	*insinglequote = 0;
	*result = malloc(sizeof(char) * 1);
	if (!(*result))
		return (-1);
	(*result)[0] = '\0';
	*i = 0;
	return (0);
}

//Remplace uniquement les variables avec $ sauf dans les single quotes
//traite $? pour exit status, $$ pour PID,
//et $VAR pour variables d'environnement
char	*replace_dollar_pour_de_vrai(char *str, t_all *all)
{
	int		i;
	char	*result;
	int		insinglequote;

	if (ft_init_dollar(&result, &i, &insinglequote) == -1)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'')
			result = ft_handle_single_quote(result, &insinglequote, str[i++]);
		else if (str[i] == '$' && str[i + 1] != '\0' && insinglequote == 0)
		{
			if (str[i + 1] == '?')
				result = ft_handle_exit_status(result, all, &i);
			else
				result = ft_handle_env_var(result, str, all, &i);
		}
		else
			result = ft_append_char(result, str[i++]);
		if (!result)
			return (NULL);
	}
	return (result);
}

// // Traite les guillemets doubles
// char	*ft_handle_double_quote(char *result, int *indoublequote)
// {
// 	*indoublequote = !(*indoublequote);
// 	return (result);
// }

// // Traite les guillemets simples (version pour test2)
// char	*ft_handle_single_quote_test2(char *result, int *insinglequote)
// {
// 	*insinglequote = !(*insinglequote);
// 	return (result);
// }

// char	*replace_dollar_test2(char *str)
// {
// 	int		i;
// 	char	*result;
// 	int		indoublequote;
// 	int		insinglequote;

// 	indoublequote = 0;
// 	insinglequote = 0;
// 	result = malloc(sizeof(char) * 1);
// 	if (!result)
// 		return (NULL);
// 	result[0] = '\0';
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '"' && !insinglequote)
// 			result = ft_handle_double_quote(result, &indoublequote);
// 		else if (str[i] == '\'' && !indoublequote)
// 			result = ft_handle_single_quote_test2(result, &insinglequote);
// 		else
// 			result = ft_append_char(result, str[i]);
// 		if (!result)
// 			return (NULL);
// 		i++;
// 	}
// 	return (result);
// }
