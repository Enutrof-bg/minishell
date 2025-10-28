/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_create_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:26:37 by kevwang           #+#    #+#             */
/*   Updated: 2025/08/14 16:26:38 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_default_env(void)
{
	char	**tab;
	char	*str;
	char	cwd[PATH_MAX];

	tab = NULL;
	if (!getcwd(cwd, sizeof(cwd)))
		return (NULL);
	str = ft_strjoin("PWD=", cwd);
	if (!str)
		return (NULL);
	tab = ft_add_double_tab(str, tab);
	if (!tab)
		return (free(str), NULL);
	free(str);
	tab = ft_add_double_tab("_=/usr/bin/env", tab);
	if (!tab)
		return (NULL);
	tab = ft_add_double_tab("SHLVL=1", tab);
	if (!tab)
		return (NULL);
	str = "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
	tab = ft_add_double_tab(str, tab);
	if (!tab)
		return (NULL);
	return (tab);
}

int	ft_init_env(t_all **all, char **env)
{
	if (env[0])
	{
		(*all)->env = ft_copy_double_tab(env);
		if (!(*all)->env)
		{
			ft_free_all(*all);
			free(*all);
			return (1);
		}
		ft_shlvl(all);
	}
	else
	{
		(*all)->env = create_default_env();
		if (!(*all)->env)
		{
			ft_err("minishell", "malloc failed");
			ft_free_all(*all);
			free(*all);
			return (1);
		}
	}
	return (0);
}
