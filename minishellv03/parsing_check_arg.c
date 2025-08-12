/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check_arg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:20:53 by kevwang           #+#    #+#             */
/*   Updated: 2025/08/11 13:20:54 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Vérifier si au moins une commande a des arguments
// Pas de commande valide, nettoyer et return(-1) aui va continue ;
// Vérification des arguments d'entrée
// Vérifier si au moins une commande a des arguments valides
// Si aucune commande valide n'a été trouvée, nettoyer les ressources
// Libérer la mémoire allouée pour chaque tableau d'arguments de commande
// Libérer le tableau de commandes et la structure de commandes
// Libérer la chaîne d'entrée et la liste chaînée
int	ft_check_arg(t_all **all)
{
	int	has_valid_cmd;
	int	j;

	has_valid_cmd = 0;
	j = 0;
	if (!all || !*all || !(*all)->t_cmd)
		return (-1);
	while (j < (*all)->t_cmd->nbr_cmd)
	{
		if ((*all)->t_cmd->cmd_tab[j].cmd_args
			&& (*all)->t_cmd->cmd_tab[j].cmd_args[0])
		{
			has_valid_cmd = 1;
			break ;
		}
		j++;
	}
	if (!has_valid_cmd)
	{
		ft_free_all(*all);
		return (-1);
	}
	return (0);
}
