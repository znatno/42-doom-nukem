/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibohun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 21:38:26 by ggavryly          #+#    #+#             */
/*   Updated: 2019/08/23 18:42:14 by ibohun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void 	debug_update(t_game *g)
{
	SDL_UpdateTexture(g->sdl.texture, NULL, g->sdl.buffer,
					  W * (sizeof(int)));
	SDL_RenderCopy(g->sdl.renderer, g->sdl.texture, NULL, NULL);
	SDL_RenderPresent(g->sdl.renderer);
	SDL_Delay(0);
}

void	print_player_pos(t_player *p)
{
	printf("\n-------------------------------\n");
	printf("| x = %5f | y = %5f |\n", p->where.x, p->where.y);
	printf("-------------------------------\n");
}

void	print_data_ds(t_player *p)
{
	printf("\n---------------------\n");
	printf("| player_x = %5f | player_y = %5f |\n", p->where.x, p->where.y);
	printf("| vlct_x = %5f | vlct_y = %5f | vlct_z = %5f|\n", p->vlct.x, p->vlct.y, p->vlct.z);
	printf("| angle = %f | ang_sin = %5f | ang_cos = %5f | yaw = %5f|\n", p->angle, p->anglesin, p->anglecos, p->yaw);
	printf("| cur_s = %u | num_s = %u|\n", p->sector, p->num_scts);
	printf("| ground = %i | falling = %i | moving = %i | ducking = %i | eyeheight = %5f|\n", p->ground, p->falling, p->moving, p->ducking,p->eyeheight);
	printf("| move_x = %5f | move_y = %5f |\n", p->mv.x, p->mv.y);
	printf("| mouse_aim_x = %i | mouse_aim_y = %i | mouse_aim_yaw = %5f |\n",p->ms.x, p->ms.y, p->ms_yaw);
	printf("---------------------\n");
}

void	init_draw(t_draw_screen_calc *ds, t_player plr)
{
	unsigned		i;

	i = 0;
	ds->it->s = 0;
	ds->it->x = 0;
	ds->it->start_do = 1;
	while (i < W)
	{
		ds->i->y_bottom[i] = H - 1;
		ds->i->y_top[i] = 0;
		i++;
	}
	i = 0;
	ds->i->renderedsectors = (int *)malloc(sizeof(int) * plr.num_scts);
	while (i < plr.num_scts)
	{
		ds->i->renderedsectors[i] = 0;
		i++;
	}
	/* Begin whole-screen rendering from where the player is. */
	*ds->s->head = (t_item){plr.sector, 0, W-1};
}

void	pick_sector_slice(t_draw_screen_calc *ds)
{
	/* Pick a sector & slice from the queue to draw */
	ds->s->now = *ds->s->tail;
	if (++ds->s->tail == ds->queue + MAX_QUE)
		ds->s->tail = ds->queue;
}

void	rotate_view(t_draw_screen_calc *ds, t_game *g)
{
	/* Acquire the x,y coordinates of the two endpoints (vertices) of this edge of the sector */
	ds->f->vx1 = ds->s->sect->vertex[ds->it->s + 0].x - g->plr.where.x;
	ds->f->vy1 = ds->s->sect->vertex[ds->it->s + 0].y - g->plr.where.y;

	ds->f->vx2 = ds->s->sect->vertex[ds->it->s + 1].x - g->plr.where.x;
	ds->f->vy2 = ds->s->sect->vertex[ds->it->s + 1].y - g->plr.where.y;

	/* Rotate them around the player's view */
	ds->f->pcos = g->plr.anglecos;
	ds->f->psin = g->plr.anglesin;

	ds->f->tx1 = ds->f->vx1 * ds->f->psin - ds->f->vy1 * ds->f->pcos;
	ds->f->tz1 = ds->f->vx1 * ds->f->pcos + ds->f->vy1 * ds->f->psin;

	ds->f->tx2 = ds->f->vx2 * ds->f->psin - ds->f->vy2 * ds->f->pcos;
	ds->f->tz2 = ds->f->vx2 * ds->f->pcos + ds->f->vy2 * ds->f->psin;
//	if (g->error == 100)
//	{
//		printf("\nSECTOR: %d\tWALL: %d\n", ds->s->now.sectorno, ds->it->s);
//		printf("tx1: %f\ttz1: %f\ttx2: %f\ttz2: %f\n",
//			   ds->f->tx1, ds->f->tz1, ds->f->tx2, ds->f->tz2);
//	}
}

void	find_intersect(t_draw_screen_calc *ds)
{
	ds->f->nearz = 1e-4f;		// ds->f->nearz = 1e-4f;
	ds->f->farz = 1;			// ds->f->farz = 5;
	ds->f->nearside = 1e-5f;	// ds->f->nearside = 1e-5f;
	ds->f->farside = 20.f;		// ds->f->farside = 20.f;
	//todo тут значення відповідають за відмальовування тому ймовірно тут
	// можна знайти чому відмальовує зайвого чи не відмальовує коли треба

	// Find an intersection between the wall and the !approximate! edges of player's view
	ds->s->i1 = intersect(ds->f->tx1, ds->f->tz1, ds->f->tx2, ds->f->tz2,
						  -ds->f->nearside, ds->f->nearz, -ds->f->farside,
						  ds->f->farz);
	ds->s->i2 = intersect(ds->f->tx1, ds->f->tz1, ds->f->tx2, ds->f->tz2,
						  ds->f->nearside, ds->f->nearz, ds->f->farside,
						  ds->f->farz);
	ds->s->org1.x = ds->f->tx1;
	ds->s->org1.y = ds->f->tz1;

	ds->s->org2.x = ds->f->tx2;
	ds->s->org2.y = ds->f->tz2;
	if (ds->f->tz1 < ds->f->nearz)
	{
		if (ds->s->i1.y > 0)
		{
			ds->f->tx1 = ds->s->i1.x;
			ds->f->tz1 = ds->s->i1.y;
		}
		else
		{
			ds->f->tx1 = ds->s->i2.x;
			ds->f->tz1 = ds->s->i2.y;
		}
	}
	if (ds->f->tz2 < ds->f->nearz)
	{
		if (ds->s->i1.y > 0)
		{
			ds->f->tx2 = ds->s->i1.x;
			ds->f->tz2 = ds->s->i1.y;
		}
		else
		{
			ds->f->tx2 = ds->s->i2.x;
			ds->f->tz2 = ds->s->i2.y;
		}
	}
	if (fabsf(ds->f->tx2 - ds->f->tx1) > fabsf(ds->f->tz2 - ds->f->tz1))
	{
		ds->i->u0 = (int)((ds->f->tx1 - ds->s->org1.x) * 1023 / (ds->s->org2.x - ds->s->org1.x));
		ds->i->u1 =(int)((ds->f->tx2 - ds->s->org1.x) * 1023 / (ds->s->org2.x - ds->s->org1.x));
	}
	else
	{
		ds->i->u0 =(int)((ds->f->tz1 - ds->s->org1.y) * 1023 / (ds->s->org2.y - ds->s->org1.y));
		ds->i->u1 = (int)((ds->f->tz2 - ds->s->org1.y) * 1023 / (ds->s->org2.y - ds->s->org1.y));
	}
}

void	perspective(t_draw_screen_calc *ds)
{
	/* Do perspective transformation */
	ds->f->xscale1 = HFOV / ds->f->tz1;
	ds->f->yscale1 = VFOV / ds->f->tz1;

	ds->i->x1 = W / 2 - (int)(ds->f->tx1 * ds->f->xscale1);

	ds->f->xscale2 = HFOV / ds->f->tz2;
	ds->f->yscale2 = VFOV / ds->f->tz2;

	ds->i->x2 = W / 2 - (int)(ds->f->tx2 * ds->f->xscale2);
}

void	render_walls(t_draw_screen_calc *ds, t_sector *sector, t_player plr)
{
	ds->f->yceil = ds->s->sect->ceil - plr.where.z;
	ds->f->yfloor = ds->s->sect->floor - plr.where.z;
	/* Check the edge type-> neighbor=-1 means wall, other=boundary between two sectors-> */
	ds->i->neightbor = ds->s->sect->neighbors[ds->it->s];
	ds->f->nyceil = 0;
	ds->f->nyfloor = 0;
	if (ds->i->neightbor >= 0) // Is another sector showing through this portal?
	{
		ds->f->nyceil = sector[ds->i->neightbor].ceil - plr.where.z;
		ds->f->nyfloor = sector[ds->i->neightbor].floor - plr.where.z;
	}
	/* Project our ceiling & floor heights into screen coordinates (Y coordinate) */
	ds->i->y1a = H / 2 - (int)(YAW(ds->f->yceil, ds->f->tz1) * ds->f->yscale1);
	ds->i->y1b = H / 2 - (int)(YAW(ds->f->yfloor, ds->f->tz1) * ds->f->yscale1);
	ds->i->y2a = H / 2 - (int)(YAW(ds->f->yceil, ds->f->tz2) * ds->f->yscale2);
	ds->i->y2b = H / 2 - (int)(YAW(ds->f->yfloor, ds->f->tz2) * ds->f->yscale2);
	/* The same for the neighboring sector */
	ds->i->ny1a = H / 2 - (int)(YAW(ds->f->nyceil, ds->f->tz1) * ds->f->yscale1);
	ds->i->ny1b = H / 2 - (int)(YAW(ds->f->nyfloor, ds->f->tz1) * ds->f->yscale1);
	ds->i->ny2a = H / 2 - (int)(YAW(ds->f->nyceil, ds->f->tz2) * ds->f->yscale2);
	ds->i->ny2b = H / 2 - (int)(YAW(ds->f->nyfloor, ds->f->tz2) * ds->f->yscale2);
	/* Render the wall-> */
	ds->i->beginx = MAX(ds->i->x1, ds->s->now.sx1);
	ds->i->endx = MIN(ds->i->x2, ds->s->now.sx2);
	ds->it->x = ds->i->beginx;
}

void	ceil_floor_light(t_draw_screen_calc *ds, t_player *p, t_game *g)
{
	/* Calculate the Z coordinate for this point. (Only used for lighting.) */
	ds->i->z = (int)roundf(((ds->it->x - ds->i->x1) * (ds->f->tz2-ds->f->tz1)
			/ (ds->i->x2-ds->i->x1) + ds->f->tz1) * 8);
	ds->i->z = (ds->i->z > 250) ? (250) : (ds->i->z);

	ds->f->perc_light = percentage(250, 0, ds->i->z); //light percent by ds-i->z
	/* Acquire the Y coordinates for our ceiling & floor for this X coordinate-> Clamp them-> */
	ds->i->ya = (ds->it->x - ds->i->x1) * (ds->i->y2a - ds->i->y1a) / (ds->i->x2 - ds->i->x1) + ds->i->y1a;
	ds->i->cya = clamp(ds->i->ya, ds->i->y_top[ds->it->x], ds->i->y_bottom[ds->it->x]); // top

	ds->i->yb = (ds->it->x - ds->i->x1) * (ds->i->y2b - ds->i->y1b) / (ds->i->x2 - ds->i->x1) + ds->i->y1b;
	ds->i->cyb = clamp(ds->i->yb, ds->i->y_top[ds->it->x], ds->i->y_bottom[ds->it->x]); // bottom

	render(CEIL, 0, p, ds);
//	render(CEIL, 0, p, ds);
//	render(FLOOR, 0, p, ds);
	/* Render ceiling: everything above this sector's ceiling height-> */
//	SDL_UpdateWindowSurface(p->sdl->window);
	vline(ds->it->x, ds->i->y_top[ds->it->x], ds->i->cya - 1, 0x00333333, p);
//	SDL_UpdateWindowSurface(p->sdl->window);
	/* Render floor: everything below this sector's floor height-> */
	vline(ds->it->x, ds->i->cyb + 1, ds->i->y_bottom[ds->it->x], 0x00663333, p);
//	SDL_UpdateWindowSurface(p->sdl->window);
}

void	render_ceil_floor(t_draw_screen_calc *ds, t_player *p)
{
	/* Same for _their_ floor and ceiling */
	ds->i->nya = (ds->it->x - ds->i->x1) * (ds->i->ny2a - ds->i->ny1a) / (ds->i->x2 - ds->i->x1) + ds->i->ny1a;
	ds->i->cnya = CLAMP(ds->i->nya, ds->i->y_top[ds->it->x], ds->i->y_bottom[ds->it->x]);

	ds->i->nyb = (ds->it->x - ds->i->x1) * (ds->i->ny2b - ds->i->ny1b) / (ds->i->x2 - ds->i->x1) + ds->i->ny1b;
	ds->i->cnyb = CLAMP(ds->i->nyb, ds->i->y_top[ds->it->x], ds->i->y_bottom[ds->it->x]);

	render(TOP_PORTAL_WALL, 3, p, ds);
	/* If our ceiling is higher than their ceiling, render upper wall */
//	ds->i->r1 = 0x010101 * (255 - ds->i->z); // top portal wall color
//	ds->i->r2 = 0x010101 * (255 - ds->i->z); // bottom portal wall color

	ds->i->y_top[ds->it->x] = clamp(max(ds->i->cya, ds->i->cnya), ds->i->y_top[ds->it->x], H - 1); // Shrink the remaining window below these ceilings
	render(BOTTOM_PORTAL_WALL, 3, p, ds);
	/* If our floor is lower than their floor, render bottom wall */
//	render(BOTTOM_PORTAL_WALL, 0, p, ds); // Between their and our floor
//	SDL_UpdateWindowSurface(p->sdl->window);
	ds->i->y_bottom[ds->it->x] = clamp(min(ds->i->cyb, ds->i->cnyb), 0, ds->i->y_bottom[ds->it->x]); // Shrink the remaining window above these floors
}

void	render_sector(t_draw_screen_calc *ds, t_player *p, t_game *g)
{
	ceil_floor_light(ds, p, g);
	/* Is there another sector behind this edge? */
	if (ds->i->neightbor >= 0)
		render_ceil_floor(ds, p);
	else
	{
		render(FULL_WALL, 5, p, ds);
		/* There's no neighbor. Render wall from top (cya = ceiling level) to bottom (cyb = floor level). */
//		ds->i->r = 0x010101 * (255 - ds->i->z); // wall color = 0x010101 * (255 - ds->i->z)
//		SDL_UpdateWindowSurface(p->sdl->window);
	}
}

void	render_sector_walls(t_draw_screen_calc *ds , t_sector *sector,
									t_item queue[MAX_QUE], t_game *g)
{
	render_walls(ds, sectore, *plr);
	ds->s->ya_int = scalar_init(ds->i->x1, ds->i->beginx, ds->i->x2, ds->i->y1a,
								ds->i->y2a);
	ds->s->yb_int = scalar_init(ds->i->x1, ds->i->beginx, ds->i->x2, ds->i->y1b,
								ds->i->y2b);
	ds->s->nya_int = scalar_init(ds->i->x1, ds->i->beginx, ds->i->x2,
								 ds->i->ny1a, ds->i->ny2a);
	ds->s->nyb_int = scalar_init(ds->i->x1, ds->i->beginx, ds->i->x2,
								 ds->i->ny1b, ds->i->ny2b);
	for (ds->it->x = ds->i->beginx; ds->it->x <= ds->i->endx; ++ds->it->x)
	{
		ds->i->txtx = (int)((ds->i->u0 * ((ds->i->x2 - ds->it->x) * ds->f->tz2) + ds->i->u1 * ((ds->it->x - ds->i->x1) * ds->f->tz1)) / ((ds->i->x2 - ds->it->x) * ds->f->tz2 + (ds->it->x - ds->i->x1) * ds->f->tz1));
		render_sector(ds, plr);
	}
	/* Schedule the neighboring sector for rendering within the window formed by this wall-> */
	if (ds->i->neightbor >= 0 && ds->i->endx >= ds->i->beginx
		&& (ds->s->head  + MAX_QUE + 1 - ds->s->tail) % MAX_QUE)
	{
		*ds->s->head  = (t_item) {ds->i->neightbor, ds->i->beginx, ds->i->endx};
		if (++ds->s->head == queue + MAX_QUE)
			ds->s->head = queue;
	}
}

void	draw_screen(t_game *g)
{
	t_tmp_iter			it;
	t_item				qe[MAX_QUE];
	t_calc_tmp_int		i;
	t_calc_tmp_float	f;
	t_calc_tmp_struct	s;
	t_draw_screen_calc	ds;

	ds.i = &i;
	ds.f = &f;
	ds.s = &s;
	ds.it = &it;
	ds.queue = qe;

	ds.s->head = ds.queue;
	ds.s->tail = ds.queue;

	init_draw(&ds, g->plr);
	if (++ds.s->head  == ds.queue + MAX_QUE)
		ds.s->head = ds.queue;
	while (ds.s->head != ds.s->tail || ds.it->start_do)
	{
		//SDL_UpdateWindowSurface(plr.sdl->window);
		pick_sector_slice(&ds);
		if ((unsigned)ds.i->renderedsectors[ds.s->now.sectorno] & 0x21u)
			continue; // Odd = still rendering, 0x20 = give up
		++ds.i->renderedsectors[ds.s->now.sectorno];
		ds.s->sect = &g->sectors[ds.s->now.sectorno];

		/* Render each wall of this sector that is facing towards player. */
		//for (ds.it->s = 0; ds.it->s < ds.s->sect->npoints; ++ds.it->s)
		ds.it->s = 0;
		while (ds.it->s < ds.s->sect->npoints)
		{
			rotate_view(&ds, g); //повертаємо вектори стін до куту огляду гравця
			/* Is the wall at least partially in front of the player? */
			if (ds.f->tz1 <= 0 && ds.f->tz2 <= 0)
			{
				ds.it->s++;
				continue;
			}
			/* If it's partially behind the player, clip it against player's view frustrum */
			if (ds.f->tz1 <= 0 || ds.f->tz2 <= 0)
				find_intersect(&ds);
			perspective(&ds);
			if (ds.i->x1 >= ds.i->x2 || ds.i->x2 < ds.s->now.sx1 || ds.i->x1 > ds.s->now.sx2)
			{
				ds.it->s++;
				continue; // Only render if it's visible
			}
			/* Acquire the floor and ceiling heights, relative to where the player's view is */
			render_sector_walls(&ds, g->sectors, ds.queue, g);
			ds.it->s++;
		} // for s in sector's edges
		++ds.i->renderedsectors[ds.s->now.sectorno];
		ds.it->start_do == 1 ? ds.it->start_do = 0 : 0;
	}
}