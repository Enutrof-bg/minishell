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

t_list	*ft_lst(char *str, int state)
{
	t_list	*newlist;

	newlist = malloc(sizeof(t_list));
	if (!newlist)
	{
		return (NULL);
	}
	newlist->str = ft_strdup(str);
	newlist->state = state;
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
		(*lst) = ft_lst(str, state);
		return ;
	}
	t_list *temp = *lst;
	while ((*lst)->next)
	{
		(*lst) = (*lst)->next;
	}
	(*lst)->next = ft_lst(str, state);
	// (*lst)->next->state = state;
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
			// printf("%d:%s:%d:%d\n", i,lst->str, lst->state, lst->redir);
			printf("%d:%s:%d\n", i,lst->str, lst->state);
			// printf("%d:'%s'\n", i,lst->str);
			lst = lst->next;
			i++;
		}
		// printf("%d\n", lst->val);
	}
}

void	ft_clear(t_list **lst)
{
	t_list	*del;

	while (*lst != NULL)
	{
		del = *lst;
		*lst = (*lst)->next;
		free(del->str);
		free(del);
	}
	*lst = NULL;
}

int ft_check(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_lstiter_env(t_list **lst, char **env)
{
	t_list *temp;
	char *new_str;

	temp = *lst;
	while (*lst != NULL)
	{
		if ((*lst)->state == DOUBLEQUOTE || (*lst)->state == NORMAL)
		{
			new_str = replace_dollar_vars((*lst)->str, env);
			if (new_str)
			{
				free((*lst)->str);
				(*lst)->str = new_str;
			}
		}
		(*lst)->redir = -1;
		if ((*lst)->state == INPUT)
			(*lst)->next->state = INFILE;
		if ((*lst)->state == OUTPUT)
			(*lst)->next->state = OUTFILE;
		if ((*lst)->state == APPEND)
			(*lst)->next->state = OUTFILEAPPEND;
		(*lst) = (*lst)->next;
	}
	*lst = temp;
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

	
	// char **tab = NULL;
	char *temp;
	char *str;
	int i = 0;
	int j = 0;
	if (argc == 1)
	{
		// shell = malloc(sizeof(t_list));
		// if (!shell)
		// 	return (1);
		// shell = NULL;
		// char *str = argv[1];
		// while (1)
		// {
			shell = malloc(sizeof(t_list));
			if (!shell)
				return (1);
			shell = NULL;
			str = readline("CacaTest >");
			add_history(str);
			// printf("%s\n", str);
			while (str[i])
			{
				if (str[i] == ' ')
					i++;
				if (str[i] == '"')
				{
					i++;
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
					if (str[i] == '"')
						i++;
					j = 0;
				}
				else if (str[i] == '\'')
				{
					i++;
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
					if (str[i] == '\'')
						i++;
					j = 0;
				}
				else if (str[i] == '|')
				{
					j++;
					while (str[i + j] == '|' && str[i + j] != '\0')
						j++;
					if (j > 0)
					{
						temp = ft_substr(str, i, j);
						// tab = ft_add_double_tab(temp, tab);
						if (ft_strlen(temp) == 1)
							ft_add(&shell, temp, PIPE);
						else
							ft_add(&shell, temp, ERROR);
						// printf("single:%s i:%d j:%d\n", temp, i, j);
						free(temp);
					}
					i = i + j;
					if (str[i] == '|')
						i++;
					j = 0;
				}
				else if (str[i] == '>')
				{
					j++;
					while (str[i + j] == '>' && str[i + j] != '\0')
						j++;
					if (j > 0)
					{
						temp = ft_substr(str, i, j);
						// tab = ft_add_double_tab(temp, tab);
						if (ft_strlen(temp) == 1)
							ft_add(&shell, temp, OUTPUT);
						else if (ft_strlen(temp) == 2)
							ft_add(&shell, temp, APPEND);
						else
							ft_add(&shell, temp, ERROR);
						// printf("single:%s i:%d j:%d\n", temp, i, j);
						free(temp);
					}
					i = i + j;
					if (str[i] == '>')
						i++;
					j = 0;
				}
				else if (str[i] == '<')
				{
					j++;
					while (str[i + j] == '<' && str[i + j] != '\0')
						j++;
					if (j > 0)
					{
						temp = ft_substr(str, i, j);
						// tab = ft_add_double_tab(temp, tab);
						if (ft_strlen(temp) == 1)
							ft_add(&shell, temp, INPUT);
						else if (ft_strlen(temp) == 2)
							ft_add(&shell, temp, HEREDOC);
						else
							ft_add(&shell, temp, ERROR);
						// printf("single:%s i:%d j:%d\n", temp, i, j);
						free(temp);
					}
					i = i + j;
					if (str[i] == '<')
						i++;
					j = 0;
				}
				else
				{
					while (str[i + j] != ' ' && str[i + j] != '"' && str[i + j] != '\'' && str[i + j] != '|' && str[i + j] != '\0')
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
			ft_lstiter_env(&shell, env);

			ft_print(shell);
			free(str);
			ft_clear(&shell);
			free(shell);
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
