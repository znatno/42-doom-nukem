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

#include "duke_nukem_editor.h"

int				open_create_map(void)
{
	int			fd;

	fd = open("../maps/ya_karta.doom", O_WRONLY | O_TRUNC);
	if (fd == -1)
	{
		system("touch ../maps/ya_karta.doom");
		fd = open("../maps/ya_karta.doom", O_WRONLY | O_TRUNC);
	}
	return (fd);
}

void			num_cat(char **tmp, int num)
{
	char *number;

	number = ft_itoa(num);
	*tmp = ft_strcat(*tmp, number);
	free(number);
}

void			vertex_record(t_xy_l *vertex, int fd)
{
	t_xy_l		*walk_v;
	int			tmp_y;
	char		*tmp;

	tmp = (char *)malloc(sizeof(char) * 256);
	ft_bzero(tmp, 256);
	walk_v = vertex;
	while (walk_v)
	{
		tmp = ft_strcpy(tmp, "vertex ");
		num_cat(&tmp, walk_v->y / 10);
		tmp_y = walk_v->y;
		while (walk_v && walk_v->y == tmp_y)
		{
			tmp = ft_strcat(tmp, " ");
			num_cat(&tmp, walk_v->x / 10);
			walk_v = walk_v->next;
		}
		tmp = ft_strcat(tmp, "\n");
		write(fd, tmp, ft_strlen(tmp));
		ft_bzero(tmp, 256);
	}
	write(fd, "\n", 1);
	free(tmp);
}

void			player_record(t_record *record, int fd)
{
	char		*tmp;
	char		*itoa_tmp;

	tmp = (char *)malloc(sizeof(char) * 256);
	ft_bzero(tmp, 256);
	tmp = ft_strcpy(tmp, "\nplayer ");
	itoa_tmp = ft_itoa(record->player_x);
	tmp = ft_strcat(tmp, itoa_tmp);
	free(itoa_tmp);
	tmp = ft_strcat(tmp, " ");
	itoa_tmp = ft_itoa(record->player_y);
	tmp = ft_strcat(tmp, itoa_tmp);
	free(itoa_tmp);
	tmp = ft_strcat(tmp, " 0 ");
	itoa_tmp = ft_itoa(record->player_sec);
	tmp = ft_strcat(tmp, itoa_tmp);
	free(itoa_tmp);
	write(fd, tmp, ft_strlen(tmp));
	free(tmp);
}

void			record_data(t_record *record)
{
	int			fd;

	fd = open_create_map();
	vertex_record(record->head_ver, fd);
	sector_record(record->head_sec, fd);
	player_record(record, fd);
	close(fd);
	record_free(record);
}
