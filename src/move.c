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

void		motion(t_player *plr, t_sector **sectors, float dx, float dy)
{
	move_init(&plr, sectors, dx, dy);
	while (++plr->mc.flag[1] < plr->mc.sect->npoints)
	{
		if (plr->mc.sect->neighbors[plr->mc.flag[1]] >= 0
				&&
				surface_in((t_math) {.x0 = plr->mc.px, .y0 = plr->mc.py,
						.x1 = plr->mc.px + dx, .y1 = plr->mc.py + dy,
						.x2 = plr->mc.vert[plr->mc.flag[1] + 0].x,
						.y2 = plr->mc.vert[plr->mc.flag[1]].y,
						.x3 = plr->mc.vert[plr->mc.flag[1] + 1].x,
						.y3 = plr->mc.vert[plr->mc.flag[1] + 1].y})
				&&
				point_basis((t_math) {.px = plr->mc.px + dx,
						.py = plr->mc.py + dy,
						.xx0 = plr->mc.vert[plr->mc.flag[1] + 0].x,
						.yy0 = plr->mc.vert[plr->mc.flag[1]].y,
						.xx1 = plr->mc.vert[plr->mc.flag[1] + 1].x,
						.yy1 = plr->mc.vert[plr->mc.flag[1] + 1].y}) < 0)
		{
			check_sector(&plr, sectors, dx, dy);
			break ;
		}
	}
	check_dia(&plr, sectors, dx, dy);
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
}

void		check_move(t_player *plr, t_sector **sc, unsigned int s)
{
	float	dx;
	float	dy;

	dx = plr->vlct.x;
	dy = plr->vlct.y;
	(*sc)->vert = (*sc)[plr->sector].vertex;
	s = -1;
	while (++s < (*sc)[plr->sector].npoints)
	{
		if (inter_point(s, sc, plr))
			chholebump((t_chloe){.sectors = *sc, .sect = (*sc)[plr->sector],
						.s = s, .plr = &plr, .vert = (*sc)->vert}, &dx, &dy);
	}
	motion(plr, sc, dx, dy);
	plr->falling = 1;
}

void		do_fall(t_player *plr, t_sector **sc, t_sounds *sounds)
{
	float	nextz;

	if (!plr->fly)
		plr->vlct.z -= 0.05f;
	else if ((*sc)[plr->sector].ceil > plr->where.z)
		plr->vlct.z += 0.001f;
	nextz = plr->where.z + plr->vlct.z;
	if (plr->vlct.z < 0 && nextz < (*sc)[plr->sector].floor + plr->eyeheight)
	{
		plr->where.z = (*sc)[plr->sector].floor + plr->eyeheight;
		plr->vlct.z = 0;
		plr->falling = 0;
		plr->ground = 1;
	}
	else if (plr->vlct.z > 0 && nextz >= (*sc)[plr->sector].ceil)
	{
		plr->vlct.z = 0;
		plr->falling = 1;
		plr->fly = 0;
	}
	if (plr->falling)
	{
		plr->where.z += plr->vlct.z;
		plr->moving = 1;
	}
}
