/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 19:04:55 by eunskim           #+#    #+#             */
/*   Updated: 2023/03/30 19:44:51 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* output */

// This is parent process. The pid of parent is 89614 (X: parent process)
// First fork pid of parent: 89615 (Y : first child process)
// Second fork pid of parent: 89616 (Z : second child process)

// This is first child process. The pid of this child is 89615 (Y: first child process)
// First fork pid of first child: 0 (means it has no child processes)
// Second fork pid of first child: 0 (what does it mean?)

// This is second child process. The pid of this child is 89616 (Z: second child process)
// First fork pid of second child: 89615 (Y: simply inherited from parent)
// Second fork pid of second child: 0 (means it has no child processes)

/* conclusion */

// first_fork_pid = 0 -> first_child
// first_fork_pid != 0 && second_for_pid == 0 -> second_child

#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>

int	main(int argc, char *argv[], char *envp[])
{
	int		pipe_fds[2];
	int		status;
	pid_t	first_fork_pid;
	pid_t	second_fork_pid;

	pipe(pipe_fds);
	first_fork_pid = fork();
	if (first_fork_pid == -1)
	{
		perror("First fork failed");
		return (1);
	}
	if (first_fork_pid == 0)
	{
		printf("This is first child process. The pid of this child is %d\n", getpid());
		printf("First fork pid of first child: %d\n", first_fork_pid);
		printf("Second fork pid of first child: %d\n\n", second_fork_pid);
	}
	if (first_fork_pid != 0)
	{
		second_fork_pid = fork();
		if (second_fork_pid == -1)
		{
			perror("Second fork failed");
			return (2);
		}
		if (second_fork_pid == 0)
		{
			printf("This is second child process. The pid of this child is %d\n", getpid());
			printf("First fork pid of second child: %d\n", first_fork_pid);
			printf("Second fork pid of second child: %d\n", second_fork_pid);
		}
		else
		{
			printf("This is parent process. The pid of parent is %d\n", getpid());
			printf("First fork pid of parent: %d\n", first_fork_pid);
			printf("Second fork pid of parent: %d\n\n", second_fork_pid);
		}
	}
	close(pipe_fds[0]);
    close(pipe_fds[1]);
    waitpid(first_fork_pid, &status, 0);
    waitpid(second_fork_pid, &status, 0);
	return (0);
}
