/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:38:30 by kevwang           #+#    #+#             */
/*   Updated: 2025/07/18 11:38:32 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_exec_commande(t_commande *t_cmd, t_redir *t_red, t_all *all, char **env)
{
	int i;
	(void)all;
	i = 0;
	while (i < t_cmd->nbr_cmd)
	{
		t_cmd->cmd_tab[i].id1 = fork();

		if (t_cmd->cmd_tab[i].id1 == 0)
		{
			if (i == 0)
			{
				if (t_red->infd >= 0)
					dup2(t_red->infd, 0);
				if (t_cmd->nbr_cmd > 1)
					dup2(t_cmd->cmd_tab[i].fd[1], 1);
				else if (t_red->outfd >= 0)
					dup2(t_red->outfd, 1);
			}
			else if (i == t_cmd->nbr_cmd - 1)
			{
				dup2(t_cmd->cmd_tab[i - 1].fd[0], 0);
				if (t_red->outfd >= 0)
					dup2(t_red->outfd, 1);
			}
			else
			{
				dup2(t_cmd->cmd_tab[i - 1].fd[0], 0);
				dup2(t_cmd->cmd_tab[i].fd[1], 1);
			}
			ft_close_pipe(t_cmd);
			// if (ft_strncmp(t_cmd->cmd_tab[i].cmd_args[0], "echo", 4) == 0
			// 	&& ft_strncmp(t_cmd->cmd_tab[i].cmd_args[1], "$?", 2) == 0)
			// {
			// 	all->exit_status_char = ft_itoa(all->exit_status);
			// 	free(all->exit_status_char);
			// }
			// else
			if (exec(t_cmd->cmd_tab[i].cmd_args, env) == -1)
				exit(127);
			exit(1);
		}
		i++;
	}
	return (0);
}


//caca parsing_test.c pipex_path.c parsing_dollar.c minishell_utils.c ft_strjoin.c ft_split.c ft_itoa.c -lreadline -o minishell
int main(int argc, char **argv, char **env)
{
	(void)argv;
	t_all *all;
	char *str;

	if (argc == 1)
	{
		all = malloc(sizeof(t_all));
		while (1)
		{
			all->shell = malloc(sizeof(t_list));
			if (!all->shell)
				return (1);
			all->shell = NULL;
			str = readline("CacaTest >");
			add_history(str);

			if (ft_strncmp(str, "exit", 4) == 0)
			{
				free(str);
				free(all->shell);
				// rl_clear_history();
				// break ;
				exit(0);
			}

			// printf("    input:%s\n", str);
			// char *new_str = replace_dollar_vars(str, env, all);
			// printf("new_input:%s\n", new_str);

			// new_str = ft_remove_quote(new_str);
			// printf("new_input:%s\n", new_str);
			// int i = 0;
			// while (i < new_str[i])
			// {
				
			// 	i++;
			// }

			// new_str2 = ft_remove_quote(new_str);

			//Parse_decoupe bah elle decoupe l'input en liste chaine
			ft_parse_decoupe(str, &all->shell);
			
			ft_lstiter_env(&all->shell, env, all);
	ft_print(all->shell);

			//Compte le nombre de commande
			all->t_cmd = malloc(sizeof(t_commande));
			all->t_cmd->nbr_cmd = ft_count_commands(all->shell);
			// printf("nbr commande: %d\n", t_cmd->nbr_cmd);

			//Creation des redirections
			all->t_red = malloc(sizeof(t_redir));
			all->t_red->infd = -1;

			all->t_red->outfd = -1;
			ft_create_fd(&all->shell, &all->t_red);
			all->t_cmd->cmd_tab = malloc(sizeof(t_cmd_tab) * all->t_cmd->nbr_cmd);
			if (!all->t_cmd->cmd_tab)
				return (1);

			//Creation des doubles tableaux pour les commandes
			ft_set_triple_tab_null(all->t_cmd);
			ft_create_triple_tab(&all->shell, &all->t_cmd);
	ft_print_triple_tab(all->t_cmd);

			//Execution
			ft_open_pipe(all->t_cmd);
			ft_exec_commande(all->t_cmd, all->t_red, all,env);
			ft_close_pipe(all->t_cmd);
			ft_waitpid(all->t_cmd);

			//exit code
			// int exit_status = 0;
			if (WIFEXITED(all->t_cmd->status))
				all->exit_status = WEXITSTATUS(all->t_cmd->status);
			// printf("exit:%d\n", all->exit_status);

			//free
			int j = 0;
			while (j < all->t_cmd->nbr_cmd && all->t_cmd->cmd_tab[j].cmd_args)
			{
				ft_free_double_tab(all->t_cmd->cmd_tab[j].cmd_args);
				j++;
			}
			free(all->t_cmd->cmd_tab);
			free(all->t_cmd);
			free(all->t_red);
			free(str);
			ft_clear(&all->shell);
			free(all->shell);
		}
		free(all);
	}
	return (0);
	// char **copy = ft_copy_double_tab(argv);
	// ft_print_tab(copy);

	// copy = ft_add_double_tab("test", copy);
	// ft_print_tab(copy);
	// ft_free_double_tab(copy);



	// char *r1;

	// while(1)
	// {
	// 	r1 = readline("test >");

	// 	add_history(r1);


	// }
}


/*
	
// void	ft_free_double_tab(char **tab)
// {
// 	int	i;

// 	i = 0;
// 	while (tab[i])
// 	{
// 		free(tab[i]);
// 		i++;
// 	}
// 	free(tab);
// }

// char	**ft_copy_double_tab(char **tab)
// {
// 	int		i;
// 	int		j;
// 	char	**newtab;

// 	i = 0;
// 	j = 0;
// 	while (tab[i])
// 		i++;
// 	newtab = malloc(sizeof(char *) * (i + 1));
// 	i = 0;
// 	while (tab[i])
// 	{
// 		newtab[i] = ft_strdup(tab[i]);
// 		i++;
// 	}
// 	newtab[i] = 0;
// 	return (newtab);
// }

// char **ft_add_double_tab(char *str, char **tab)
// {
// 	int		i;
// 	int		j;
// 	char	**newtab;

// 	i = 0;
// 	j = 0;
// 	if (tab == NULL)
// 	{
// 		newtab = malloc(sizeof(char *) * 2);
// 		newtab[0] = ft_strdup(str);
// 		newtab[1] = 0;
// 		return (newtab);
// 	}
// 	while (tab[i])
// 		i++;
// 	newtab = malloc(sizeof(char *) * (i + 2));
// 	i = 0;
// 	while (tab[i])
// 	{
// 		newtab[i] = ft_strdup(tab[i]);
// 		i++;
// 	}
// 	newtab[i] = ft_strdup(str);
// 	i++;
// 	newtab[i] = 0;
// 	ft_free_double_tab(tab);
// 	return (newtab);
// }

// t_list	*ft_lst(char *str, int state)
// {
// 	t_list	*newlist;

// 	newlist = malloc(sizeof(t_list));
// 	if (!newlist)
// 	{
// 		return (NULL);
// 	}
// 	newlist->str = ft_strdup(str);
// 	newlist->state = state;
// 	newlist->next = NULL;
// 	return (newlist);
// }

// void	ft_lstadd_back(t_list **lst, t_list *new)
// {
// 	t_list	*temp;

// 	temp = *lst;
// 	if (*lst == NULL)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	while ((*lst)->next != NULL)
// 	{
// 		*lst = (*lst)->next;
// 	}
// 	(*lst)->next = new;
// 	*lst = temp;
// }

// void ft_add(t_list **lst, char *str, int state)
// {
// 	if (!(*lst))
// 	{
// 		(*lst) = ft_lst(str, state);
// 		return ;
// 	}
// 	t_list *temp = *lst;
// 	while ((*lst)->next)
// 	{
// 		(*lst) = (*lst)->next;
// 	}
// 	(*lst)->next = ft_lst(str, state);
// 	// (*lst)->next->state = state;
// 	(*lst) = temp;
// }

// int ft_size(t_list *lst)
// {
// 	int size = 0;
// 	while (lst)
// 	{
// 		size++;
// 		lst = lst->next;
// 	}
// 	return size;
// }

// void ft_print(t_list *lst)
// {
// 	if (lst)
// 	{
// 		int size = ft_size(lst);
// 		// printf("size:%d\n", size);
// 		int i = 0;
// 		while (i < size)
// 		{
// 			// printf("%d:%s:%d:%d\n", i,lst->str, lst->state, lst->redir);
// 			printf("%d:%s:%d\n", i,lst->str, lst->state);
// 			// printf("%d:'%s'\n", i,lst->str);
// 			lst = lst->next;
// 			i++;
// 		}
// 		// printf("%d\n", lst->val);
// 	}
// }

// void ft_print_tab(char **tab)
// {
// 	int i = 0;
// 	if (tab)
// 	{
// 		while (tab[i])
// 		{
// 			printf("%s\n", tab[i]);
// 			i++;
// 		}
// 	}
// }

// void	ft_clear(t_list **lst)
// {
// 	t_list	*del;

// 	while (*lst != NULL)
// 	{
// 		del = *lst;
// 		*lst = (*lst)->next;
// 		free(del->str);
// 		free(del);
// 	}
// 	*lst = NULL;
// }

// int ft_check(char *str, char c)
// {
// 	int i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == c)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// void	ft_lstiter_env(t_list **lst, char **env, t_all *all)
// {
// 	t_list *temp;
// 	char *new_str;

// 	temp = *lst;
// 	while (*lst != NULL)
// 	{
// 		if ((*lst)->state == DOUBLEQUOTE || (*lst)->state == NORMAL)
// 		{
// 			new_str = replace_dollar_vars((*lst)->str, env, all);
// 			if (new_str)
// 			{
// 				free((*lst)->str);
// 				(*lst)->str = new_str;
// 			}
// 		}
// 		(*lst)->redir = -1;
// 		if ((*lst)->state == INPUT)
// 			(*lst)->next->state = INFILE;
// 		if ((*lst)->state == OUTPUT)
// 			(*lst)->next->state = OUTFILE;
// 		if ((*lst)->state == APPEND)
// 			(*lst)->next->state = OUTFILEAPPEND;
// 		(*lst) = (*lst)->next;
// 	}
// 	*lst = temp;
// }

// int ft_count_commands(t_list *lst)
// {
// 	int count;

// 	count = 1;
// 	while (lst)
// 	{
// 		if (lst->state == PIPE)
// 			count++;
// 		lst = lst->next;
// 	}
// 	return (count);
// }

// int	ft_open_pipe(t_commande *t_cmd)
// {
// 	int	i;

// 	i = 0;
// 	while (i < t_cmd->nbr_cmd - 1)
// 	{
// 		if (pipe(t_cmd->cmd_tab[i].fd) == -1)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// void	ft_close_pipe(t_commande *t_cmd)
// {
// 	int	i;

// 	i = 0;
// 	while (i < t_cmd->nbr_cmd - 1)
// 	{
// 		close(t_cmd->cmd_tab[i].fd[0]);
// 		close(t_cmd->cmd_tab[i].fd[1]);
// 		i++;
// 	}
// }

// void	ft_waitpid(t_commande *t_cmd)
// {
// 	int	j;

// 	j = 0;
// 	while (j < t_cmd->nbr_cmd)
// 	{
// 		waitpid(t_cmd->cmd_tab[j].id1, &t_cmd->status, 0);
// 		j++;
// 	}
// }

// int	ft_dup(int fd0, int fd1)
// {
// 	if (dup2(fd0, 0) == -1)
// 		return (-1);
// 	if (dup2(fd1, 1) == -1)
// 		return (-1);
// 	return (0);
// }

// int ft_parse_double_quote(char *str, t_list **shell, int *i)
// {
// 	int j;
// 	char *temp;

// 	j = 0;
// 	while (str[*i + j] != '"' && str[*i + j] != '\0')
// 		j++;
// 	if (j > 0)
// 	{
// 		temp = ft_substr(str, *i, j);
// 		// tab = ft_add_double_tab(temp, tab);
// 		ft_add(shell, temp, DOUBLEQUOTE);
// 		// printf("double:%s i:%d j:%d\n", temp, i, j);
// 		free(temp);
// 	}
// 	*i = *i + j;
// 	if (str[*i] == '"')
// 		(*i)++;
// 	return (0);
// }

// int ft_parse_singlequote(char *str, t_list **shell, int *i)
// {
// 	int j;
// 	char *temp;

// 	j = 0;
// 	while (str[*i + j] != '\'' && str[*i + j] != '\0')
// 		j++;
// 	if (j > 0)
// 	{
// 		temp = ft_substr(str, *i, j);
// 		// tab = ft_add_double_tab(temp, tab);
// 		ft_add(shell, temp, SINGLEQUOTE);
// 		// printf("single:%s i:%d j:%d\n", temp, i, j);
// 		free(temp);
// 	}
// 	*i = *i + j;
// 	if (str[*i] == '\'')
// 		(*i)++;
// 	j = 0;
// 	return (0);
// }

// int ft_parse_pipe(char *str, t_list **shell, int *i)
// {
// 	int j;
// 	char *temp;

// 	j = 0;
// 	j++;
// 	while (str[*i + j] == '|' && str[*i + j] != '\0')
// 		j++;
// 	if (j > 0)
// 	{
// 		temp = ft_substr(str, *i, j);
// 		// tab = ft_add_double_tab(temp, tab);
// 		if (ft_strlen(temp) == 1)
// 			ft_add(shell, temp, PIPE);
// 		else
// 			ft_add(shell, temp, ERROR);
// 		// printf("single:%s i:%d j:%d\n", temp, i, j);
// 		free(temp);
// 	}
// 	*i = *i + j;
// 	if (str[*i] == '|')
// 		(*i)++;
// 	j = 0;
// 	return (0);
// }

// int ft_parse_out(char *str, t_list **shell, int *i)
// {
// 	int j;
// 	char *temp;

// 	j = 0;
// 	j++;
// 	while (str[*i + j] == '>' && str[*i + j] != '\0')
// 		j++;
// 	if (j > 0)
// 	{
// 		temp = ft_substr(str, *i, j);
// 		// tab = ft_add_double_tab(temp, tab);
// 		if (ft_strlen(temp) == 1)
// 			ft_add(shell, temp, OUTPUT);
// 		else if (ft_strlen(temp) == 2)
// 			ft_add(shell, temp, APPEND);
// 		else
// 			ft_add(shell, temp, ERROR);
// 		// printf("single:%s i:%d j:%d\n", temp, i, j);
// 		free(temp);
// 	}
// 	*i = *i + j;
// 	if (str[*i] == '>')
// 		(*i)++;
// 	j = 0;
// 	return (0);
// }

// int ft_parse_in(char *str, t_list **shell, int *i)
// {
// 	int j;
// 	char *temp;

// 	j = 0;
// 	j++;
// 	while (str[*i + j] == '<' && str[*i + j] != '\0')
// 		j++;
// 	if (j > 0)
// 	{
// 		temp = ft_substr(str, *i, j);
// 		// tab = ft_add_double_tab(temp, tab);
// 		if (ft_strlen(temp) == 1)
// 			ft_add(shell, temp, INPUT);
// 		else if (ft_strlen(temp) == 2)
// 			ft_add(shell, temp, HEREDOC);
// 		else
// 			ft_add(shell, temp, ERROR);
// 		// printf("single:%s i:%d j:%d\n", temp, i, j);
// 		free(temp);
// 	}
// 	*i = *i + j;
// 	if (str[*i] == '<')
// 		(*i)++;
// 	j = 0;
// 	return (0);
// }

// char *ft_remove_quote(char *str)
// {
// 	int i;
// 	int j;
// 	char *new;
// 	int insinglequote;
// 	int indoublequote;

// 	i = 0;
// 	j = 0;
// 	insinglequote = 0;
// 	indoublequote = 0;
// 	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
// 	while (str[i])
// 	{
// 		if (str[i] == '"' && !insinglequote)
// 		{
// 			indoublequote = !indoublequote;
// 			// j++;
// 		}
// 		else if (str[i] == '\'' && !indoublequote)
// 		{
// 			insinglequote = !insinglequote;
// 			// j++;
// 		}
// 		else
// 		{
// 			new[j] = str[i];
// 			j++;
// 		}
// 		i++;
// 	}
// 	new[i] = '\0';
// 	return (new);
// }

// int ft_parse_space(char *str, t_list **shell, int *i)
// {
// 	int j;
// 	int state;
// 	char *temp;
// 	char *temp2;
// 	int insinglequote;
// 	int indoublequote;

// 	insinglequote = 0;
// 	indoublequote = 0;
// 	j = 0;
// 	state = NORMAL;
// 	while (str[*i + j] != ' ' && str[*i + j] != '"' && str[*i + j] != '\''
// 		&& str[*i + j] != '|' && str[*i + j] != '\0')
// 	{
// 		// if (str[*i +j] == '"' && !insinglequote)
// 		// {
// 		// 	indoublequote = !indoublequote;
// 		// 	if (indoublequote)
// 		// 	// j++;
// 		// }
// 		// else if (str[*i +j] == '\'' && !indoublequote)
// 		// {
// 		// 	insinglequote = !insinglequote;
// 		// 	// j++;
// 		// }
// 		j++;
// 	}
// 	if (j > 0)
// 	{
// 		temp = ft_substr(str, *i, j);

// 		temp2 = ft_remove_quote(temp);
// 		// tab = ft_add_double_tab(temp, tab);
// 		ft_add(shell, temp2, state);
// 		// printf("space:%s i:%d j:%d\n", temp, i, j);
// 		free(temp);
// 		free(temp2);
// 	}
// 	*i = *i + j;
// 	j = 0;
// 	return (0);
// }

// int ft_parse_decoupe(char *str, t_list **shell)
// {
// 	int i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == ' ')
// 			i++;
// 		if (str[i] == '"')
// 		{
// 			i++;
// 			ft_parse_double_quote(str, shell, &i);
// 		}
// 		else if (str[i] == '\'')
// 		{
// 			i++;
// 			ft_parse_singlequote(str, shell, &i);
// 		}
// 		else if (str[i] == '|')
// 		{
// 			ft_parse_pipe(str, shell, &i);
// 		}
// 		else if (str[i] == '>')
// 		{
// 			ft_parse_out(str, shell, &i);
// 		}
// 		else if (str[i] == '<')
// 		{
// 			ft_parse_in(str, shell, &i);
// 		}
// 		else
// 		{
// 			ft_parse_space(str, shell, &i);
// 		}
// 	}
// 	return (0);
// }

// int ft_create_fd(t_list **shell, t_redir **t_red)
// {
// 	t_list *temp;

// 	temp = *shell;
// 	while (*shell)
// 	{
// 		// printf("fd state%d\n", shell->state);
// 		if ((*shell)->state == INFILE)
// 		{
// 			(*t_red)->infd = open((*shell)->str, O_RDONLY, 0644);
// 			if ((*t_red)->infd < 0)
// 				perror("infd error");
// 		}
// 		if ((*shell)->state == OUTFILE)
// 			(*t_red)->outfd = open((*shell)->str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
// 		if ((*shell)->state == OUTFILEAPPEND)
// 			(*t_red)->outfd = open((*shell)->str, O_WRONLY | O_APPEND | O_CREAT, 0644);
// 		// printf("fd:%d\n", (*t_red)->infd);
// 		(*shell) = (*shell)->next;
// 	}
// 	(*shell) = temp;
// 	// printf("infd:%d outfd:%d\n", (*t_red)->infd, (*t_red)->outfd);
// 	return (0);
// }

// int ft_init()
// {

// }

// int ft_print_triple_tab(t_commande *t_cmd)
// {
// 	int j;

// 	j = 0;
// 	while (j < t_cmd->nbr_cmd)
// 	{
// 		if (t_cmd->cmd_tab[j].cmd_args)
// 		{
// 			printf("tab:%d\n", j);
// 			ft_print_tab(t_cmd->cmd_tab[j].cmd_args);
// 		}
// 		j++;
// 	}
// 	return (0);
// }

// int ft_set_triple_tab_null(t_commande *t_cmd)
// {
// 	int i = 0;
// 	while (i < t_cmd->nbr_cmd)
// 	{
// 		t_cmd->cmd_tab[i].cmd_args = NULL;
// 		i++;
// 	}
// 	return (0);
// }

// int ft_create_triple_tab(t_list **shell ,t_commande **t_cmd)
// {
// 	int i = 0;

// 	t_list *temp = *shell;
// 	while (*shell != NULL)
// 	{
// 		if ((*shell)->state == NORMAL || (*shell)->state == DOUBLEQUOTE || (*shell)->state == SINGLEQUOTE)
// 			(*t_cmd)->cmd_tab[i].cmd_args = ft_add_double_tab((*shell)->str, (*t_cmd)->cmd_tab[i].cmd_args);
// 		if ((*shell)->state == PIPE)
// 			i++;
// 		(*shell) = (*shell)->next;
// 	}
// 	(*shell) = temp;
// 	return (0);
// }

*/