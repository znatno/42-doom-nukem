/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_fts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibohun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:05:45 by ibohun            #+#    #+#             */
/*   Updated: 2019/08/23 20:05:42 by ibohun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		render_var(int y1, int y2, t_draw_screen_calc *ds)
{
	ds->i->y1 = y1;
	ds->i->y2 = y2;
}

void		render(int dm, t_tex_i tex_i, t_player *p, t_draw_screen_calc *ds)
{
	ds->i->tn = tex_i.wall;
	if (dm == TOP_PORTAL_WALL)
	{
		render_var(ds->i->cya, ds->i->cnya - 1, ds);
		vertl(scalar_create((t_scri) {.a = ds->i->ya, .b = ds->i->
				cya, .c = ds->i->yb, .d = 0, .f = p->sdl->textures->
				arr_tex[tex_i.wall]->w - 1}), ds->i->txtx, p, ds);
	}
	else if (dm == BOTTOM_PORTAL_WALL)
	{
		render_var(ds->i->cnyb + 1, ds->i->cyb, ds);
		vertl(scalar_create((t_scri) {.a = ds->i->ya, .b = ds->i->
				cnyb + 1, .c = ds->i->yb, .d = 0, .f = p->sdl->textures->
				arr_tex[tex_i.wall]->w - 1}), ds->i->txtx, p, ds);
	}
	else if (dm == FULL_WALL)
	{
		render_var(ds->i->cya, ds->i->cyb, ds);
		vertl(scalar_create((t_scri) {.a = ds->i->ya, .b = ds->i->
				cya, .c = ds->i->yb, .d = 0, .f = p->sdl->
				textures->arr_tex[tex_i.wall]->w - 1}), ds->i->txtx, p, ds);
	}
	else if (dm == CEIL || dm == FLOOR)
		draw_ceil_floor(ds, p, tex_i);
}

void		vertl(t_scaler ty, unsigned txtx, t_player *p,
				t_draw_screen_calc *ds)
{
	uint32_t	*pix;
	unsigned	txty;
	int			y;

	y = ds->i->y1;
	pix = (uint32_t *)p->sdl->buffer;
	ds->i->y1 = CLAMP(ds->i->y1, 0, H - 1);
	ds->i->y2 = CLAMP(ds->i->y2, 0, H - 1);
	pix += ds->i->y1 * W + ds->it->x;
	while (y <= ds->i->y2)
	{
		++y;
		txty = scr_nxt(&ty);
		*pix = color_transoform(ft_get_pixel(
				p->sdl->textures->arr_tex[ds->i->tn],
						txtx % p->sdl->textures->arr_tex[ds->i->tn]->w,
						txty % p->sdl->textures->arr_tex[ds->i->tn]->w),
						ds->f->perc_light);
		pix += W;
	}
}
