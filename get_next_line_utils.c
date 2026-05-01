/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busyigit <busyigit@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 02:50:47 by busyigit          #+#    #+#             */
/*   Updated: 2026/03/14 08:45:20 by busyigit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gn_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*gn_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char) c)
			return (s + i);
		i++;
	}
	return (NULL);
}

char	*gn_get_line(char *left_str)
{
	int		len;
	char	*line;

	if (!left_str || !left_str[0])
		return (NULL);
	len = 0;
	while (left_str[len] && left_str[len] != '\n')
		len++;
	if (left_str[len] == '\n')
		len++;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	len = 0;
	while (left_str[len] && left_str[len] != '\n')
	{
		line[len] = left_str[len];
		len++;
	}
	if (left_str[len] == '\n')
		line[len++] = '\n';
	line[len] = '\0';
	return (line);
}

char	*gn_new_left_str(char *left_str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	while (left_str[i] && left_str[i] != '\n')
		i++;
	if (!left_str[i] || !left_str[i + 1])
	{
		free(left_str);
		return (NULL);
	}
	i++;
	new = malloc(gn_strlen(left_str + i) + 1);
	if (!new)
		return (free(left_str), NULL);
	j = 0;
	while (left_str[i])
		new[j++] = left_str[i++];
	new[j] = '\0';
	free(left_str);
	return (new);
}
