/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 21:58:53 by eunskim           #+#    #+#             */
/*   Updated: 2023/02/01 12:11:26 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* main function */

char	*get_next_line(int fd)
{
	char		*line;
	static char	*backup;
	ssize_t		index;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	backup = read_next_line(fd, backup);
	line = get_first_line(&index, backup);
	backup = backup_the_rest(&index, backup);
	return (line);
}

/*
 * @brief : Uses read() function to read next line of the file,
 *	when there is no line left in the current backup.
 * @param : int fd and the address of the static char *
 * @details : Check the return value of the read() function,
 *	and take consequences needed for each case.
 */

char	*read_next_line(int fd, char *backup)
{
	char	*buff;
	ssize_t	read_size;

	buff = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buff == NULL)
		return (NULL);
	while (gnl_strchr(backup, '\n') == 0)
	{
		read_size = read(fd, buff, BUFFER_SIZE);
		if (read_size == -1)
		{
			free(buff);
			free(backup);
			return (NULL);
		}
		if (read_size == 0)
			break ;
		buff[read_size] = '\0';
		backup = gnl_strjoin(backup, buff);
	}
	free(buff);
	return (backup);
}

/*
 * @brief : Allocates and returns a new string,
 *	which is the first line detected in the backup.
 */

char	*get_first_line(ssize_t *index, char *backup)
{
	char	*line;

	if (backup == NULL)
		return (NULL);
	*index = gnl_strchr(backup, '\n');
	if (*index == 0)
		*index = gnl_strlen(backup);
	if (*index == 0)
	{
		free(backup);
		return (NULL);
	}
	line = (char *) malloc(sizeof(char) * (*index + 1));
	if (line == NULL)
		return (NULL);
	gnl_memcpy(line, backup, *index + 1);
	return (line);
}

/*
 * @brief : Trims the first line from the backup,
 *	allocates a new string to save the rest of it.
 */

char	*backup_the_rest(ssize_t *index, char *backup)
{	
	size_t	size;
	char	*new_backup;

	if (backup == NULL)
		return (NULL);
	size = gnl_strlen(backup) - *index + 1;
	if (size == 1)
	{
		free(backup);
		return (NULL);
	}
	new_backup = (char *) malloc (sizeof(char) * size);
	if (new_backup == NULL)
		return (NULL);
	gnl_memcpy(new_backup, backup + *index, size);
	free(backup);
	return (new_backup);
}
