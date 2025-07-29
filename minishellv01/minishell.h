/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:49:19 by kevwang           #+#    #+#             */
/*   Updated: 2025/06/26 12:49:19 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h> // pour readline etc
# include <readline/history.h> // pour readline etc
# include <sys/types.h>//wait
# include <sys/wait.h>//wait

# define SINGLEQUOTE 1
# define DOUBLEQUOTE 2
# define NORMAL 3
# define CMD 4
# define PIPE 5
# define ARG 6
# define INPUT 7
# define OUTPUT 8
# define HEREDOC 9
# define APPEND 10
# define ERROR 99

# define INFILE 20
# define OUTFILE 21
# define OUTFILEAPPEND 22

typedef struct s_redir
{
	int		infd;
	int		outfd;
}t_redir;

typedef struct s_cmd_tab
{
	char	**cmd_args;
	int		fd[2];
	int		id1;

}t_cmd_tab;

typedef struct s_cmd
{
	t_cmd_tab	*cmd_tab;
	int			nbr_cmd;
	int			status;
}t_commande;

typedef struct s_minishell
{
	char				*str;
	int					state;
	int					redir;
	struct s_minishell	*next;
}t_list;

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);

//minishell_exec
void	exec_v2(char *arg, char **env);

//minishell_free
void	ft_free(char **tab1, char **tab2, char *str);
void	ft_free_double_tab(char **tab);

//minishell_utils
size_t	ft_strlen(const char *str);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
void	ft_print_tab(char **tab);
char	*ft_strdup(char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);

//parsing_dollar
char	*replace_dollar_vars(char *str, char **env);

//parsing_test
int		ft_count_commands(t_list *lst);

int		exec(char **tab, char **env);

#endif
