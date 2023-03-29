/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:58:02 by eunskim           #+#    #+#             */
/*   Updated: 2023/03/29 21:40:25 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* keywords */
/* executing linux commands in c */
/* getting exit code */
/* redirecting the outcome to another file */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int	main(int argc, char *argv[])
{
	int pid = fork();
	
	if (pid == -1)
	{
		printf("fork error\n");
		return 1;
	}
	if (pid == 0)
	{
		// Child process
		int file = open("result.txt", O_WRONLY | O_CREAT, 0777);
		
		if (file == -1)
		{
			printf("file open error\n");
			return 2;
		}

		// int file2 = dup(file);
		printf("The original fd of result.txt: %d\n", file);
		int file2 = dup2(file, STDOUT_FILENO);
		printf("The duplicated fd: %d\n\n", file2);
		close(file);
	
		// int err = execlp("ping", "ping", "-c", "1", "google.com", NULL);
		int err = execlp("pings", "ping", "-c", "1", "google.com", NULL);
		// int err = execlp("ping", "ping", "-c", "1", "google.con", NULL);

		// int err = execlp("wc", "wc", "result.txt", NULL);
		
		if (err == -1)
		{
			printf("exec failed\n");
			return 3;
		}		
	}
	else
	{
		// Parent proess
		int wstatus;

		wait(&wstatus);
		if (WIFEXITED(wstatus))
		{
			int status_code = WEXITSTATUS(wstatus);
			if (status_code == 0)
				printf("Success!\n");
			else
				printf("failure with status code %d\n", status_code);
		}
	}
}