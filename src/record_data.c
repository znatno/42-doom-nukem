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

int		open_create_map()
{
	int 	fd;

	fd = open("../maps/ya_karta.doom", O_WRONLY);
	if (fd == -1)
	{
		system("touch ../maps/ya_karta.doom");
		fd = open("../maps/ya_karta.doom", O_WRONLY);
	}
	return (fd);
}

void	vertex_record(t_xy_l *vertex, int fd)
{
	t_xy_l	*walk_v;
	int 	tmp_i[2];
	char *tmp;

	tmp = (char *)malloc(sizeof(char) * 256);
	ft_bzero(tmp, 256);
	walk_v = vertex;
	while (walk_v)
	{
		tmp = ft_strcpy(tmp, "vertex ");
		tmp = ft_strcat(tmp , trim_itof(ft_itof(walk_v->y)));
		tmp_i[0] = walk_v->y;
		while (walk_v && walk_v->y == tmp_i[0])
		{
			tmp = ft_strcat(tmp, " ");
			tmp = ft_strcat(tmp, trim_itof(ft_itof(walk_v->x)));
			walk_v = walk_v->next;
			tmp_i[1] = -1;
		}
		tmp = ft_strcat(tmp, "\n");
		write(fd, tmp, ft_strlen(tmp));
		ft_bzero(tmp, 256);
		if (walk_v)
			walk_v = (tmp[1] == -1) ? walk_v : walk_v->next;
	}
}

void	sector_record(t_rec_sec *head_s, int fd)
{
	t_rec_sec	*walk_s;
	t_index		*walk_sv;
	t_portal	*walk_sp;
	char		*tmp;

	walk_s = head_s;
	tmp = (char *)malloc(sizeof(char) * 256);
	ft_bzero(tmp, 256);
	while (walk_s)
	{
		tmp = ft_strcpy(tmp, "sector ");
		tmp = ft_strcat(tmp, trim_itof((ft_itof(walk_s->floor))));
		tmp = ft_strcat(tmp, " ");
		tmp = ft_strcat(tmp, trim_itof((ft_itof(walk_s->ceil))));
		tmp = ft_strcat(tmp, "\t");
		walk_sv = walk_s->head_ind;
		walk_sp = walk_s->head_por;
		while (walk_sv)
		{
			tmp = ft_strcat(tmp, " ");
			tmp = ft_strcat(tmp, trim_itof((ft_itof(walk_sv->index))));
			walk_sv = walk_sv->next;
		}
		while (walk_sp)
		{
			tmp = ft_strcat(tmp, " ");
			tmp = ft_strcat(tmp, trim_itof((ft_itof(walk_sp->wall_portal))));
			walk_sp = walk_sp->next;
		}
		tmp = ft_strcat(tmp, "\n");
		write(fd, tmp, ft_strlen(tmp));
		ft_bzero(tmp, 256);
		walk_s = walk_s->next;
	}
}

void	player_record()
{
	//record player to file
}

void	record_to_file(t_record *rec)
{

}

void	record_data(t_record *record)
{
	int fd;

	fd = open_create_map();
	vertex_record(record->head_ver, fd);
	sector_record(record->head_sec, fd);
//	player_record(player, fd);
	close(fd);
}