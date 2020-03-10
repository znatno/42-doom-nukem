/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_fts2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 12:47:56 by ggavryly          #+#    #+#             */
/*   Updated: 2019/09/08 12:48:06 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		draw_ceil_floor(t_draw_screen_calc *ds, t_player *p, t_tex_i tex_i)
{
	int y;

	y = ds->i->y_top[ds->it->x];
	while (++y <= ds->i->y_bottom[ds->it->x])
	{
		if (y >= ds->i->cya && y <= ds->i->cyb)
		{
			y = ds->i->cyb;
			continue;
		}
		ds->f->hei = y < ds->i->cya ? ds->f->yceil : ds->f->yfloor;
		ds->f->mapz = ds->f->hei * H * V_FOV / ((H / 2 - (float)y)
												- p->yaw * H * V_FOV);
		ds->f->mapx = ds->f->mapz * (W / 2 - (float)ds->it->x) / (W * H_FOV);
		ds->f->rtx = ds->f->mapz * ds->f->pcos + ds->f->mapx * ds->f->psin;
		ds->f->rtz = ds->f->mapz * ds->f->psin - ds->f->mapx * ds->f->pcos;
		ds->f->mapx = ds->f->rtx + p->where.x;
		ds->f->mapz = ds->f->rtz + p->where.y;
		ds->i->txtx1 = (unsigned int)(ds->f->mapx * 256);
		ds->i->txtz = (unsigned int)(ds->f->mapz * 256);
		if (y < ds->i->cya)
			pix1(p, ds, y, tex_i);
		else
			pix2(p, ds, y, tex_i);
	}
}

int			exit_doom(t_game *g)
{
	unload_data(g);
	SDL_Quit();
	TTF_Quit();
	exit(0);
}

int			scr_nxt(t_scaler *i)
{
	i->cache += i->fd;
	while (i->cache >= i->ca)
	{
		i->result += i->bop;
		i->cache -= i->ca;
	}
	return (i->result);
}

t_scaler	scalar_create(t_scri r)
{
	t_scaler	s;

	s.result = r.d + (r.b - 1 - r.a) * (r.f - r.d) / (r.c - r.a);
	s.bop = ((r.f < r.d) ^ (r.c < r.a)) ? -1 : 1;
	s.fd = abs(r.f - r.d);
	s.ca = abs(r.c - r.a);
	s.cache = (int)((r.b - 1 - r.a) * abs(r.f - r.d)) % abs(r.c - r.a);
	return (s);
}

int			ft_get_pixel(SDL_Surface *sur, uint32_t x, uint32_t y)
{
	int		*pixel;

	pixel = sur->pixels + y * sur->pitch + x * sur->format->BytesPerPixel;
	return (*pixel);
}
