/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:14:51 by eunskim           #+#    #+#             */
/*   Updated: 2023/03/30 17:15:30 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int  main(void)
{
	if (access("test.txt", F_OK | R_OK) < 0)
	{
			perror(NULL); //perror는 현재 errno에 해당하는 시스템 에러 메세지를 stderr로 출력
			return (1);
	}
	else
	{
			printf("can read file\n");
			return (0);
	}
}
