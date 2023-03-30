/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:15:00 by eunskim           #+#    #+#             */
/*   Updated: 2023/03/30 17:04:02 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int	main(int argc, char *argv[])
{
	// char *arr[] = {"ping", "google.com", NULL};
	// execvp("ping", arr);
	execvp("id", (char *[3]) {"id", "eunskim", 0});
	int err = errno;
	printf("exec failed");
	return (0);
}