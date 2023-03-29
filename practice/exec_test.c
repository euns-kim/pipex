/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:15:00 by eunskim           #+#    #+#             */
/*   Updated: 2023/03/29 18:48:57 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int	main(int argc, char *argv[])
{
	char *arr[] = {"ping", "google.com", NULL};
	execvp("ping", arr);
	int err = errno;
	printf("exec failed");
	return (0);
}