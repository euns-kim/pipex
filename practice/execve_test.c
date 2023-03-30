/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:30:54 by eunskim           #+#    #+#             */
/*   Updated: 2023/03/30 17:05:52 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

extern char **environ;

int	main(void)
{
	char	*path = "/bin/ls";
	// char	*path = "/usr/bin/env";
	char	*cmd[5];

	cmd[0] = "asdfasdf";
	cmd[1] = "-a";
    cmd[2] = "-l";
	cmd[3] = NULL;
	if (execve(path, cmd, environ) < 0)
		perror(NULL);
	// if (execve(path, cmd, NULL) < 0)
	// 	perror(NULL);
	// if (execve(path, NULL, environ) < 0)
	// 	perror(NULL);
	printf("if failed, this will be printed\n");
}
