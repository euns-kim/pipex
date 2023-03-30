/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:26:10 by eunskim           #+#    #+#             */
/*   Updated: 2023/03/30 16:26:12 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int	fd = open("newfile", O_RDWR | O_CREAT, 0644);
	printf("printf before dup2\n");
	dup2(fd, STDOUT_FILENO);
	printf("printf after dup2\n");
	close(fd);
	return (0);
}