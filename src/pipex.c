/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 18:30:37 by eunskim           #+#    #+#             */
/*   Updated: 2023/04/05 21:01:17 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// How the original shell commands "< file1 cmd1 | cmd2 > file2" works:
// When file1 does not exists, first process will print an error message and close pipe_fds[1]
// When file2 does not exists, it will create a new file named file2 with permission -rw-r--r-- (644)
// When there is file2 already, it will overwrite the file and truncate the original content.
// By overwriting it will not change the permission.
// When needed permission is not given, an error message will be printed.

void	second_child_process(char *outfile, char *cmd2, char **envp, t_data *pipex)
{
	pipex->outfile_fd = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->outfile_fd == -1)
		error("File open error");
	if (close(pipex->pipe_fds[1]) == -1)
		error("Closing pipe end failed");
	dup2(pipex->pipe_fds[0], STDIN_FILENO);
}

int	first_child_process(char *infile, char *cmd1, char **envp, t_data *pipex)
{
	pipex->infile_fd = open(infile, O_RDONLY);
	if (pipex->infile_fd == -1)
	{
		perror("File open error");
		return (1);
	}
	if (close(pipex->pipe_fds[0]) == -1)
	{
		perror("Closing pipe end failed");
		return (1);
	}
	dup2(pipex->pipe_fds[1], STDOUT_FILENO);
}

void	wait_and_error_exit(t_data pipex)
{
	int	wstatus1;
	int	wstatus2;
	int	status_code;

	waitpid(pipex.ret_pid1, &(wstatus1), 0);
	waitpid(pipex.ret_pid2, &(wstatus2), 0);
	if (WIFEXITED(wstatus2))
		status_code = WEXITSTATUS(wstatus2);
	if (status_code != 0)
	{
		errno = status_code;
		error(NULL);
	}
	return ;
}

void	error(char *err_msg)
{
	perror(err_msg);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	pipex;

	if (argc != 5)
	{
		ft_printf("Invalid arguments. Usage: ./pipex file1 cmd1 cmd2 file2");
		exit(EXIT_FAILURE);
	}
	if (pipe(pipex.pipe_fds) == -1)
		error("Pipe function failed");
	pipex.ret_pid1 = fork();
	if (pipex.ret_pid1 == -1)
		error("Failed to create first child process");
	if (pipex.ret_pid1 == 0)
		first_child_process(argv[1], argv[2], envp, &pipex);
	pipex.ret_pid2 = fork();
	if (pipex.ret_pid2 == -1)
		error("Failed to create second child process");
	if (pipex.ret_pid2 == 0)
		second_child_process(argv[4], argv[3], envp, &pipex);
	if (close(pipex.pipe_fds[0]) == -1 || close(pipex.pipe_fds[1] == -1))
		error("Closing pipe end failed");
	wait_and_error_exit(pipex);
	exit(EXIT_SUCCESS);
}
