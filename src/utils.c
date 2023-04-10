/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 21:51:44 by eunskim           #+#    #+#             */
/*   Updated: 2023/04/10 13:31:41 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* a function that joins each path string with '/' and command */
/* to find the accessible one */
/* when the path is already given by $which or '/', */
/* this path will be forwarded */
char	*get_cmd_path(char *cmd, char **path_splitted)
{
	char	*tmp;
	char	*cmd_path;

	if (ft_strnstr(cmd, "/", ft_strlen(cmd)) \
	|| ft_strnstr(cmd, "$(which", ft_strlen(cmd)))
		return (cmd);
	while (path_splitted && *path_splitted)
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

/* a function that splits the command string given into several arguments */
char	**get_cmd_args(char *cmd, t_data *pipex)
{
	char	**cmd_args;

	cmd_args = ft_split(cmd, ' ');
	if (cmd_args == NULL)
		error_exit("Failed to get command arguments", pipex);
	return (cmd_args);
}

/* a funtion that reads 'PATH' line from environment variable, */
/* splits it into multiple paths and saves those in string array */
char	**get_path_and_split(char **env, t_data *pipex)
{
	char	**path_splitted;

	if (env == NULL || *env == NULL)
		return (NULL);
	while (*env && ft_strncmp(*env, "PATH=", 5) != 0)
		env++;
	path_splitted = ft_split(*env + 5, ':');
	if (path_splitted == NULL)
		error_exit("Failed to split path", pipex);
	return (path_splitted);
}

/* a function that initializes every pointer in the data struct to null */
void	initialize_pipex(t_data *pipex)
{
	pipex->path_splitted = NULL;
	pipex->cmd_args1 = NULL;
	pipex->cmd_args2 = NULL;
	pipex->cmd_path1 = NULL;
	pipex->cmd_path2 = NULL;
}
