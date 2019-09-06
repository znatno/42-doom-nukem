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

void		chholebump(t_sector **sectors, t_sector sect, const unsigned int *s,
						t_player *plr, t_xy **vert, float *dx, float *dy)
{
	float hole_low;
	float hole_high;
	float xd;
	float yd;

	hole_low = sect.neighbors[*s] <
			0 ? 9e9 : MAX(sect.floor, (*sectors)[sect.neighbors[*s]].floor);
	hole_high = sect.neighbors[*s] <
			0 ? -9e9 : MIN(sect.ceil, (*sectors)[sect.neighbors[*s]].ceil);
	if (hole_high < plr->where.z + HEAD_MARGIN
		|| hole_low > plr->where.z - plr->eyeheight + KNEE_H)
	{
		xd = (*vert)[*s + 1].x - (*vert)[*s + 0].x;
		yd = (*vert)[*s + 1].y - (*vert)[*s + 0].y;
		*dx = xd * (*dx * xd + yd * *dy) / (xd * xd + yd * yd);
		*dy = yd * (*dx * xd + yd * *dy) / (xd * xd + yd * yd);
		plr->moving = 0;
	}
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
			chholebump(sc, (*sc)[plr->sector], &s, plr, &(*sc)->vert, &dx, &dy);
	}
	move_player(plr, sc, dx, dy, -1);
	plr->falling = 1;
}

void		do_fall(t_player *plr, t_sector **sc, t_sounds *sounds)
{
	float	nextz;

	if (plr->vlct.z > 0 || plr->vlct.z < -0.6)
		plr->jump_check = true;
	plr->vlct.z -= 0.05f; /* Add gravity */
	nextz = plr->where.z + plr->vlct.z;
	if (plr->vlct.z < 0.f && nextz < (*sc)[plr->sector].floor + plr->eyeheight) // When going down
	{
		if (plr->jump_check)
		{
			Mix_PlayChannel(LANDING, sounds->landing, 0);
			plr->jump_check = false;
		}
		//printf("landing, vlct %f\n", plr->vlct.z);
		plr->where.z = (*sc)[plr->sector].floor + plr->eyeheight; /* Fix to ground */
		plr->vlct.z = 0.f;
		//plr->falling = 0;
		plr->ground = 1;
	}
	else if (plr->vlct.z > 0 && nextz > (*sc)[plr->sector].ceil) // When going up
	{
		plr->vlct.z = 0; /* Prevent jumping above ceiling */
		plr->falling = 1;
	}
	if (plr->falling)
	{
		plr->where.z += plr->vlct.z;
		plr->moving = 1;
	}
}
