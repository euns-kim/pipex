/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 18:30:37 by eunskim           #+#    #+#             */
/*   Updated: 2023/04/04 20:15:24 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	second_child_process(char *outfile, char *cmd2, char *envp[])
{
}

void	first_child_process(char *infile, char	*cmd1, char *envp[])
{
}

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		pipe_fds[2];
	pid_t	ret_pid;

	if (argc != 5)
	{
		printf("Invalid arguments. Usage: ./pipex file1 cmd1 cmd2 file2");
		exit(EXIT_FAILURE);
	}
	if (pipe(pipe_fds) == -1)
		error();
	ret_pid = fork();
	if (ret_pid == -1)
		error();
	if (ret_pid == 0)
		first_child_process(argv[1], argv[2], envp);
	ret_pid = fork();
	if (ret_pid == -1)
		error();
	if (ret_pid == 0)
		second_child_process(argv[4], argv[3], envp);
	if (close(pipe_fds[0]) == -1 || close(pipe_fds[1] == -1))
		error();
	wait(NULL);
	wait(NULL);
	exit(EXIT_SUCCESS);
}
