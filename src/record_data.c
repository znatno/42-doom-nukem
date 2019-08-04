/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 13:59:22 by ggavryly          #+#    #+#             */
/*   Updated: 2019/08/04 13:59:24 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl1.h"

void	vertex(char *path ,int *y, int **x, int count_y, int *count_x)
{
	int fd;
	int i;

	i = 0;
	fd = 0;
	if ((fd = open(path, O_WRONLY) < 0))
	{
		system("mkdir ya_karta.doom");
		if ((fd = open("ya_karta.doom", O_WRONLY) < 0))
		{
			printf("Ah shit, here we go again %s", "write to ya_karta.doom");
			return;
		}
	}
	while (i < count_y)
	{

		write(fd, ft_it)
		i++;
	}

}
