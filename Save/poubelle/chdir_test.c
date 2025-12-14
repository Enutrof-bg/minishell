#include <stdio.h>
#include <unistd.h>


int main()
{
//TEST getcwd()
	//obtenir le lien absolu actuel
	char *pwd;
	pwd = getcwd(NULL, 0);
	printf("pwd: %s\n", pwd);

	//TEST chdir()
	//changer le lien aboslue actuel
	pwd = getcwd(NULL, 0);
	printf("pwd AVANT chdir: %s\n", pwd);

	chdir("/home/kevwang/Desktop/gitenutrofbg/cercle4/minishell"); // changer avec un lien qui existe sur le pc

	pwd = getcwd(NULL, 0);
	printf("pwd APRES chdir: %s\n", pwd);

}