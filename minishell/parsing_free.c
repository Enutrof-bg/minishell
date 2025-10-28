/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:28:46 by kevwang           #+#    #+#             */
/*   Updated: 2025/07/31 12:28:46 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_double_tab(char **tab);
void	ft_clear(t_list **lst);

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

// Sauvegarde le pointeur vers le nœud suivant
// Vérification pour éviter de libérer un pointeur NULL
// Avance au nœud suivant
// Marque la liste comme vide
void	ft_clear(t_list **lst)
{
	t_list	*del;
	t_list	*next;

	if (!lst || !*lst)
		return ;
	del = *lst;
	while (del != NULL)
	{
		next = del->next;
		if (del->str)
		{
			free(del->str);
			del->str = NULL;
		}
		free(del);
		del = next;
	}
	*lst = NULL;
}

void	ft_free_cmd_tab(t_all *all)
{
	int	j;

	if (!all || !all->t_cmd || !all->t_cmd->cmd_tab)
		return ;
	j = 0;
	while (j < all->t_cmd->nbr_cmd)
	{
		if (all->t_cmd->cmd_tab[j].cmd_args)
		{
			ft_free_double_tab(all->t_cmd->cmd_tab[j].cmd_args);
			all->t_cmd->cmd_tab[j].cmd_args = NULL;
		}
		j++;
	}
	free(all->t_cmd->cmd_tab);
	all->t_cmd->cmd_tab = NULL;
}

void	ft_free_all(t_all *all)
{
	if (!all)
		return ;
	ft_close_fd(&all);
	if (all->str)
	{
		free(all->str);
		all->str = NULL;
	}
	if (all->shell)
		ft_clear(&all->shell);
	ft_free_cmd_tab(all);
	if (all->t_cmd)
	{
		free(all->t_cmd);
		all->t_cmd = NULL;
	}
}
