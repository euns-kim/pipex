/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 21:56:55 by eunskim           #+#    #+#             */
/*   Updated: 2023/04/06 20:13:50 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_and_error_exit(t_data *pipex)
{
	int	wstatus1;
	int	wstatus2;
	int	status_code;

	status_code = 0;
	waitpid(pipex->ret_pid1, &(wstatus1), 0);
	waitpid(pipex->ret_pid2, &(wstatus2), 0);
	if (WIFEXITED(wstatus2))
		status_code = WEXITSTATUS(wstatus2);
	if (status_code != 0)
	{
		errno = status_code;
		error_exit(NULL, pipex);
	}
	return ;
}

int	error_return(char *err_msg)
{
	perror(err_msg);
	return (EXIT_FAILURE);
}

void	error_exit(char *err_msg, t_data *pipex)
{
	perror(err_msg);
	free_before_terminating(pipex);
	exit(EXIT_FAILURE);
}
