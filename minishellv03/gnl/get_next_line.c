/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:18:52 by kevwang           #+#    #+#             */
/*   Updated: 2025/05/05 17:18:54 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_str_return(char *str)
{
	int		i;
	int		j;
	char	*newstr;

	i = 0;
	j = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		i++;
	newstr = malloc(sizeof(char) * (i + 1));
	if (!newstr)
		return (NULL);
	while (j < i)
	{
		newstr[j] = str[j];
		j++;
	}
	newstr[j] = '\0';
	return (newstr);
}

char	*ft_str_reste(char *str)
{
	int		i;
	int		j;
	char	*newstr;

	i = 0;
	j = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	while (str[i + j] != '\0')
		j++;
	newstr = malloc(sizeof(char) * (j + 1));
	if (!newstr)
		return (NULL);
	j = 0;
	while (str[i + j])
	{
		newstr[j] = str[i + j];
		j++;
	}
	newstr[j] = '\0';
	return (newstr);
}

char	*ft_read(int fd, char *str)
{
	char	*temp;
	char	*charread;
	int		readfd;

	charread = ft_calloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!charread)
		return (NULL);
	readfd = read(fd, charread, BUFFER_SIZE);
	while (readfd > 0)
	{
		charread[readfd] = '\0';
		temp = ft_strjoin_gnl(str, charread);
		if (!temp)
			return (NULL);
		free(str);
		str = temp;
		if (ft_check_gnl(charread, '\n') == 1)
			break ;
		readfd = read(fd, charread, BUFFER_SIZE);
	}
	free(charread);
	return (ft_erreur(readfd, str));
}

char	*ft_reste(char *str)
{
	char	*temp;

	temp = ft_str_reste(str);
	if (!temp)
		return (NULL);
	free(str);
	str = temp;
	return (str);
}

char	*get_next_line(int fd)
{
	static char		*str;
	char			*strreturn;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	if (!str)
	{
		str = ft_calloc(sizeof(char) * 1);
		if (!str)
			return (NULL);
	}
	str = ft_read(fd, str);
	if (!str)
		return (NULL);
	strreturn = ft_str_return(str);
	if (!strreturn)
		return (NULL);
	str = ft_reste(str);
	if (!str)
		return (NULL);
	if (str && str[0] == '\0')
		return (free(str), str = NULL, strreturn);
	return (strreturn);
}
