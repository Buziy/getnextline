/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busyigit <busyigit@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 01:49:54 by busyigit          #+#    #+#             */
/*   Updated: 2026/03/12 23:32:31 by busyigit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*gn_realloc(char *left_str, char *buff, size_t *total, size_t need)
{
	char	*str;
	size_t	l;
	size_t	i;

	l = gn_strlen(left_str);
	if (*total == 0)
		*total = 1;
	while (*total < need)
		*total *= 2;
	str = malloc(*total);
	if (!str)
		return (free(left_str), NULL);
	i = -1;
	while (left_str && left_str[++i])
		str[i] = left_str[i];
	i = -1;
	while (buff[++i])
		str[l + i] = buff[i];
	str[l + i] = '\0';
	free(left_str);
	return (str);
}

static char	*gn_append(char *left_str, char *buff, size_t *total)
{
	size_t	l;
	size_t	b;
	size_t	i;

	l = gn_strlen(left_str);
	b = gn_strlen(buff);
	if (*total < l + b + 1)
		return (gn_realloc(left_str, buff, total, l + b + 1));
	i = 0;
	while (i < b)
	{
		left_str[l + i] = buff[i];
		i++;
	}
	left_str[l + b] = '\0';
	return (left_str);
}

static char	*gn_process(char *left_str, char *buff, size_t *total, int rd)
{
	buff[rd] = '\0';
	left_str = gn_append(left_str, buff, total);
	return (left_str);
}

char	*gn_read_to_left_str(int fd, char *left_str)
{
	char	*buff;
	int		rd_bytes;
	size_t	total;

	total = 0;
	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (free(left_str), NULL);
	rd_bytes = 1;
	while (!gn_strchr(left_str, '\n') && rd_bytes > 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
			return (free(buff), free(left_str), NULL);
		if (rd_bytes > 0)
			left_str = gn_process(left_str, buff, &total, rd_bytes);
		if (!left_str)
			return (free(buff), NULL);
	}
	free(buff);
	return (left_str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*left_str[1024];

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	left_str[fd] = gn_read_to_left_str(fd, left_str[fd]);
	if (!left_str[fd])
		return (NULL);
	line = gn_get_line(left_str[fd]);
	if (!line)
	{
		free(left_str[fd]);
		left_str[fd] = NULL;
		return (NULL);
	}
	left_str[fd] = gn_new_left_str(left_str[fd]);
	return (line);
}
