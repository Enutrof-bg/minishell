/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dollar_handle_quote.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 12:51:25 by kevwang           #+#    #+#             */
/*   Updated: 2025/08/14 12:51:26 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Traite les guillemets simples
char	*ft_handle_single_quote(char *result, int *insinglequote, char c)
{
	*insinglequote = !(*insinglequote);
	return (ft_append_char(result, c));
}

// Traite les guillemets doubles
char	*ft_handle_double_quote(char *result, int *indoublequote)
{
	*indoublequote = !(*indoublequote);
	return (result);
}

// Traite les guillemets simples (version pour test2)
char	*ft_handle_single_quote_test2(char *result, int *insinglequote)
{
	*insinglequote = !(*insinglequote);
	return (result);
}
