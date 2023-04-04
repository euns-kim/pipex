/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:05:23 by eunskim           #+#    #+#             */
/*   Updated: 2023/02/01 12:11:36 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

/* main functions */
char	*get_next_line(int fd);
char	*read_next_line(int fd, char *backup);
char	*get_first_line(ssize_t *index, char *backup);
char	*backup_the_rest(ssize_t *index, char *backup);

/* util funtions */
ssize_t	gnl_strchr(const char *s, int c);
char	*gnl_strjoin(char *s1, const char *s2);
char	*gnl_strdup(const char *s1);
char	*gnl_memcpy(char *dst, const char *src, size_t n);
size_t	gnl_strlen(const char *s);

#endif