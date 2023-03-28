/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perror_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:39:28 by eunskim           #+#    #+#             */
/*   Updated: 2023/03/28 15:16:28 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
 
int main(void)
{
   FILE *fh;
 
   if ((fh = fopen("test1.txt","r")) == NULL)
   {
      perror(NULL);
	  // perror("ERROR");
	  // perror("Can not open the said file.");
   }
}
