/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:05:27 by eunskim           #+#    #+#             */
/*   Updated: 2023/02/01 12:12:00 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/*
 * @brief : Locates the first occurence of c
 *	in the string pointed by s.
 * @return : (int) The index + 1 where c is found in the string.
 * 	And 0 when no c is found in the whole string.  
 */

ssize_t	gnl_strchr(const char *s, int c)
{
	ssize_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i])
	{
		if ((char) c == s[i])
			return (i + 1);
		i++;
	}
	return (0);
}

/*
 * @brief : Allocates and returns a new string,
 *	which is the result of the concatenation of s1 and s2.
 * @param : s1 (the prefix string) and s2 (the suffix string)
 * @return : The new string. NULL if allocation fails.
 * @details : (1) If s1 is a null pointer, duplicate the string s2.
 * 	(2) Free s1 before returning the newstr.
 */

char	*gnl_strjoin(char *s1, const char *s2)
{
	char	*newstr;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s1 == NULL)
		return (gnl_strdup(s2));
	newstr = malloc(sizeof(char) * (gnl_strlen(s1) + gnl_strlen(s2) + 1));
	if (newstr == NULL)
		return (NULL);
	while (s1[i])
	{
		newstr[j++] = s1[i++];
	}
	i = 0;
	while (s2[i])
	{
		newstr[j++] = s2[i++];
	}
	newstr[j] = '\0';
	free(s1);
	return (newstr);
}

/*
 * @brief : Allocates and returns a new string,
 * which is the duplication of the s1.
 * @param : s1 (the string to be duplicated)
 * @return : The new string. NULL if allocation fails.
 */

char	*gnl_strdup(const char *s1)
{
	char	*p;
	size_t	size;

	size = gnl_strlen(s1) + 1;
	p = (char *) malloc(sizeof(char) * size);
	if (p == NULL)
		return (NULL);
	gnl_memcpy(p, s1, size);
	return (p);
}

/*
 * @brief : Copies n bytes from memory area src to dst
 * @details : (1) No typecasting to char *
 * 	(2) Set null terminator at the end.
 */

char	*gnl_memcpy(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

/* subfunction */

size_t	gnl_strlen(const char *s)
{
	size_t	strlen;

	strlen = 0;
	while (s[strlen] != '\0')
		strlen++;
	return (strlen);
}
