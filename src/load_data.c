/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibohun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 19:06:01 by ggavryly          #+#    #+#             */
/*   Updated: 2019/08/22 23:30:37 by ibohun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_reader	*reader_coroutine4(t_reader *read, char *line, t_player *p,
		t_sector **sectors)
{
	while (!ft_isdigit(line[read->posf.pos]))
		read->posf.pos++;
	read->posf = atof_posf(line, read->posf, 0);
	p->where.x = read->posf.value;
	read->posf = atof_posf(line, read->posf, 0);
	p->where.y = read->posf.value;
	read->posf = atof_posf(line, read->posf, 0);
	p->angle = read->posf.value;
	read->posf = atof_posf(line, read->posf, 0);
	read->n = (int)read->posf.value;
	p->sector = read->n;
	p->where.z = (*sectors)[p->sector].floor + EYE_H;
}

t_reader	*reader_coroutine3(t_reader *read)
{
	read->sect->npoints = read->all /= 2;
	read->sect->neighbors = malloc((read->all) *
			sizeof(*read->sect->neighbors));
	read->sect->vertex = malloc((read->all + 1) * sizeof(*read->sect->vertex));
	read->n = 0;
	while (read->n < read->all)
	{
		read->sect->neighbors[read->n] = read->num[read->all + read->n];
		read->n++;
	}
	read->n = 0;
	while (read->n < read->all)
	{
		read->sect->vertex[read->n + 1] = read->vert[read->num[read->n]];
		read->n++;
	}
	read->sect->vertex[0] = read->sect->vertex[read->all];
	free(read->num);
	return (read);
}

t_reader	*reader_coroutine2(t_reader *read, t_sector **sectors, t_player *p,
		char *line)
{
	while (!ft_isdigit(line[read->posf.pos]))
		read->posf.pos++;
	read->posf = atof_posf(line, read->posf, 0);
	read->sect->floor = read->posf.value;
	while (!ft_isdigit(line[read->posf.pos]))
		read->posf.pos++;
	read->posf = atof_posf(line, read->posf, 0);
	read->sect->ceil = (int)read->posf.value;
	read->all = 0;
	read->len = ft_strlen(line);
	while (line[read->posf.pos] && read->len >= read->posf.pos)
	{
		while (!ft_isdigit(line[read->posf.pos]))
			read->posf.pos++;
		if (line[read->posf.pos - 1] == '-')
			read->posf.pos--;
		if (read->len >= read->posf.pos)
		{
			read->num = ft_realloc(read->num, ++read->all * sizeof(*read->num));
			read->posf = atof_posf(line, read->posf, 0);
			read->num[read->all - 1] = (int)read->posf.value;
		}
	}
	return (read);
}

t_reader	*reader_coroutine1(t_reader *read, char *line)
{
	while (line[--read->posf.pos])
	{
		while (!ft_isdigit(line[read->posf.pos]))
			read->posf.pos++;
		read->vert = ft_realloc(read->vert, ++read->NuMVertices
		* sizeof(*read->vert));
		if (read->posf.is_y)
		{
			read->posf = atof_posf(line, read->posf, 0);
			read->vert[read->NuMVertices - 1].y = read->posf.value;
			read->posf.y = read->posf.value;
			while (!ft_isdigit(line[read->posf.pos]))
				read->posf.pos++;
			read->posf = atof_posf(line, read->posf, 0);
			read->vert[read->NuMVertices - 1].x = read->posf.value;
			read->posf.is_y = 0;
		}
		else
		{
			read->posf = atof_posf(line, read->posf, 0);
			read->vert[read->NuMVertices - 1].x = read->posf.value;
			read->vert[read->NuMVertices - 1].y = read->posf.y;
		}
	}
	return (read);
}

void		load_data(t_player *player, t_sector **sectors)
{
	int		fd;
	char	*line;

	line = ft_strnew(1);
	fd = open("../test.txt", O_RDONLY);
	if (!(check_file(fd)))
		exit(-1);
	reader(line, fd, player, sectors);
}
