/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fd_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:33:56 by eunskim           #+#    #+#             */
/*   Updated: 2023/03/28 14:46:38 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#define IN 0
#define OUT 1

int main(int argc, const char * argv[]) {
    int pid;
	int pipe_fd[2];

	if (pipe(pipe_fd) == -1) {
		// possible errors: EFAULT, EMFILE, ENFILE.
		perror("Failed to create pipe");
		return -1;
	}

	printf("pipe_fd[IN]: %d, pipe_fd[OUT]: %d\n", pipe_fd[IN], pipe_fd[OUT]);

	pid = fork();
	if (pid == -1) {
		// possible errors: EAGAIN, ENOMEM.
	    perror("Failed to fork");
	    return -1;
	}

	if (pid == 0) {
		// child
		printf("Child pid: %d\n", getpid());
		while (1) {
			write(pipe_fd[OUT], "hello", 5);
			sleep(1);
		}
	} else {
		// parent
		printf("Parent pid: %d\n", getpid());
		char buf[10];
		while (1) {
			read(pipe_fd[IN], buf, 10);
			printf("Incomming message from child process: %s\n", buf);
		}
	}

	return 0;
}
