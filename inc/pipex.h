/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 20:31:10 by eunskim           #+#    #+#             */
/*   Updated: 2023/04/05 21:57:22 by eunskim          ###   ########.fr       */
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
# include "get_next_line.h"

typedef struct s_data
{
	int		pipe_fds[2];
	int		infile_fd;
	int		outfile_fd;
	pid_t	ret_pid1;
	pid_t	ret_pid2;
}	t_data;


int		main(int argc, char **argv, char **envp);
int		first_child_process(char *infile, char *cmd1, char **env, t_data *pipex);
int		second_child_process(char *outfile, char *cmd2, char **env, t_data *pipex);
int		execute(char *cmd, char **env);

void	close_pipe_fds(t_data *pipex);

void	wait_and_error_exit(t_data pipex);
void	error_exit(char *err_msg);
int		error_return(char *err_msg);

#endif