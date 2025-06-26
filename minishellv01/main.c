/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:49:06 by kevwang           #+#    #+#             */
/*   Updated: 2025/06/26 13:11:48 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	//test readline
	char *Ptest = "Salut > ";
	char *r1;
	r1 = readline(Ptest);
	printf("%s\n", r1);


}
