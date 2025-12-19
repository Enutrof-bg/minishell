#include <unistd.h>
#include <stdio.h>
int	ft_pwd()
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)))
	{
		return (printf("%s\n", cwd), 0);
	}
	else
	{
		perror("pwd: error retrieving current directory:");
		perror(" getcwd: cannot access parent directories: ");
		// (*all)->exit_status = 1;
	}
	return (1);
}
int main()
{
	chdir("//");
	ft_pwd();
}