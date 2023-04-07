/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 21:51:44 by eunskim           #+#    #+#             */
/*   Updated: 2023/04/07 18:28:05 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipe_fds(t_data *pipex)
{
	close(pipex->pipe_fds[0]);
	close(pipex->pipe_fds[1]);
}

char	*get_cmd_path(char *cmd, char **path_splitted)
{
	char	*tmp;
	char	*cmd_path;

	while (*path_splitted)
	{
		tmp = ft_strjoin(*path_splitted, "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free_string(tmp);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free_string(cmd_path);
		path_splitted++;
	}
	return (NULL);
}

char	**get_cmd_args(char *cmd, t_data *pipex)
{
	char	**cmd_args;

	cmd_args = ft_split(cmd, ' ');
	if (cmd_args == NULL)
		error_exit("Failed to split command", pipex);
	return (cmd_args);
}

char	**get_path_and_split(char **env, t_data *pipex)
{
	char	**path_splitted;

	while (ft_strncmp(*env, "PATH=", 5) != 0)
		env++;
	path_splitted = ft_split(*env + 5, ':');
	if (path_splitted == NULL)
		error_exit("Failed to split path", pipex);
	return (path_splitted);
}

void	initialize_pipex(t_data *pipex)
{
	pipex->path_splitted = NULL;
	pipex->cmd_args1 = NULL;
	pipex->cmd_args2 = NULL;
	pipex->cmd_path1 = NULL;
	pipex->cmd_path2 = NULL;
}
