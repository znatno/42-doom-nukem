#include "doom_nukem.h"

void	render_sector_walls1(t_draw_screen_calc *ds,
							 t_sector *sector, t_game *g)
{
	render_walls(ds, sector, g->plr);
	ds->s->ya_int = scalar_init(ds->i->x1, ds->i->beginx, ds->i->x2, ds->i->y1a,
								ds->i->y2a);
	ds->s->yb_int = scalar_init(ds->i->x1, ds->i->beginx, ds->i->x2, ds->i->y1b,
								ds->i->y2b);
	ds->s->nya_int = scalar_init(ds->i->x1, ds->i->beginx, ds->i->x2,
								 ds->i->ny1a, ds->i->ny2a);
	ds->s->nyb_int = scalar_init(ds->i->x1, ds->i->beginx, ds->i->x2,
								 ds->i->ny1b, ds->i->ny2b);
	ds->it->x = ds->i->beginx;
}

void	render_sector_walls(t_draw_screen_calc *ds , t_sector *sector,
							t_item queue[MAX_QUE], t_game *g)
{
	render_sector_walls1(ds, sector, g);
	while (ds->it->x <= ds->i->endx)
	{
		ds->i->txtx = (int)((ds->i->u0 * ((ds->i->x2 - ds->it->x) * ds->f->tz2)
				+ ds->i->u1 * ((ds->it->x - ds->i->x1) * ds->f->tz1))
						/ ((ds->i->x2 - ds->it->x) * ds->f->tz2
						+ (ds->it->x - ds->i->x1) * ds->f->tz1));
		render_sector(ds, &g->plr, g);
		ds->it->x++;
	}
	if (ds->i->neightbor >= 0 && ds->i->endx >= ds->i->beginx
		&& (ds->s->head  + MAX_QUE + 1 - ds->s->tail) % MAX_QUE)
	{
		*ds->s->head  = (t_item) {ds->i->neightbor, ds->i->beginx, ds->i->endx};
		if (++ds->s->head == queue + MAX_QUE)
			ds->s->head = queue;
	}
}

void	draw_screen2(t_game *g, t_draw_screen_calc ds)
{
	while (ds.it->s < ds.s->sect->npoints)
	{
		rotate_view(&ds, g);
		if (ds.f->tz1 <= 0 && ds.f->tz2 <= 0)
		{
			ds.it->s++;
			continue;
		}
		ds.i->u0 = 0;
		ds.i->u1 = 600;
		if (ds.f->tz1 <= 0 || ds.f->tz2 <= 0)
			find_intersect(&ds);
		perspective(&ds);
		if (ds.i->x1 >= ds.i->x2 || ds.i->x2 < ds.s->now.sx1 ||
			ds.i->x1 > ds.s->now.sx2)
		{
			ds.it->s++;
			continue;
		}
		render_sector_walls(&ds, g->sectors, ds.queue, g);
		ds.it->s++;
	}
	++ds.i->renderedsectors[ds.s->now.sectorno];
	ds.it->start_do == 1 ? ds.it->start_do = 0 : 0;
}

int		draw_screen1(t_game *g, t_draw_screen_calc ds)
{
	pick_sector_slice(&ds);
	if ((unsigned)ds.i->renderedsectors[ds.s->now.sectorno] & 0x21u)
		return (0);
	++ds.i->renderedsectors[ds.s->now.sectorno];
	ds.s->sect = &g->sectors[ds.s->now.sectorno];
	ds.it->s = 0;
	return (1);
}

void	draw_screen(t_game *g, t_draw_screen_calc ds)
{
	t_tmp_iter			it;
	t_item				qe[MAX_QUE];
	t_calc_tmp_int		i;
	t_calc_tmp_float	f;
	t_calc_tmp_struct	s;

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
		if (draw_screen1(g, ds) == 0)
			continue;
		draw_screen2(g, ds);
	}
}
