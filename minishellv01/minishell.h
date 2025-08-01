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
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <readline/readline.h> // pour readline etc
#include <readline/history.h> // pour readline etc
#include <sys/types.h>//wait
#include <sys/wait.h>//wait

#define SINGLEQUOTE 1
#define DOUBLEQUOTE 2
#define NORMAL 3
#define CMD 4
#define PIPE 5
#define ARG 6
#define INPUT 7
#define OUTPUT 8
#define HEREDOC 9
#define APPEND 10
#define ERROR 99

#define INFILE 20
#define OUTFILE 21
#define OUTFILEAPPEND 22

typedef struct s_redir
{
	int infd;
	int outfd;
}t_redir;

typedef struct s_cmd_tab
{
	char **cmd_args;
	int fd[2];
	int id1;

	int infd;
	int outfd;
}t_cmd_tab;

typedef struct s_cmd
{
	t_cmd_tab *cmd_tab;
	int nbr_cmd;
	int status;
}t_commande;

typedef struct s_minishell
{
	char *str;
	int state;
	int redir;
	struct s_minishell *next;

	// int nbr_cmd;
	// t_cmd_tab *cmd_tab;
}t_list;

typedef struct s_all
{
	t_list		*shell;
	t_commande	*t_cmd;
	t_redir		*t_red;
	char **env;
	int exit_status;
	char *exit_status_char;
}t_all;

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_itoa(int n);

//cd_test.c
int is_builtin(char **tab);
int is_builtin2(char **tab, t_all **all);

//exec_pipe.c  
int	ft_open_pipe(t_commande *t_cmd);
void	ft_close_pipe(t_commande *t_cmd);
void	ft_waitpid(t_commande *t_cmd);
int	ft_dup(int fd0, int fd1);

//minishell_exec
// void		exec(char *arg, char **env);

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
char *ft_strcpy(char *dest, char *src);
int ft_isalnum(char c);
char *get_env_var(char *str, char **env);
char *get_env_name(char *str, int start);
char *replace_dollar_vars(char *str, char **env, t_all *all);
char *replace_dollar_test2(char *str, char **env, t_all *all);

//parsing_double_tab.c
char	**ft_copy_double_tab(char **tab);
char	**ft_add_double_tab(char *str, char **tab);

//parsing_free.c
void	ft_free_double_tab(char **tab);
void	ft_clear(t_list **lst);

//parsing_init.c
int ft_count_commands(t_list *lst);

//parsing_lst_utils.c
t_list	*ft_lst(char *str, int state);
void	ft_lstadd_back(t_list **lst, t_list *new);
void ft_add(t_list **lst, char *str, int state);

//parsing_lst_utils_2.c
int ft_size(t_list *lst);
void ft_print(t_list *lst);
int ft_check(char *str, char c);
void	ft_lstiter_env(t_list **lst, char **env, t_all *all);
void ft_lstiteration(t_all **all, void(*f)(char *));

//parsing_parsing_1.c
int ft_parse_decoupe(char *str, t_list **shell, t_all *all);

//parsing_parsing_2.c
int ft_parse_double_quote(char *str, t_list **shell, int *i, t_all *all);
int ft_parse_singlequote(char *str, t_list **shell, int *i, t_all *all);
char *ft_remove_quote(char *str);
int ft_parse_space(char *str, t_list **shell, int *i, t_all *all);

//parsing_parsing_3.c
int ft_parse_pipe(char *str, t_list **shell, int *i);
int ft_parse_out(char *str, t_list **shell, int *i);
int ft_parse_in(char *str, t_list **shell, int *i);

//parsing_redir.c
int ft_create_fd(t_list **shell, t_redir **t_red);

// //parsing_test
// int ft_count_commands(t_list *lst);

//parsing_triple_tab.c
int ft_print_triple_tab(t_commande *t_cmd);
int ft_set_triple_tab_null(t_commande *t_cmd);
int ft_create_triple_tab(t_list **shell ,t_commande **t_cmd);

//pipex_path
void	ft_err(char *msg1, char *msg2);
int	exec(char **tab, char **env);

#endif
