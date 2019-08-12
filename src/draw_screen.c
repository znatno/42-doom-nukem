/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 21:38:26 by ggavryly          #+#    #+#             */
/*   Updated: 2019/08/02 21:38:27 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		main_loop_condition(t_draw_screen_calc *ds)
{
	if (ds->it->start_do == 1)
	{
		ds->it->start_do = 0;
		return (1);
	}
	if (ds->s->head  != ds->s->tail)
		return (1);
	return (0);
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
	if (++ds->s->tail == ds->que + MaxQue)
		ds->s->tail = ds->que;
}

void	rotate_view(t_draw_screen_calc *ds, t_player plr)
{
	/* Acquire the x,y coordinates of the two endpoints (vertices) of this edge of the sector */
	ds->f->vx1 = ds->s->sect->vertex[ds->it->s + 0].x - plr.where.x;
	ds->f->vy1 = ds->s->sect->vertex[ds->it->s + 0].y - plr.where.y;

	ds->f->vx2 = ds->s->sect->vertex[ds->it->s + 1].x - plr.where.x;
	ds->f->vy2 = ds->s->sect->vertex[ds->it->s + 1].y - plr.where.y;

	/* Rotate them around the player's view */
	ds->f->pcos = plr.anglecos;
	ds->f->psin = plr.anglesin;

	ds->f->tx1 = ds->f->vx1 * ds->f->psin - ds->f->vy1 * ds->f->pcos;
	ds->f->tz1 = ds->f->vx1 * ds->f->pcos + ds->f->vy1 * ds->f->psin;

	ds->f->tx2 = ds->f->vx2 * ds->f->psin - ds->f->vy2 * ds->f->pcos;
	ds->f->tz2 = ds->f->vx2 * ds->f->pcos + ds->f->vy2 * ds->f->psin;
}

void	find_intersect(t_draw_screen_calc *ds)
{
	ds->f->nearz = 1e-4f;
	ds->f->farz = 5;
	ds->f->nearside = 1e-5f;
	ds->f->farside = 20.f;
	// Find an intersection between the wall and the approximate edges of player's view
	ds->s->i1 = intersect(ds->f->tx1, ds->f->tz1, ds->f->tx2, ds->f->tz2,
						  -ds->f->nearside, ds->f->nearz, -ds->f->farside,
						  ds->f->farz);
	ds->s->i2 = intersect(ds->f->tx1, ds->f->tz1, ds->f->tx2, ds->f->tz2,
						  ds->f->nearside, ds->f->nearz, ds->f->farside,
						  ds->f->farz);
	if (ds->f->tz1 < ds->f->nearz)
	{
		if (ds->s->i1.y > 0)
		{
			ds->f->tx1 = ds->s->i1.x;
			ds->f->tz1 = ds->s->i1.y;
		} else
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
}

void	perspective(t_draw_screen_calc *ds)
{
	/* Do perspective transformation */
	ds->f->xscale1 = hfov / ds->f->tz1;
	ds->f->yscale1 = vfov / ds->f->tz1;

	ds->i->x1 = W / 2 - (int)(ds->f->tx1 * ds->f->xscale1);

	ds->f->xscale2 = hfov / ds->f->tz2;
	ds->f->yscale2 = vfov / ds->f->tz2;

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
	ds->i->y1a = H / 2 - (int)(Yaw(ds->f->yceil, ds->f->tz1) * ds->f->yscale1);
	ds->i->y1b = H / 2 - (int)(Yaw(ds->f->yfloor, ds->f->tz1) * ds->f->yscale1);
	ds->i->y2a = H / 2 - (int)(Yaw(ds->f->yceil, ds->f->tz2) * ds->f->yscale2);
	ds->i->y2b = H / 2 - (int)(Yaw(ds->f->yfloor, ds->f->tz2) * ds->f->yscale2);
	/* The same for the neighboring sector */
	ds->i->ny1a = H / 2 - (int)(Yaw(ds->f->nyceil, ds->f->tz1) * ds->f->yscale1);
	ds->i->ny1b = H / 2 - (int)(Yaw(ds->f->nyfloor, ds->f->tz1) * ds->f->yscale1);
	ds->i->ny2a = H / 2 - (int)(Yaw(ds->f->nyceil, ds->f->tz2) * ds->f->yscale2);
	ds->i->ny2b = H / 2 - (int)(Yaw(ds->f->nyfloor, ds->f->tz2) * ds->f->yscale2);
	/* Render the wall-> */
	ds->i->beginx = max(ds->i->x1, ds->s->now.sx1);
	ds->i->endx = min(ds->i->x2, ds->s->now.sx2);
	ds->it->x = ds->i->beginx;
}

void	ceil_floor_light(t_draw_screen_calc *ds, t_player *p)
{
	/* Calculate the Z coordinate for this point. (Only used for lighting.) */
	ds->i->z = (int)roundf(((ds->it->x - ds->i->x1) * (ds->f->tz2-ds->f->tz1) / (ds->i->x2-ds->i->x1) + ds->f->tz1) * 8);
	ds->i->z = (ds->i->z > 250) ? (250) : (ds->i->z);
	/* Acquire the Y coordinates for our ceiling & floor for this X coordinate-> Clamp them-> */
	ds->i->ya = (ds->it->x - ds->i->x1) * (ds->i->y2a - ds->i->y1a) / (ds->i->x2 - ds->i->x1) + ds->i->y1a;
	ds->i->cya = clamp(ds->i->ya, ds->i->y_top[ds->it->x], ds->i->y_bottom[ds->it->x]); // top

	ds->i->yb = (ds->it->x - ds->i->x1) * (ds->i->y2b - ds->i->y1b) / (ds->i->x2 - ds->i->x1) + ds->i->y1b;
	ds->i->cyb = clamp(ds->i->yb, ds->i->y_top[ds->it->x], ds->i->y_bottom[ds->it->x]); // bottom

	/* Render ceiling: everything above this sector's ceiling height-> */
	vline(ds->it->x, ds->i->y_top[ds->it->x], ds->i->cya - 1, 0x222222, p);
	/* Render floor: everything below this sector's floor height-> */
	vline(ds->it->x, ds->i->cyb + 1, ds->i->y_bottom[ds->it->x], 0x0000AA, p);
}

void	render_ceil_floor(t_draw_screen_calc *ds, t_player *p)
{
	/* Same for _their_ floor and ceiling */
	ds->i->nya = (ds->it->x - ds->i->x1) * (ds->i->ny2a - ds->i->ny1a) / (ds->i->x2 - ds->i->x1) + ds->i->ny1a;
	ds->i->cnya = clamp(ds->i->nya, ds->i->y_top[ds->it->x], ds->i->y_bottom[ds->it->x]);

	ds->i->nyb = (ds->it->x - ds->i->x1) * (ds->i->ny2b - ds->i->ny1b) / (ds->i->x2 - ds->i->x1) + ds->i->ny1b;
	ds->i->cnyb = clamp(ds->i->nyb, ds->i->y_top[ds->it->x], ds->i->y_bottom[ds->it->x]);

	/* If our ceiling is higher than their ceiling, render upper wall */
	ds->i->r1 = 0x010101 * (255 - ds->i->z); // top portal wall color
	ds->i->r2 = 0x010101 * (255 - ds->i->z); // bottom portal wall color

	vline(ds->it->x, ds->i->cya, ds->i->cnya - 1, (ds->it->x == ds->i->x1 || ds->it->x == ds->i->x2) ? (SEC_COLOR) : (ds->i->r1), p); // Between our and their ceiling

	ds->i->y_top[ds->it->x] = clamp(max(ds->i->cya, ds->i->cnya), ds->i->y_top[ds->it->x], H - 1); // Shrink the remaining window below these ceilings
	/* If our floor is lower than their floor, render bottom wall */
	vline(ds->it->x, ds->i->cnyb + 1, ds->i->cyb, (ds->it->x == ds->i->x1 || ds->it->x == ds->i->x2) ? (SEC_COLOR) : (ds->i->r2), p); // Between their and our floor

	ds->i->y_bottom[ds->it->x] = clamp(min(ds->i->cyb, ds->i->cnyb), 0, ds->i->y_bottom[ds->it->x]); // Shrink the remaining window above these floors
}

void	render_sector(t_draw_screen_calc *ds, t_player *p)
{
	ceil_floor_light(ds, p);
	/* Is there another sector behind this edge? */
	if (ds->i->neightbor >= 0)
		render_ceil_floor(ds, p);
	else
	{
		/* There's no neighbor. Render wall from top (cya = ceiling level) to bottom (cyb = floor level). */
		ds->i->r = 0x010101 * (255 - ds->i->z); // wall color = 0x010101 * (255 - ds->i->z)
		vline(ds->it->x, ds->i->cya, ds->i->cyb, (ds->it->x == ds->i->x1 || ds->it->x == ds->i->x2) ? (SEC_COLOR) : (ds->i->r), p);
	}
}

void	render_sector_walls(t_draw_screen_calc *ds , t_sector *sectore,
							t_item queue[MaxQue], t_player *plr)
{
	render_walls(ds, sectore, *plr);
	for (ds->it->x = ds->i->beginx; ds->it->x <= ds->i->endx; ++ds->it->x)
		render_sector(ds, plr);
	/* Schedule the neighboring sector for rendering within the window formed by this wall-> */
	if (ds->i->neightbor >= 0 && ds->i->endx >= ds->i->beginx && (ds->s->head  + MaxQue + 1 - ds->s->tail) % MaxQue)
	{
		*ds->s->head  = (t_item) {ds->i->neightbor, ds->i->beginx, ds->i->endx};
		if (++ds->s->head == queue + MaxQue)
			ds->s->head = queue;
	}
}

void	draw_screen(t_sector *sector, t_player plr)
{
	t_tmp_iter			it;
	t_item				qe[MaxQue];
	t_calc_tmp_int		i;
	t_calc_tmp_float	f;
	t_calc_tmp_struct	s;
	t_draw_screen_calc	ds;

	ds.i = &i;
	ds.f = &f;
	ds.s = &s;
	ds.it = &it;
	ds.que = qe;

	ds.s->head = ds.que;
	ds.s->tail = ds.que;

	init_draw(&ds, plr);
	if (++ds.s->head  == ds.que + MaxQue)
		ds.s->head = ds.que;
	while (main_loop_condition(&ds))
	{
		pick_sector_slice(&ds);
		if ((unsigned)ds.i->renderedsectors[ds.s->now.sectorno] & 0x21u)
			continue; // Odd = still rendering, 0x20 = give up
		++ds.i->renderedsectors[ds.s->now.sectorno];
		ds.s->sect = &sector[ds.s->now.sectorno];
		/* Render each wall  of this sector that is facing towards player. */
		for (ds.it->s = 0; ds.it->s < ds.s->sect->npoints; ++ds.it->s)
		{
			rotate_view(&ds, plr);
			/* Is the wall at least partially in front of the player? */
			if (ds.f->tz1 <= 0 && ds.f->tz2 <= 0)
				continue;
			/* If it's partially behind the player, clip it against player's view frustrum */
			if (ds.f->tz1 <= 0 || ds.f->tz2 <= 0)
				find_intersect(&ds);
			perspective(&ds);
			if (ds.i->x1 >= ds.i->x2 || ds.i->x2 < ds.s->now.sx1 || ds.i->x1 > ds.s->now.sx2)
				continue; // Only render if it's visible
			/* Acquire the floor and ceiling heights, relative to where the player's view is */
			render_sector_walls(&ds, sector, ds.que, &plr);
		} // for s in sector's edges
		++ds.i->renderedsectors[ds.s->now.sectorno];
	}
}