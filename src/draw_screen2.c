/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screen2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 13:08:22 by ggavryly          #+#    #+#             */
/*   Updated: 2019/09/08 13:08:27 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	render_walls2(t_draw_screen_calc *d, t_player plr)
{
	d->i->y1a = H / 2 - (int)(YAW(d->f->yceil, d->f->tz1) * d->f->yscale1);
	d->i->y1b = H / 2 - (int)(YAW(d->f->yfloor, d->f->tz1) * d->f->yscale1);
	d->i->y2a = H / 2 - (int)(YAW(d->f->yceil, d->f->tz2) * d->f->yscale2);
	d->i->y2b = H / 2 - (int)(YAW(d->f->yfloor, d->f->tz2) * d->f->yscale2);
	d->i->ny1a = H / 2 - (int)(YAW(d->f->nyceil, d->f->tz1) * d->f->yscale1);
	d->i->ny1b = H / 2 - (int)(YAW(d->f->nyfloor, d->f->tz1) * d->f->yscale1);
	d->i->ny2a = H / 2 - (int)(YAW(d->f->nyceil, d->f->tz2) * d->f->yscale2);
	d->i->ny2b = H / 2 - (int)(YAW(d->f->nyfloor, d->f->tz2) * d->f->yscale2);
	d->i->beginx = MAX(d->i->x1, d->s->now.sx1);
	d->i->endx = MIN(d->i->x2, d->s->now.sx2);
	d->it->x = d->i->beginx;
}

void	render_walls(t_draw_screen_calc *ds, t_sector *sector, t_player plr)
{
	ds->f->yceil = ds->s->sect->ceil - plr.where.z;
	ds->f->yfloor = ds->s->sect->floor - plr.where.z;
	ds->i->neightbor = ds->s->sect->neighbors[ds->it->s];
	ds->f->nyceil = 0;
	ds->f->nyfloor = 0;
	if (ds->i->neightbor >= 0)
	{
		ds->f->nyceil = sector[ds->i->neightbor].ceil - plr.where.z;
		ds->f->nyfloor = sector[ds->i->neightbor].floor - plr.where.z;
	}
	render_walls2(ds, plr);
}

void	ceil_floor_light(t_draw_screen_calc *ds, t_player *p, t_game *g)
{
	ds->i->z = (int)roundf(((ds->it->x - ds->i->x1) * (ds->f->tz2 - ds->f->tz1)
							/ (ds->i->x2 - ds->i->x1) + ds->f->tz1) * p->light);
	ds->i->z = (ds->i->z > 250) ? (250) : (ds->i->z);
	ds->f->perc_light = percentage(250, 0, ds->i->z);
	ds->i->ya = scr_nxt(&ds->s->ya_int);
	ds->i->yb = scr_nxt(&ds->s->yb_int);
	ds->i->cya = CLAMP(ds->i->ya, ds->i->y_top[ds->it->x],
			ds->i->y_bottom[ds->it->x]);
	ds->i->cyb = CLAMP(ds->i->yb, ds->i->y_top[ds->it->x],
			ds->i->y_bottom[ds->it->x]);
	render(CEIL, (t_tex_i){.ceil = 1, .floor = 4}, p, ds);
}

void	render_ceil_floor(t_draw_screen_calc *ds, t_player *p)
{
	ds->i->nya = scr_nxt(&ds->s->nya_int);
	ds->i->nyb = scr_nxt(&ds->s->nyb_int);
	ds->i->cnya = CLAMP(ds->i->nya, ds->i->y_top[ds->it->x],
						ds->i->y_bottom[ds->it->x]);
	ds->i->cnyb = CLAMP(ds->i->nyb, ds->i->y_top[ds->it->x],
						ds->i->y_bottom[ds->it->x]);
	render(TOP_PORTAL_WALL, (t_tex_i){.wall = 5}, p, ds);
	ds->i->y_top[ds->it->x] = CLAMP(MAX(ds->i->cya, ds->i->cnya),
									ds->i->y_top[ds->it->x], H - 1);
	render(BOTTOM_PORTAL_WALL, (t_tex_i){.wall = 5}, p, ds);
	ds->i->y_bottom[ds->it->x] = CLAMP(MIN(ds->i->cyb, ds->i->cnyb),
			0, ds->i->y_bottom[ds->it->x]);
}

void	render_sector(t_draw_screen_calc *ds, t_player *p, t_game *g)
{
	ceil_floor_light(ds, p, g);
	if (ds->i->neightbor >= 0)
		render_ceil_floor(ds, p);
	else
		render(FULL_WALL, (t_tex_i){.wall = 5}, p, ds);
}
