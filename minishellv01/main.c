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

	//TEST readline()
	char *Ptest;
	char *r1;

	while(1)
	{
		Ptest = "Salut > ";
		r1 = readline(Ptest);
		printf("%s\n", r1);
	}

/*
	//TEST getcwd()
	//obtenir le lien absolu actuel
	char *pwd;
	pwd = getcwd(NULL, 0);
	printf("pwd: %s\n", pwd);

	//TEST chdir()
	//changer le lien aboslue actuel
	pwd = getcwd(NULL, 0);
	printf("pwd AVANT chdir: %s\n", pwd);

	chdir("/home/kevwang/Desktop/gitenutrofbg/cercle4/minishell/minishellv01/dossiertest");

	pwd = getcwd(NULL, 0);
	printf("pwd APRES chdir: %s\n", pwd);
*/
}
