/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_triple_tab_heredoc_2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 13:21:14 by kevwang           #+#    #+#             */
/*   Updated: 2025/08/14 13:21:14 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Configuration des signaux et terminal pour heredoc
void	ft_setup_heredoc_env(t_all *all)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	if (tcgetattr(STDIN_FILENO, &all->term) == 0)
	{
		all->term.c_lflag &= ~0001000;
		tcsetattr(STDIN_FILENO, TCSANOW, &all->term);
	}
}

// Préparation du fichier temporaire pour heredoc
void	ft_prepare_temp_file(t_commande *t_cmd, int i)
{
	if (access("temp", F_OK) == 0)
	{
		close(t_cmd->cmd_tab[i].infd);
		unlink("temp");
	}
	t_cmd->cmd_tab[i].infd = open("temp", O_WRONLY | O_CREAT | O_APPEND, 0644);
}

// Lecture et écriture des lignes heredoc
void	ft_process_heredoc_lines(t_list *shell, t_commande *t_cmd, int i)
{
	char	*line;

	line = get_next_line(0);
	while (line && g_sigvaleur == 0)
	{
		if (ft_strncmp(line, shell->str, ft_strlen(shell->str)) == 0)
		{
			free(line);
			break ;
		}
		write(t_cmd->cmd_tab[i].infd, line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
}

// Gestion du processus enfant heredoc
int	ft_handle_heredoc_child(t_list *shell, t_commande *t_cmd, t_all *all, int i)
{
	ft_setup_heredoc_env(all);
	t_cmd->cmd_tab[i].heredoc++;
	ft_prepare_temp_file(t_cmd, i);
	ft_process_heredoc_lines(shell, t_cmd, i);
	close(t_cmd->cmd_tab[i].infd);
	exit(0);
}
