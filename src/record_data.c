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


char	*trim_itof(char *flt)
{
	int		i;

	i = ft_strlen(flt);
	if (flt[i - 1] == '0')
	{
		flt[i - 2] = '\0';
		return (flt);
	}
	return (flt);
}

/*void	vertex(t_xy *vertex, int num_vertex)
{
	int fd;
	int i;
	char *tmp;

	i = 0;
	fd = open("../maps/ya_karta.doom", O_WRONLY);
	tmp = (char *)malloc(sizeof(char) * 256);
	ft_bzero(tmp, 256);
	if (fd == -1)
	{
		system("touch ../maps/ya_karta.doom");
		fd = open("../maps/ya_karta.doom", O_WRONLY);
	}
	while (i < num_vertex)
	{
		tmp = ft_strcpy(tmp, "vertex ");
		tmp = ft_strcat(tmp , trim_itof(ft_itof(vertex[i].y)));
		tmp = ft_strcat(tmp, " ");
		tmp = ft_strcat(tmp, trim_itof(ft_itof(vertex[i].x)));
		tmp = ft_strcat(tmp, "\n");
		write(fd, tmp, ft_strlen(tmp));
		i++;
	}
	close(fd);
<<<<<<< HEAD
}
=======
}*/


>>>>>>> ibohun-engine
