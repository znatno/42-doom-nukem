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

/*
**	MovePlayer(dx,dy): Moves the player by (dx,dy) in the map, and
**	also updates their anglesin/anglecos/sector properties properly.
*/

int		move_or_not(t_xyz where ,t_sector sector, unsigned sect_num)
{
	t_xy	xy[2];
	int		res;
	float sum_angles = 0;
	float cur_angle = 0;

	res = -1;
	for (int j = 0; j < sector.npoints; j++)
	{
		xy[0] = vv_to_v(where.x, where.y,sector.vertex[j].x, sector.vertex[j].y);
		xy[1] = vv_to_v(where.x, where.y, sector.vertex[j + 1].x, sector.vertex[j + 1].y);
		cur_angle = angles(xy[0], xy[1]);
		if (vector_product(xy[0], xy[1]) > 0)
			sum_angles += cur_angle;
		else
			sum_angles -= cur_angle;
	}
//	printf("%f - angle\n", sum_angles);
	if ((sum_angles >= 357.0 && sum_angles <= 363.0) || (sum_angles >= -363.0 && sum_angles <= -357.0))
		res = sect_num;
	return (res);
}

void	move_player(t_player *plr, t_sector **sectors, float dx, float dy)
{
	t_sector	*sect;
	t_xy		*vert;
	float		px;
	float		py;
	unsigned	i;
	int flag;

	px = plr->where.x;
	py = plr->where.y;
	sect = &(*sectors)[plr->sector];
	vert = sect->vertex;
	i = 0;
	flag = -2;
	plr->where.x += dx;
	plr->where.y += dy;
	while (i < sect->npoints)
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
			flag = move_or_not(plr->where, (*sectors)[sect->neighbors[i]], sect->neighbors[i]);
			printf("flag_value - %d\n", flag);
			if (flag >= 0 && flag < plr->num_scts)
				plr->sector = sect->neighbors[i];
			else if (flag == -1)
			{
				plr->where.x -= dx;
				plr->where.y -= dy;
			}
			break ;
		}
		i++;
	}
	if (flag == -2)
	{
		printf("-2\n");
		flag = move_or_not(plr->where, (*sectors)[plr->sector], plr->sector);
		if (flag == -1)
		{
			plr->where.x -= dx;
			plr->where.y -= dy;
		}
	}
//	printf("player_x - %f| player_y - %f\n", plr->where.x, plr->where.y);
	plr->anglesin = sinf(plr->angle);
	plr->anglecos = cosf(plr->angle);
}

void		chholebump(t_sector **sectors, t_sector sect, const unsigned int *s,
					   t_player *plr, t_xy **vert, float *dx, float *dy)
{
	float hole_low; /* Check where the hole is. */
	float hole_high;
	float xd;
	float yd;

//	printf("Check Bump.\n");
	hole_low = sect.neighbors[*s] <
			0 ? 9e9 : MAX(sect.floor, (*sectors)[sect.neighbors[*s]].floor);
	hole_high = sect.neighbors[*s] <
			0 ? -9e9 : MIN(sect.ceil, (*sectors)[sect.neighbors[*s]].ceil);
	/* Check whether we're bumping into a wall. */
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

void		check_move(t_player *plr, t_sector **sc)
{
	unsigned int	s;
	float 			px;
	float 			py;
	float 			dx;
	float 			dy;

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
			// перевірка, чи вміщаємось ми туди, куди ліземо, по висоті
			chholebump(sc, (*sc)[plr->sector], &s, plr, &(*sc)->vert, &dx, &dy);
	}
	move_player(plr, sc, dx, dy);
	plr->falling = 1;
}

void		check_fall(t_player *plr, t_sector **sectors)
{
	float	nextz;

	if (!plr->fly)
		plr->vlct.z -= 0.05f; /* Add gravity */
	else
		plr->vlct.z += 0.001f;
	nextz = plr->where.z + plr->vlct.z;
	if (plr->vlct.z < 0 && nextz < (*sectors)[plr->sector].floor + plr->eyeheight) // When going down
	{
		plr->where.z = (*sectors)[plr->sector].floor + plr->eyeheight; /* Fix to ground */
		plr->vlct.z = 0;
		plr->falling = 0;
		plr->ground = 1;
	}
	else if (plr->vlct.z > 0 && nextz > (*sectors)[plr->sector].ceil) // When going up
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
