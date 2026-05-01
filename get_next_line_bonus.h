/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busyigit <busyigit@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 01:47:20 by busyigit          #+#    #+#             */
/*   Updated: 2026/03/14 10:28:13 by busyigit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

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