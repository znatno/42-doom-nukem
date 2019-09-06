/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibohun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:00:35 by ibohun            #+#    #+#             */
/*   Updated: 2019/08/19 19:24:08 by ibohun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int			move_or_not(t_xyz where, t_sector sector, unsigned sect_num, int j)
{
	t_xy	xy[2];
	int		res;
	float	sum_angles;
	float	cur_angle;

	j = -1;
	res = -1;
	sum_angles = 0;
	cur_angle = 0;
	while (++j < sector.npoints)
	{
		xy[0] = vv_to_v(where.x, where.y, sector.vertex[j].x,
				sector.vertex[j].y);
		xy[1] = vv_to_v(where.x, where.y, sector.vertex[j + 1].x,
				sector.vertex[j + 1].y);
		cur_angle = angles(xy[0], xy[1]);
		if (vector_product(xy[0], xy[1]) > 0)
			sum_angles += cur_angle;
		else
			sum_angles -= cur_angle;
	}
	if ((sum_angles >= 357.0 && sum_angles <= 363.0)
	|| (sum_angles >= -363.0 && sum_angles <= -357.0))
		res = sect_num;
	return (res);
}

void		move_player(t_player *plr, t_sector **sectors, float dx, float dy, int i)
{
	t_sector	*sect;
	t_xy		*vert;
	float		px;
	float		py;
	int			flag;

	px = plr->where.x;
	py = plr->where.y;
	sect = &(*sectors)[plr->sector];
	vert = sect->vertex;
	i = -1;
	flag = -2;
	plr->where.x += dx;
	plr->where.y += dy;
	while (++i < sect->npoints)
	{
		if (sect->neighbors[i] >= 0
				&&
				intersect_box(px, py, px + dx, py + dy,
						vert[i + 0].x, vert[i].y,
						vert[i + 1].x, vert[i + 1].y)
				&&
				point_side(px + dx, py + dy,
						vert[i + 0].x, vert[i].y,
						vert[i + 1].x, vert[i + 1].y) < 0)
		{
			flag = move_or_not(plr->where, (*sectors)[sect->neighbors[i]], sect->neighbors[i], 0);
			if (flag >= 0 && flag < plr->num_scts)
				plr->sector = sect->neighbors[i];
			else if (flag == -1)
			{
				plr->where.x -= dx;
				plr->where.y -= dy;
			}
			break ;
		}
	}
	if (flag == -2)
	{
		flag = move_or_not(plr->where, (*sectors)[plr->sector], plr->sector, 0);
		if (flag == -1)
		{
			plr->where.x -= dx;
			plr->where.y -= dy;
		}
	}
	plr->anglesin = sinf(plr->angle);
	plr->anglecos = cosf(plr->angle);
}

void		chholebump(t_chloe c, float *dx, float *dy)
{
	float hole_low;
	float hole_high;
	float xd;
	float yd;

	hole_low = c.sect.neighbors[c.s] <
			0 ? 9e9 : MAX(c.sect.floor, c.sectors[c.sect.neighbors[c.s]].floor);
	hole_high = c.sect.neighbors[c.s] <
			0 ? -9e9 : MIN(c.sect.ceil, c.sectors[c.sect.neighbors[c.s]].ceil);
	if (hole_high < (*c.plr)->where.z + HEAD_MARGIN
		|| hole_low > (*c.plr)->where.z - (*c.plr)->eyeheight + KNEE_H)
	{
		xd = c.vert[c.s + 1].x - c.vert[c.s + 0].x;
		yd = c.vert[c.s + 1].y - c.vert[c.s + 0].y;
		*dx = xd * (*dx * xd + yd * *dy) / (xd * xd + yd * yd);
		*dy = yd * (*dx * xd + yd * *dy) / (xd * xd + yd * yd);
		(*c.plr)->moving = 0;
	}
	printf("hole_high - %f\n", hole_high);
}

void		check_move(t_player *plr, t_sector **sc, unsigned int s)
{
	float	px;
	float	py;
	float	dx;
	float	dy;

	px = plr->where.x;
	py = plr->where.y;
	dx = plr->vlct.x;
	dy = plr->vlct.y;
	(*sc)->vert = (*sc)[plr->sector].vertex;
	s = -1;
	while (++s < (*sc)[plr->sector].npoints)
	{
		if (intersect_box(px, py, px + dx, py + dy,
				(*sc)->vert[s + 0].x, (*sc)->vert[s + 0].y,
				(*sc)->vert[s + 1].x, (*sc)->vert[s + 1].y)
			&& point_side(px + dx, py + dy,
					(*sc)->vert[s + 0].x, (*sc)->vert[s + 0].y,
					(*sc)->vert[s + 1].x, (*sc)->vert[s + 1].y) < 0)
			chholebump((t_chloe){.sectors = *sc, .sect = (*sc)[plr->sector],
						.s = s, .plr = &plr, .vert = (*sc)->vert}, &dx, &dy);
	}
	move_player(plr, sc, dx, dy, -1);
	plr->falling = 1;
}

void		do_fall(t_player *plr, t_sector **sc, t_sounds *sounds)
{
	float	nextz;

	if (!plr->fly)
		plr->vlct.z -= 0.05f; /* Add gravity */
	else if ((*sc)[plr->sector].ceil > plr->where.z)
		plr->vlct.z += 0.001f;
	nextz = plr->where.z + plr->vlct.z;
	if (plr->vlct.z < 0 && nextz < (*sc)[plr->sector].floor + plr->eyeheight) // When going down
	{
		plr->where.z = (*sc)[plr->sector].floor + plr->eyeheight; /* Fix to ground */
		plr->vlct.z = 0;
		plr->falling = 0;
		plr->ground = 1;
	}
	else if (plr->vlct.z > 0 && nextz >= (*sc)[plr->sector].ceil) // When going up
	{
		plr->vlct.z = 0; /* Prevent jumping above ceiling */
		plr->falling = 1;
		plr->where.z -= 0.1f;
		plr->fly = 0;
	}
	if (plr->falling)
	{
		plr->where.z += plr->vlct.z;
		plr->moving = 1;
	}
}
