/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_parsing_0.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:17:06 by kevwang           #+#    #+#             */
/*   Updated: 2025/08/11 13:17:09 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_parse(t_all **all)
{
//Parse_decoupe bah elle decoupe l'input en liste chaine
	int parse_result = ft_check_parse(all);
	if (parse_result == -1)
		return (-1); // Continue si la parsing a échoué à cause de guillemets non fermés
	else if (parse_result == -2)
		return (-2); // Malloc failure - exit program
	ft_concatenate(&(*all)->shell);
// ft_print(all->shell);
	if (ft_lstiter_env(&(*all)->shell, (*all)->env, *all) == -1)
	{
		free((*all)->str);
		if ((*all)->shell)
			ft_clear(&(*all)->shell);
		return (-1);
	}
// ft_print((*all)->shell);
	if (ft_init_triple_tab(all) == -2)
		return (ft_free_all(*all), -2);
	parse_result = ft_create_triple_tab(&(*all)->shell, &(*all)->t_cmd, all);
	if (parse_result == -2)
		return (ft_free_all(*all), -2);
	if (parse_result == -1)
		return (ft_free_all(*all), -1);
	if (ft_check_arg(all) == -1)
		return (-1);
	return (0);
}
