/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 21:51:44 by eunskim           #+#    #+#             */
/*   Updated: 2023/04/08 17:20:23 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**simple_double_quote_management(char *cmd)
{
	char	**cmd_args;
	char	*start;
	size_t	len;

	cmd_args = (char **) malloc (sizeof(char *) * 3);
	if (cmd_args == NULL)
		return (NULL);
	len = ft_strlen(cmd);
	start = ft_strnstr(cmd, " ", len);
	cmd_args[0] = ft_substr(cmd, 0, start - cmd);
	if (cmd_args[0] == NULL)
	{
		free_string_arr(cmd_args);
		return (NULL);
	}
	cmd_args[1] = ft_substr(cmd, start - cmd + 1, cmd + len - start - 1);
	if (cmd_args[1] == NULL)
	{
		free_string_arr(cmd_args);
		return (NULL);
	}
	cmd_args[2] = NULL;
	return (cmd_args);
}

char	*get_cmd_path(char *cmd, char **path_splitted)
{
	char	*tmp;
	char	*cmd_path;

	if (ft_strnstr(cmd, "/", ft_strlen(cmd)) \
	|| ft_strnstr(cmd, "which", ft_strlen(cmd)))
		return (cmd);
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

	if (ft_strnstr(cmd, "\"", ft_strlen(cmd)))
		cmd_args = simple_double_quote_management(cmd);
	else
		cmd_args = ft_split(cmd, ' ');
	if (cmd_args == NULL)
		error_exit("Failed to get command arguments", pipex);
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
