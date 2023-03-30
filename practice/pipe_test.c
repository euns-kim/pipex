/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:28:39 by eunskim           #+#    #+#             */
/*   Updated: 2023/03/30 16:29:20 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
                                                                          
int	main(void)
{
	int	pipefd[2];
	pipe(pipefd);
	pid_t	child_pid = fork();
	if (child_pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		printf("this is child\n");
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		char	*buff = calloc(100, sizeof(char));
		read(0, buff, 13);
		printf("this is parent, read from pipe: %s\n", buff);
		free(buff);
	}
	return (0);
}