/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screen3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 13:09:59 by ggavryly          #+#    #+#             */
/*   Updated: 2019/09/08 13:10:01 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	find_intersect3(t_draw_screen_calc *ds)
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

void	find_intersect2(t_draw_screen_calc *ds)
{
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
		find_intersect3(ds);
}

void	find_intersect1(t_draw_screen_calc *ds)
{
	ds->f->nearz = 1e-4f;
	ds->f->farz = 5;
	ds->f->nearside = 1e-5f;
	ds->f->farside = 20.f;
	ds->s->i1 = crossing((t_math) {.xxx1 = ds->f->tx1, .yyy1 = ds->f->tz1,
			.xxx2 = ds->f->tx2, .yyy2 = ds->f->tz2,
			.xxx3 = -ds->f->nearside, .yyy3 = ds->f->nearz,
			.xxx4 = -ds->f->farside, .yyy4 = ds->f->farz});
	ds->s->i2 = crossing((t_math) {.xxx1 = ds->f->tx1, .yyy1 = ds->f->tz1,
			.xxx2 = ds->f->tx2, .yyy2 = ds->f->tz2,
			.xxx3 = ds->f->nearside, .yyy3 = ds->f->nearz,
			.xxx4 = ds->f->farside, .yyy4 = ds->f->farz});
	ds->s->org1.x = ds->f->tx1;
	ds->s->org1.y = ds->f->tz1;
	ds->s->org2.x = ds->f->tx2;
	ds->s->org2.y = ds->f->tz2;
}

void	find_intersect(t_draw_screen_calc *ds)
{
	find_intersect1(ds);
	find_intersect2(ds);
	if (fabsf(ds->f->tx2 - ds->f->tx1) > fabsf(ds->f->tz2 - ds->f->tz1))
	{
		ds->i->u0 = (int)((ds->f->tx1 - ds->s->org1.x) * 600 /
				(ds->s->org2.x - ds->s->org1.x));
		ds->i->u1 = (int)((ds->f->tx2 - ds->s->org1.x) * 600 /
				(ds->s->org2.x - ds->s->org1.x));
	}
	else
	{
		ds->i->u0 = (int)((ds->f->tz1 - ds->s->org1.y) * 600 /
				(ds->s->org2.y - ds->s->org1.y));
		ds->i->u1 = (int)((ds->f->tz2 - ds->s->org1.y) * 600 /
				(ds->s->org2.y - ds->s->org1.y));
	}
}

void	perspective(t_draw_screen_calc *ds)
{
	ds->f->xscale1 = HFOV / ds->f->tz1;
	ds->f->yscale1 = VFOV / ds->f->tz1;
	ds->i->x1 = W / 2 - (int)(ds->f->tx1 * ds->f->xscale1);
	ds->f->xscale2 = HFOV / ds->f->tz2;
	ds->f->yscale2 = VFOV / ds->f->tz2;
	ds->i->x2 = W / 2 - (int)(ds->f->tx2 * ds->f->xscale2);
}
