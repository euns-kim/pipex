/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitpid_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:08:47 by eunskim           #+#    #+#             */
/*   Updated: 2023/03/30 16:13:36 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	pid_t	pid;
	pid_t	ret;

	pid = fork();
	int	state = 0;
	if (pid == 0)
	{
		sleep(1);
    	ret = waitpid(-1, &state, 0);
    	perror("child");
		printf("this is child\n");
	}
	else
	{
		ret = waitpid(pid, &state, 0);
		perror("parent");
	    printf("child pid: %d\n", ret);
		printf("this is parent\n");
	}
	return (0);
}