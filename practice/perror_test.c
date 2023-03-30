/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perror_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:39:28 by eunskim           #+#    #+#             */
/*   Updated: 2023/03/30 22:02:28 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
 
// int main(void)
// {
//    FILE *fh;
 
//    if ((fh = fopen("test1.txt","r")) == NULL)
//    {
//       perror(NULL);
// 	  // perror("ERROR");
// 	  // perror("Can not open the said file.");
//    }
// }

// int main(void)
// {
// 	int i;

// 	i = 0;
// 	while (i < 127)
// 	{
// 		errno = i;
// 		perror("pipex");
// 		i++;
// 	}
// 	return (0);
// }

int	main(void)
{
	perror("before error");
	errno = ENOMEM;
	perror("errno = ENOMEM");
	errno = EACCES;
	perror("errno = EACCES");
	errno = ENOENT;
	perror("errno = ENOENT");
	errno = ENOTDIR;
	perror("errno = ENOTDIR");
	errno = EFAULT;
	perror("errno = EFAULT");
	errno = EBADF;
	perror("errno = EBADF");
	return (0);
}