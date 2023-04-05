/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 18:30:37 by eunskim           #+#    #+#             */
/*   Updated: 2023/04/05 21:52:13 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// How the original shell commands "< file1 cmd1 | cmd2 > file2" works:
// When file1 does not exists, first process will print an error message and close pipe_fds[1]
// When file2 does not exists, it will create a new file named file2 with permission -rw-r--r-- (644)
// When there is file2 already, it will overwrite the file and truncate the original content.
// By overwriting it will not change the permission.
// When needed permission is not given, an error message will be printed.

int	execute(char *cmd, char **env)
{
	char	**cmd_args = get_cmd_args(cmd);
	char	*path = get_path(cmd_args[0], env);
	return (execve(path, cmd_args, env));
}

int	second_child_process(char *outfile, char *cmd2, char **env, t_data *pipex)
{
	pipex->outfile_fd = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->outfile_fd == -1)
		error_exit("File open error");
	dup2(pipex->pipe_fds[0], STDIN_FILENO);
	close_pipe_fds(pipex);
	dup2(pipex->outfile_fd, STDOUT_FILENO);
	close(pipex->outfile_fd);
	return (execute(cmd2, env));
}

int	first_child_process(char *infile, char *cmd1, char **env, t_data *pipex)
{
	pipex->infile_fd = open(infile, O_RDONLY);
	if (pipex->infile_fd == -1)
		error_return("File open error");
	dup2(pipex->pipe_fds[1], STDOUT_FILENO);
	close_fds(pipex);
	dup2(pipex->infile_fd, STDIN_FILENO);
	close(pipex->infile_fd);
	return (execute(cmd1, env));
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
		error_exit("Pipe function failed");
	pipex.ret_pid1 = fork();
	if (pipex.ret_pid1 == -1)
		error_exit("Failed to create first child process");
	if (pipex.ret_pid1 == 0)
		first_child_process(argv[1], argv[2], envp, &pipex);
	pipex.ret_pid2 = fork();
	if (pipex.ret_pid2 == -1)
		error_exit("Failed to create second child process");
	if (pipex.ret_pid2 == 0)
		second_child_process(argv[4], argv[3], envp, &pipex);
	close_pipe_fds(&pipex);
	wait_and_error_exit(pipex);
	exit(EXIT_SUCCESS);
}
