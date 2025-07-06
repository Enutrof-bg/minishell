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
#include <readline/readline.h> // pour readline etc
#include <readline/history.h> // pour readline etc
#include <sys/types.h>//wait
#include <sys/wait.h>//wait

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);


//minishell_exec
void		exec(char *arg, char **env);

//minishell_free
void	ft_free(char **tab1, char **tab2, char *str);
void	ft_free_double_tab(char **tab);

//minishell_utils
size_t	ft_strlen(const char *str);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
#endif
