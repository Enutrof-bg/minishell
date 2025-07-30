#include "minishell.h"

char *ft_strcpy(char *dest, char *src)
{
	int i;
	
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int ft_isalnum(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
}

char *get_env_var(char *str, char **env)
{
	int i;
	int len;

	i = 0;
	if (!str || !env)
		return (NULL);
	len = ft_strlen(str);
	while (env[i])
	{
		if (ft_strncmp(str, env[i], len) == 0 && env[i][len] == '=')
		{
			return (&env[i][len+1]);
		}
		i++;
	}
	return (NULL);
}

char *get_env_name(char *str, int start)
{
	int i;
	int len;

	len = 0;
	i = start;
	// printf("test1:%s\n", str);
	if (!str)
		return (NULL);
	// printf("test2:%s\n", str);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		i++;
		len++;
	}
	if (len == 0)
		return (NULL);
	return (ft_substr(str, start, len));
}

char *replace_dollar_vars_test(char *str, char **env, t_all *all)
{
	(void)env;
	(void)all;
	int i;
	char *result;
	char *env_name;
	char *env_var;
	char *temp;
	int len;

	result = malloc(sizeof(char) * 1);
	if (!result)
		return (NULL);
	result[0] = '\0';

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '\0')
		{
			if (str[i + 1] == '?')
			{
				all->exit_status_char = ft_itoa(all->exit_status);
				temp = ft_strjoin(result, all->exit_status_char);
				free(result);
				result = temp;
				free(all->exit_status_char);
				i += 2;
			}
			else
			{
				env_name = get_env_name(str, i + 1);
				if (env_name)
				{
					env_var = get_env_var(env_name, env);
					if (env_var)
					{
						// printf("%s\n", env_var);
						temp = ft_strjoin(result, env_var);
						free(result);
						result = temp;
					}
					i = i + ft_strlen(env_name) + 1;
					free(env_name);
				}
				else
				{
					len = ft_strlen(result);
					temp = malloc(sizeof(char) * (len + 2));
					if (!temp)
						return (NULL);
					ft_strcpy(temp, result);
					temp[len] = '\0';
					free(result);
					result = temp;
					i++;
				}
			}
		}
		else
		{
			len = ft_strlen(result);
			temp = malloc(sizeof(char) * (len + 2));
			if (!temp)
				return (NULL);
			ft_strcpy(temp, result);
			temp[len] = str[i];
			temp[len +1] = '\0';
			free(result);
			result = temp;
			i++;
		}
		// i++;
	}
	// return ("caca");
	return (result);
}

//caca test4.c parsing_dollar.c ft_strjoin.c minishell_utils.c ft_itoa.c -lreadline
int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	t_all *all = malloc(sizeof(t_all));

	while (1)
	{


		char *str = readline("CacaTest >");
		add_history(str);

		printf("    input:%s\n", str);
		char *new_str = replace_dollar_vars_test(str, env, all);
		printf("new_input:%s\n", new_str);
		int i = 0;
		while (i < new_str[i])
		{
			
			i++;
		}
	}
}