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
			printf("%d:%s:%d\n", i,lst->str, lst->state);
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

// Fonction ft_strcpy utilitaire
char *ft_strcpy(char *dest, char *src)
{
	int i;
	
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

// Fonction pour vérifier si un caractère est alphanumérique
int ft_isalnum(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
}

// Fonction pour trouver une variable d'environnement
char *get_env_var(char *var_name, char **env)
{
	int i;
	int var_len;
	
	if (!var_name || !env)
		return (NULL);
	
	var_len = ft_strlen(var_name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, var_len) == 0 && env[i][var_len] == '=')
			return (&env[i][var_len + 1]);
		i++;
	}
	return (NULL);
}

// Fonction pour extraire le nom de la variable après $
char *extract_var_name(char *str, int start)
{
	int i;
	int len;
	
	i = start;
	len = 0;
	
	// Compter la longueur du nom de variable (lettres, chiffres, underscore)
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		len++;
		i++;
	}
	
	if (len == 0)
		return (NULL);
		
	return (ft_substr(str, start, len));
}

// Fonction pour vérifier si un caractère est alphanumérique
// int ft_isalnum(char c)
// {
// 	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
// }

// Fonction principale pour remplacer les variables d'environnement
char *replace_dollar_vars(char *str, char **env)
{
	char *result;
	char *var_name;
	char *var_value;
	char *temp;
	int i;
	int result_len;
	
	if (!str)
		return (NULL);
		
	// Calculer la taille nécessaire pour le résultat
	result_len = ft_strlen(str) * 2; // Estimation large
	result = malloc(result_len);
	if (!result)
		return (NULL);
	
	result[0] = '\0';
	i = 0;
	
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			var_name = extract_var_name(str, i + 1);
			if (var_name)
			{
				var_value = get_env_var(var_name, env);
				if (var_value)
				{
					temp = ft_strjoin(result, var_value);
					free(result);
					result = temp;
				}
				i += ft_strlen(var_name) + 1; // +1 pour le $
				free(var_name);
			}
			else
			{
				// Si pas de nom de variable valide après $, garder le $
				temp = malloc(ft_strlen(result) + 2);
				ft_strcpy(temp, result);
				temp[ft_strlen(result)] = '$';
				temp[ft_strlen(result) + 1] = '\0';
				free(result);
				result = temp;
				i++;
			}
		}
		else
		{
			// Copier le caractère normal
			temp = malloc(ft_strlen(result) + 2);
			ft_strcpy(temp, result);
			temp[ft_strlen(result)] = str[i];
			temp[ft_strlen(result) + 1] = '\0';
			free(result);
			result = temp;
			i++;
		}
	}
	
	return (result);
}

void replace_dollar(char *str)
{
	printf("iter:%s\n", str);
	int i;

	i = 0;
	if (ft_check(str, '$') == 1)
	{
		printf("il y a un $\n");
		// La vraie logique de remplacement sera faite dans la fonction principale
		// car on a besoin d'accès aux variables d'environnement
	}
}

void	ft_lstiter_env(t_list **lst, char **env)
{
	t_list *temp;
	char *new_str;

	temp = *lst;
	while (*lst != NULL)
	{
		if ((*lst)->state == DOUBLEQUOTE)
		{
			new_str = replace_dollar_vars((*lst)->str, env);
			if (new_str)
			{
				free((*lst)->str);
				(*lst)->str = new_str;
			}
		}
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
