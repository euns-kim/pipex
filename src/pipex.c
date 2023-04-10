/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 18:30:37 by eunskim           #+#    #+#             */
/*   Updated: 2023/04/10 15:40:29 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* second child process */
/* which reads from stdin, executes command and writes to outfile */
/* the file descriptor of pipe_fds[0] is copied to stdin */
/* the file descriptor of outfile is copied to stdout */
void	child_process_2(char *outfile, char *cmd2, char **env, t_data *pipex)
{
	dup2(pipex->pipe_fds[0], STDIN_FILENO);
	close_pipe_fds(pipex);
	pipex->outfile_fd = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->outfile_fd == -1)
		error_exit("File open error", pipex);
	dup2(pipex->outfile_fd, STDOUT_FILENO);
	close(pipex->outfile_fd);
	pipex->cmd_args2 = get_cmd_args(cmd2, pipex);
	pipex->cmd_path2 = get_cmd_path(pipex->cmd_args2[0], pipex->path_splitted);
	if (pipex->cmd_path2 == NULL)
	{
		errno = 127;
		error_exit("Command not found", pipex);
	}
	if (execve(pipex->cmd_path2, pipex->cmd_args2, env) == -1)
		error_exit("Failed to execute command", pipex);
}

/* first child process */
/* which reads from infile, executes command and writes to stdout */
/* the file descriptor of infile is copied to stdin */
/* the file descriptor of pipe_fds[1] is copied to stdout */
void	child_process_1(char *infile, char *cmd1, char **env, t_data *pipex)
{
	dup2(pipex->pipe_fds[1], STDOUT_FILENO);
	close_pipe_fds(pipex);
	pipex->infile_fd = open(infile, O_RDONLY);
	if (pipex->infile_fd == -1)
		error_exit("File open error", pipex);
	dup2(pipex->infile_fd, STDIN_FILENO);
	close(pipex->infile_fd);
	pipex->cmd_args1 = get_cmd_args(cmd1, pipex);
	pipex->cmd_path1 = get_cmd_path(pipex->cmd_args1[0], pipex->path_splitted);
	if (pipex->cmd_path1 == NULL)
	{
		errno = 127;
		error_exit("Command not found", pipex);
	}
	if (execve(pipex->cmd_path1, pipex->cmd_args1, env) == -1)
		error_exit("Failed to execute command", pipex);
}

/* main function where two sub-processe are created */
/* using pipe and fork functions */
/* it awaits exit status of the second process and returns it */
int	main(int argc, char **argv, char **envp)
{
	t_data	pipex;

	if (argc != 5)
	{
		ft_putstr_fd("Invalid arguments. \
		Usage: ./pipex file1 cmd1 cmd2 file2", 2);
		exit(EXIT_FAILURE);
	}
	initialize_pipex(&pipex);
	pipex.path_splitted = get_path_and_split(envp, &pipex);
	if (pipe(pipex.pipe_fds) == -1)
		error_exit("Pipe function failed", &pipex);
	pipex.ret_pid1 = fork();
	if (pipex.ret_pid1 == -1)
		error_exit("Failed to create first child process", &pipex);
	if (pipex.ret_pid1 == 0)
		child_process_1(argv[1], argv[2], envp, &pipex);
	pipex.ret_pid2 = fork();
	if (pipex.ret_pid2 == -1)
		error_exit("Failed to create second child process", &pipex);
	if (pipex.ret_pid2 == 0)
		child_process_2(argv[4], argv[3], envp, &pipex);
	close_pipe_fds(&pipex);
	wait_and_get_exit_code(&pipex);
	free_before_terminating(&pipex);
	return (pipex.exit_code);
}
