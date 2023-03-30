/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_pid_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:06:19 by eunskim           #+#    #+#             */
/*   Updated: 2023/03/30 16:06:21 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	printf("pid before fork: %d\n", getpid());
	pid_t	newpid = fork();
	if (newpid < 0)
	{
		perror(NULL);
		return (1);
	}
	if (newpid == 0)
	{
		printf("this is child process. child's pid: %d\n", getpid());
		printf("newpid from child: %d\n", newpid);
	}
	else
	{
		printf("this is parent process. parent's pid: %d\n", getpid());
		printf("newpid from parent: %d\n", newpid);
	}
	printf("this is common part\n");
	return (0);
}