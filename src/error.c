/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 21:56:55 by eunskim           #+#    #+#             */
/*   Updated: 2023/04/10 13:35:59 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* a function that waits for the sub-processes to end */
/* and returns the exit status of the last process to main */
void	wait_and_get_exit_code(t_data *pipex)
{
	int	wstatus1;
	int	wstatus2;

	pipex->exit_code = 0;
	waitpid(pipex->ret_pid1, &(wstatus1), 0);
	waitpid(pipex->ret_pid2, &(wstatus2), 0);
	if (WIFEXITED(wstatus2))
	{
		if (WEXITSTATUS(wstatus2))
			pipex->exit_code = WEXITSTATUS(wstatus2);
	}
}

/* a function that prints out an error message with perror, */
/* frees everything and exits with errno */
void	error_exit(char *err_msg, t_data *pipex)
{
	perror(err_msg);
	free_before_terminating(pipex);
	exit(errno);
}
