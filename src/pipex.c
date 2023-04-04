/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 18:30:37 by eunskim           #+#    #+#             */
/*   Updated: 2023/04/04 20:36:08 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// How the original shell commands "< file1 cmd1 | cmd2 > file2" works:
// When file1 does not exists, first process will print an error message and close pipe_fds[1]
// When file2 does not exists, it will create a new file named file2 with permission -rw-r--r-- (644)
// When there is file2 already, it will overwrite the file and truncate the original content.
// By overwriting it will not change the permission.
// When needed permission is not given, an error message will be printed.

void	second_child_process(char *outfile, char *cmd2, char **envp, int *pipe_fds)
{
	int	outfile_fd;

	outfile_fd = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (outfile_fd == -1)
		error();
	if (close(pipe_fds[1]) == -1)
		error();
	dup2(pipe_fds[0], STDIN_FILENO);
}

void	first_child_process(char *infile, char	*cmd1, char **envp, int *pipe_fds)
{
	int	infile_fd;

	infile_fd = open(infile, O_RDONLY);
	if (infile_fd == -1)
		error_not_exiting();
	if (close(pipe_fds[0]) == -1)
		error_not_exiting();
	dup2(pipe_fds[1], STDOUT_FILENO);
}

void	error_not_exiting(void)
{
	perror("Error");
	return ;
}

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
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
		first_child_process(argv[1], argv[2], envp, pipe_fds);
	ret_pid = fork();
	if (ret_pid == -1)
		error();
	if (ret_pid == 0)
		second_child_process(argv[4], argv[3], envp, pipe_fds);
	if (close(pipe_fds[0]) == -1 || close(pipe_fds[1] == -1))
		error();
	wait(NULL);
	wait(NULL);
	exit(EXIT_SUCCESS);
}
