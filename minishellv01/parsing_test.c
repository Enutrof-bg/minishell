/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:38:30 by kevwang           #+#    #+#             */
/*   Updated: 2025/07/18 11:38:32 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_double_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**ft_copy_double_tab(char **tab)
{
	int		i;
	int		j;
	char	**newtab;

	i = 0;
	j = 0;
	while (tab[i])
		i++;
	newtab = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (tab[i])
	{
		newtab[i] = ft_strdup(tab[i]);
		i++;
	}
	newtab[i] = 0;
	return (newtab);
}

char **ft_add_double_tab(char *str, char **tab)
{
	int		i;
	int		j;
	char	**newtab;

	i = 0;
	j = 0;
	if (tab == NULL)
	{
		newtab = malloc(sizeof(char *) * 2);
		newtab[0] = ft_strdup(str);
		newtab[1] = 0;
		return (newtab);
	}
	while (tab[i])
		i++;
	newtab = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (tab[i])
	{
		newtab[i] = ft_strdup(tab[i]);
		i++;
	}
	newtab[i] = ft_strdup(str);
	i++;
	newtab[i] = 0;
	ft_free_double_tab(tab);
	return (newtab);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*newstr;
	size_t			s_len;

	i = 0;
	s_len = ft_strlen(s);
	if (start > s_len)
	{
		return (ft_strdup(""));
	}
	if (s_len - start > len)
		newstr = malloc(sizeof(char) * len + 1);
	else
		newstr = malloc(sizeof(char) * (s_len - start) + 1);
	if (newstr == NULL)
		return (NULL);
	while (i < len && s[start + i] != '\0'
		&& (size_t)start < ft_strlen(s))
	{
		newstr[i] = s[start + i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

//caca parsing_test.c minishell_utils.c 
int main(int argc, char **argv)
{
	// if (argc > 1)
	(void)argc;
	(void)argv;

	char **tab = NULL;
	char *temp;
	int i = 0;
	int j = 0;
	if (argc >1)
	{
		char *str = argv[1];
		// printf("%s\n", str);
		while (str[i])
		{
			if (str[i] == ' ')
				i++;
			else if (str[i] == '"')
			{
				i++; // Passer le guillemet ouvrant
				while (str[i + j] != '"' && str[i + j] != '\0')
				{
					j++;
				}
				temp = ft_substr(str, i, j);
				tab = ft_add_double_tab(temp, tab);
				free(temp);
				i = i + j;
				if (str[i] == '"') // Passer le guillemet fermant si présent
					i++;
				j = 0;
			}
			else
			{
				while (str[i + j] != ' ' && str[i + j] != '"' && str[i + j] != '\0')
					j++;
				temp = ft_substr(str, i, j);
				tab = ft_add_double_tab(temp, tab);
				free(temp);
				i = i + j;
				j = 0;
			}
		}
		ft_print_tab(tab);
		ft_free_double_tab(tab);
	}
	// char **copy = ft_copy_double_tab(argv);
	// ft_print_tab(copy);

	// copy = ft_add_double_tab("test", copy);
	// ft_print_tab(copy);
	// ft_free_double_tab(copy);



	// char *r1;

	// while(1)
	// {
	// 	r1 = readline("test >");

	// 	add_history(r1);


	// }
}
