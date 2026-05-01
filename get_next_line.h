/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busyigit <busyigit@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 00:56:18 by busyigit          #+#    #+#             */
/*   Updated: 2026/03/14 10:28:20 by busyigit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*gn_read_to_left_str(int fd, char *left_str);
char	*gn_strchr(char *s, int c);
size_t	gn_strlen(char *s);
char	*gn_get_line(char *left_str);
char	*gn_new_left_str(char *left_str);

#endif