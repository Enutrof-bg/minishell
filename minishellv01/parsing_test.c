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

t_list	*ft_lst(char *str)
{
	t_list	*newlist;

	newlist = malloc(sizeof(t_list));
	if (!newlist)
	{
		return (NULL);
	}
	newlist->str = ft_strdup(str);
	newlist->next = NULL;
	return (newlist);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	temp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while ((*lst)->next != NULL)
	{
		*lst = (*lst)->next;
	}
	(*lst)->next = new;
	*lst = temp;
}

void ft_add(t_list **lst, char *str, int state)
{
	if (!(*lst))
	{
		(*lst) = ft_lst(str);
		return ;
	}
	t_list *temp = *lst;
	while ((*lst)->next)
	{
		(*lst) = (*lst)->next;
	}
	(*lst)->next = ft_lst(str);
	(*lst)->state = state;
	(*lst) = temp;
}

int ft_size(t_list *lst)
{
	int size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return size;
}

void ft_print(t_list *lst)
{
	if (lst)
	{
		int size = ft_size(lst);
		// printf("size:%d\n", size);
		int i = 0;
		while (i < size)
		{
			printf("%d:%s\n", i,lst->str);
			lst = lst->next;
			i++;
		}
		// printf("%d\n", lst->val);
	}
}

//caca parsing_test.c minishell_utils.c 
int main(int argc, char **argv, char **env)
{
	// if (argc > 1)
	(void)argc;
	(void)argv;
	(void)env;

	t_list *shell;
	
	// t_list *temp;

	shell = malloc(sizeof(t_list));
	if (!shell)
		return (1);
	shell = NULL;
	// char **tab = NULL;
	char *temp;
	char *str;
	int i = 0;
	int j = 0;
	if (argc == 1)
	{
		// char *str = argv[1];
		// while (1)
		// {
		str = readline("test >");
		add_history(str);
		// printf("%s\n", str);
		while (str[i])
		{
			if (str[i] == ' ')
				i++;
			if (str[i] == '"')
			{
				i++; // Passer le guillemet ouvrant
				while (str[i + j] != '"' && str[i + j] != '\0')
					j++;
				if (j > 0)
				{
					temp = ft_substr(str, i, j);
					// tab = ft_add_double_tab(temp, tab);
					ft_add(&shell, temp, DOUBLEQUOTE);
					// printf("double:%s i:%d j:%d\n", temp, i, j);
					free(temp);
				}
				i = i + j;
				if (str[i] == '"') // Passer le guillemet fermant si présent
					i++;
				j = 0;
			}
			else if (str[i] == '\'')
			{
				i++; // Passer le guillemet ouvrant
				while (str[i + j] != '\'' && str[i + j] != '\0')
					j++;
				if (j > 0)
				{
					temp = ft_substr(str, i, j);
					// tab = ft_add_double_tab(temp, tab);
					ft_add(&shell, temp, SINGLEQUOTE);
					// printf("single:%s i:%d j:%d\n", temp, i, j);
					free(temp);
				}
				i = i + j;
				if (str[i] == '\'') // Passer le guillemet fermant si présent
					i++;
				j = 0;
			}
			else
			{
				while (str[i + j] != ' ' && str[i + j] != '"' && str[i + j] != '\'' /*&& str[i + j] != '|' */&& str[i + j] != '\0')
					j++;
				if (j > 0)
				{
					temp = ft_substr(str, i, j);
					// tab = ft_add_double_tab(temp, tab);
					ft_add(&shell, temp, NORMAL);
					// printf("space:%s i:%d j:%d\n", temp, i, j);
					free(temp);
				}
				i = i + j;
				j = 0;
			}
		}
		// ft_print_tab(tab);
		ft_print(shell);
		// }

		// ft_free_double_tab(tab);
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
