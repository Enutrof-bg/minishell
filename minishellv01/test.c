/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:17:02 by kevwang           #+#    #+#             */
/*   Updated: 2025/06/27 11:17:03 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	//TEST fork()
	pid_t child_pid = fork();
        
    // The child process
    if (child_pid == 0) {
        printf("### Child ###\nCurrent PID: %d and Child PID: %d\n",
               getpid(), child_pid);

    } else {
    	sleep(1);
        printf("### Parent ###\nCurrent PID: %d and Child PID: %d\n",
               getpid(), child_pid);
    }

/*
	//TEST isatty()
	//#include <unistd.h>
	//int isatty(int fd);
	//isatty() returns 1 if fd is an open file descriptor referring to a
    //   terminal; otherwise 0 is returned, and errno is set to indicate
    //   the error.
	int test = isatty(0);
	if (test == 0)
		perror("Error: ");
	printf("isatty: %d\n", test);
*/


/*
	//TEST ttyname()
	//char **ttyname(int fd);
	char *tab = ttyname(2);
	if (!tab)
		perror("Error:");
	printf("%s\n", tab); //print /dev/pts/1 c'est quoi
*/


/*
	//TEST getenv()
	//char *getenv(const char *name);
	// printenv pour les var env
	char *test = getenv("USER");
	printf("USER=%s\n", test);
	test = getenv("PATH");
	printf("PATH=%s\n", test);
*/


/*
	//TEST readline()
	char *Ptest = "Salut > ";
	char *r1;
	r1 = readline(Ptest);
	printf("%s\n", r1);
	rl_clear_history();
*/


/*
	//TEST add_history()
	//jsp
	add_history(r1);
*/


/*
	//TEST getcwd()
	//obtenir le lien absolu actuel
	char *pwd;
	pwd = getcwd(NULL, 0);
	printf("pwd: %s\n", pwd);
*/


/*
	//TEST chdir()
	//changer le lien aboslue actuel
	pwd = getcwd(NULL, 0);
	printf("pwd AVANT chdir: %s\n", pwd);

	chdir("/home/kevwang/Desktop/gitenutrofbg/cercle4/minishell/minishellv01/dossiertest");
	
	pwd = getcwd(NULL, 0);
	printf("pwd APRES chdir: %s\n", pwd);
*/
}
