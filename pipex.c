/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 18:30:37 by eunskim           #+#    #+#             */
/*   Updated: 2023/03/30 22:32:04 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void	second_child_process(char *outfile, char *cmd2, char *envp[])
{
	// open for fds
	// functions needed:
	// dup2 for fds
	// execve for executing - path, cmd should be parsed and provided
	// close fds
}

void	first_child_process(char *infile, char	*cmd1, char *envp[])
{
	// open for fds
	// functions needed:
	// dup2 for fds
	// execve for executing - path, cmd should be parsed and provided
	// close fds
}

int	main(int argc, char *argv[], char *envp[])
{
	int		pipe_fds[2];
	int		status;
	pid_t	ret_pid;

	if (argc != 5)
	{
		printf("Invalid arguments. Usage: ./pipex file1 cmd1 cmd2 file2");
		return (1);
	}
	if (pipe(pipe_fds) == -1)
	{
		perror("Pipe function failed");
		return (2);
	}
	ret_pid = fork();
	if (ret_pid == -1)
	{
		perror("First fork failed");
		return (3);
	}
	if (ret_pid == 0)
		first_child_process(argv[1], argv[2], envp);
	ret_pid = fork();
	if (ret_pid == -1)
	{
		perror("Second fork failed");
		return (4);
	}
	if (ret_pid == 0)
		second_child_process(argv[4], argv[3], envp);
	// waiting for the processes to end
	return (0);
}
