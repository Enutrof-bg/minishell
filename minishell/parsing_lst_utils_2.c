/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lst_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:46:18 by kevwang           #+#    #+#             */
/*   Updated: 2025/07/31 12:46:18 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_size(t_list *lst);
void	ft_print(t_list *lst);
int		ft_check(char *str, char c);
int		ft_lstiter_env(t_list **lst, char **env, t_all *all);

// int	ft_size(t_list *lst)
// {
// 	int	size;

// 	size = 0;
// 	while (lst)
// 	{
// 		size++;
// 		lst = lst->next;
// 	}
// 	return (size);
// }

// void	ft_print(t_list *lst)
// {
// 	int	size;
// 	int	i;

// 	if (lst)
// 	{
// 		size = ft_size(lst);
// 		i = 0;
// 		while (i < size)
// 		{
// 			printf("%d:%s:%d:%zu\n", i, lst->str,
// 				lst->state, ft_strlen(lst->str));
// 			lst = lst->next;
// 			i++;
// 		}
// 	}
// }

// int	ft_check(char *str, char c)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == c)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

//ft_iter pour les redirections, a modifier | pas fonctionnelle correctemnt
// Vérifie si le token de redirection est suivi d'un token
// Vérifie si le token qui suit est un token valide pour une redirection
// Met à jour l'état du token suivant pour indiquer son rôle
int	check_redirect_syntax(t_list **lst, t_list *temp, int new_state)
{
	if (!(*lst)->next)
		return (*lst = temp,
			ft_err("syntax error near unexpected token `newline'\n", NULL), -1);
	if ((*lst)->next->state != NORMAL
		&& (*lst)->next->state != SINGLEQUOTE
		&& (*lst)->next->state != DOUBLEQUOTE)
		return (*lst = temp,
			ft_err_2("syntax error near unexpected token ",
				(*lst)->next->str), -1);
	(*lst)->next->state = new_state;
	return (0);
}

// Traite les différents types de redirections selon l'état
int	ft_process_redirection(t_list **lst, t_list *temp, int state)
{
	int	ret;
	int	target_state;

	if (state == INPUT)
		target_state = INFILE;
	else if (state == HEREDOC)
		target_state = LIMITER;
	else if (state == OUTPUT)
		target_state = OUTFILE;
	else if (state == APPEND)
		target_state = OUTFILEAPPEND;
	else
		return (0);
	ret = check_redirect_syntax(lst, temp, target_state);
	if (ret != 0)
		return (ret);
	return (0);
}

// Vérifie si le premier token est un pipe
// Vérifie si un pipe est le dernier token
// Traitement des différents types de redirections
int	ft_lstiter_env(t_list **lst, char **env, t_all *all)
{
	t_list	*temp;
	int		ret;

	(void)env;
	(void)all;
	if (!lst || !*lst)
		return (0);
	temp = *lst;
	if ((*lst)->state == PIPE)
		return (ft_err("syntax error near unexpected token `|'\n", NULL), -1);
	while (*lst)
	{
		if ((*lst)->next && (*lst)->next->state == PIPE && !(*lst)->next->next)
			return (*lst = temp,
				ft_err("syntax error near unexpected token `|'\n", NULL), -1);
		if ((*lst)->state == INPUT || (*lst)->state == HEREDOC
			|| (*lst)->state == OUTPUT || (*lst)->state == APPEND)
		{
			ret = ft_process_redirection(lst, temp, (*lst)->state);
			if (ret != 0)
				return (ret);
		}
		(*lst) = (*lst)->next;
	}
	return (*lst = temp, 0);
}
