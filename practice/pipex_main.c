/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:50:21 by eunskim           #+#    #+#             */
/*   Updated: 2023/03/30 21:51:22 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void	second_child_process(int outfile_fd, char *cmd2, char *envp[])
{
	// functions needed:
	// dup2 for fds
	// execve for executing - path, cmd should be parsed and provided
	// close fds
}

void	first_child_process(int infile_fd, char	*cmd1, char *envp[])
{
	// functions needed:
	// dup2 for fds
	// execve for executing - path, cmd should be parsed and provided
	// close fds
}

// first_fork_pid = 0 -> first_child
// first_fork_pid != 0 && second_for_pid == 0 -> second_child

int	pipex(int infile_fd, int outfile_fd, char *argv[], char *envp[])
{
	int		pipe_fds[2];
	int		status;
	pid_t	first_fork_pid;
	pid_t	second_fork_pid;

	pipe(pipe_fds);
	first_fork_pid = fork();
	if (first_fork_pid == -1)
	{
		perror("First fork failed");
		return (2);
	}
	if (first_fork_pid != 0)
	{
		second_fork_pid = fork();
		if (second_fork_pid == -1)
		{
			perror("Second fork failed");
			return (3);
		}
	} // finished forking with error handling
	if (first_fork_pid == 0)
		first_child_process(infile_fd, argv[2], envp);
	if (first_fork_pid != 0 && second_fork_pid == 0)
		second_child_process(outfile_fd, argv[3], envp); // gave tasks to each process
	waitpid(first_fork_pid, &status, 0);
    waitpid(second_fork_pid, &status, 0);
	return (0); // waited for them to be finished and return (0)
}

// How the original shell commands "< file1 cmd1 | cmd2 > file2" behaves:
// When there is no file1, first process will print an error message and close pipe_fds[1]
// When there is no file2, it will create a new file named file2 with permission -rw-r--r-- (644)
// When there is already file2, it will overwrite the file and truncate the original content.
// By overwriting it will not change the permission.
// When needed permission is not given, an error message will be printed.

int	main(int argc, char *argv[], char *envp[])
{
	int	infile_fd;
	int	outfile_fd;

	if (argc != 5)
	{
		printf("Invalid arguments. Usage: ./pipex file1 cmd1 cmd2 file2");
		return (1);
	}
	infile_fd = open(argv[1], O_RDONLY);
	outfile_fd = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (infile_fd == -1 || outfile_fd == -1)
	{
		perror("Open failed");
		return (-1);
	}
	return (pipex(infile_fd, outfile_fd, argv, envp));
}
