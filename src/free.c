/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:13:55 by eunskim           #+#    #+#             */
/*   Updated: 2023/04/07 20:54:12 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipe_fds(t_data *pipex)
{
	close(pipex->pipe_fds[0]);
	close(pipex->pipe_fds[1]);
}

void	free_before_terminating(t_data *pipex)
{
	free_string_arr(pipex->path_splitted);
	free_string_arr(pipex->cmd_args1);
	free_string_arr(pipex->cmd_args2);
	free_string(pipex->cmd_path1);
	free_string(pipex->cmd_path2);
}

void	free_string_arr(char **arr)
{
	size_t	i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i] != 0)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_string(char *ptr)
{
	if (ptr)
		free(ptr);
}
