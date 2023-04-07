/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 20:31:10 by eunskim           #+#    #+#             */
/*   Updated: 2023/04/07 18:52:53 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"

typedef struct s_data
{
	int		pipe_fds[2];
	int		infile_fd;
	int		outfile_fd;
	pid_t	ret_pid1;
	pid_t	ret_pid2;
	char	**path_splitted;
	char	**cmd_args1;
	char	**cmd_args2;
	char	*cmd_path1;
	char	*cmd_path2;
	int		exit_code;
}	t_data;

int		first_child_process(char *infile, char *cmd1, \
char **env, t_data *pipex);
int		second_child_process(char *outfile, char *cmd2, \
char **env, t_data *pipex);

char	**get_path_and_split(char **env, t_data *pipex);
char	**get_cmd_args(char *cmd, t_data *pipex);
char	*get_cmd_path(char *cmd, char **path_splitted);
void	close_pipe_fds(t_data *pipex);
void	initialize_pipex(t_data *pipex);

void	free_string(char *ptr);
void	free_string_arr(char **arr);
void	free_before_terminating(t_data *pipex);

int		error_return(char *err_msg);
void	error_exit(char *err_msg, t_data *pipex);
void	wait_and_get_exit_code(t_data *pipex);

#endif