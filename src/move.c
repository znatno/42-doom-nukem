/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibohun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:00:35 by ibohun            #+#    #+#             */
/*   Updated: 2019/08/12 16:28:28 by ibohun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/* MovePlayer(dx,dy): Moves the player by (dx,dy) in the map, and
 * also updates their anglesin/anglecos/sector properties properly.
 */
void	move_player(t_player *plr, t_sector **sectors, float dx, float dy)
{
	t_sector	*sect;
	t_xy		*vert;
	float		px;
	float		py;
	unsigned	s;

	px = plr->where.x;
	py = plr->where.y;
	sect = &(*sectors)[plr->sector];
	vert = sect->vertex;
	s = 0;
	while (s < sect->npoints)
	{
		if (sect->neighbors[s] >= 0 &&
				intersect_box(px, py, px + dx, py + dy, vert[s + 0].x,
							  vert[s + 0].y, vert[s + 1].x, vert[s + 1].y) &&
				point_side(px + dx, py + dy, vert[s + 0].x, vert[s + 0].y,
						   vert[s + 1].x, vert[s + 1].y) < 0)
		{
			//printf("prev sec: %d\n",plr->sector);
			plr->sector = sect->neighbors[s];
			printf("Moved to another sector\n");
			//printf("curr sec: %d\n",plr->sector);
			break;
		}
		s++;
	}
	plr->where.x += dx;
	plr->where.y += dy;
	plr->anglesin = sinf(plr->angle);
	plr->anglecos = cosf(plr->angle);
}

void		chholebump(t_sector **sectors, t_sector sect, const unsigned int *s,
					   t_player *plr, t_xy **vert, float *dx, float *dy)
{
	float hole_low; /* Check where the hole is. */
	float hole_high;

	printf("Check Bump. ");
	hole_low = sect.neighbors[*s] < 0 ? 9e9 : max(sect.floor, (*sectors)[sect.neighbors[*s]].floor);
	hole_high = sect.neighbors[*s] < 0 ? -9e9 : min(sect.ceil, (*sectors)[sect.neighbors[*s]].ceil);
	//printf("hHigh: %f, hLow: %f\n\n", hole_high, hole_low);
	/* Check whether we're bumping into a wall. */
	if (hole_high < plr->where.z + HeadMargin || hole_low > plr->where.z - plr->eyeheight + KneeHeight)
	{
		float xd;
		float yd;

		xd = (*vert)[*s + 1].x - (*vert)[*s + 0].x;
		yd = (*vert)[*s + 1].y - (*vert)[*s + 0].y;

		*dx = xd * (*dx * xd + yd * *dy) / (xd * xd + yd * yd);
		*dy = yd * (*dx * xd + yd * *dy) / (xd * xd + yd * yd);
		//printf("[] xd %f, yd %f, dx %f, dy %f\n\n", xd, yd, *dx, *dy);
		plr->moving = 0;
	}
}

void		do_move(t_player *plr, t_sector **sc)
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
	/*if ((g_x % 10) == 7)
		printf("px: %f, py: %f, dx: %f, dy: %f\n", px, py, dx, dy);*/
	s = -1;
	while (++s < (*sc)[plr->sector].npoints)
	{
		if (intersect_box(px, py, px + dx, py + dy,
						  (*sc)->vert[s + 0].x,
						  (*sc)->vert[s + 0].y,

						  (*sc)->vert[s + 1].x,
						  (*sc)->vert[s + 1].y)

			&& point_side(px + dx, py + dy,
						  (*sc)->vert[s + 0].x,
						  (*sc)->vert[s + 0].y,

						  (*sc)->vert[s + 1].x,
						  (*sc)->vert[s + 1].y) < 0)
		{
			chholebump(sc, (*sc)[plr->sector], &s, plr, &(*sc)->vert, &dx, &dy);
			/*printf("v[s+0] x: %f\nv[s+0] y: %f\nv[s+1] x: %f\nv[s+1] y: "
		   "%f\n\n",
				   (*sc)->vert[s + 0].x + 1,
				   (*sc)->vert[s + 0].y + 1,
				   (*sc)->vert[s + 1].x + 1,
				   (*sc)->vert[s + 1].y + 1);
			printf("player\n");
			printf("x: %f\ny: %f\nz: %f\n",
				   plr->where.x, plr->where.y, plr->where.z);*/
		}
	}
	//printf("prev sec: %d\n",plr->sector);
	move_player(plr, sc, dx, dy);
	//printf("curr sec: %d\n",plr->sector);
	plr->falling = 1;
	//g_x++;
}

void		do_fall(t_player *plr, t_sector **sectors)
{
	float	nextz;

	plr->vlct.z -= 0.05f; /* Add gravity */
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
