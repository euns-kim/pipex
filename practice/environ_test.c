/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:45:39 by eunskim           #+#    #+#             */
/*   Updated: 2023/03/28 14:46:35 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

extern char **environ;

int	main(int argc, char *argv[])
{
	int	idx = 0;

	(void)argc;
	(void)argv;
	while (environ[idx])
	{
		printf("environ[%d]: %s\n", idx, environ[idx]);
		idx++;
	}
	return (0);
}
