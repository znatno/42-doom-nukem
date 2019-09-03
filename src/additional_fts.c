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

void		unload_data(t_game *g)
{
	unsigned a;

	a = 0;
	while (a < g->plr.num_scts)
		free(g->sectors[a++].vertex);
	a = 0;
	while (a < g->plr.num_scts)
		free(g->sectors[a++].neighbors);
	free(g->sectors);
	g->sectors = NULL;
	g->plr.num_scts = 0;
	a = 0;
	while (a < FONTS_NUM)
		clear_font(&g->fonts[a++]);
}

float		percentage(int start, int end, int curr)
{
	float place;
	float dist;

	place = curr - start;
	dist = end - start;
	return ((dist == 0) ? 1.0 : (place / dist));
}

int			color_transoform(int color, float percent)
{
	int		rgb[3];

	rgb[RED] = ((color >> 8) & 0xFF) * percent;
	rgb[GREEN] = ((color >> 16) & 0xFF) * percent;
	rgb[BLUE] = ((color >> 24) & 0xFF) * percent;
	color = ((rgb[BLUE] << 24) | (rgb[GREEN] << 16) | rgb[RED] << 8);
	return (color);
}

void		draw_ceil_floor(t_draw_screen_calc *ds, t_player *p, t_tex_i tex_i)
{
	uint32_t *pix;
	int y;

	y = ds->i->y_top[ds->it->x];
	pix = (uint32_t *)p->sdl->buffer;
	while (y <= ds->i->y_bottom[ds->it->x])
	{
		++y;
		if (y >= ds->i->cya && y <= ds->i->cyb)
			y = ds->i->cyb;
		else
		{
			ds->f->hei = y < ds->i->cya ? ds->f->yceil : ds->f->yfloor;
			ds->f->mapz = ds->f->hei * H * V_FOV / ((H / 2 - (float) y) - p->yaw * H * V_FOV);
			ds->f->mapx = ds->f->mapz * (W / 2 - (float) ds->it->x) / (W * H_FOV);
			ds->f->rtx = ds->f->mapz * ds->f->pcos + ds->f->mapx * ds->f->psin;
			ds->f->rtz = ds->f->mapz * ds->f->psin - ds->f->mapx * ds->f->pcos;
			ds->f->mapx = ds->f->rtx + p->where.x;
			ds->f->mapz = ds->f->rtz + p->where.y;
			ds->i->txtx1 = (unsigned int) (ds->f->mapx * 256);
			ds->i->txtz = (unsigned int) (ds->f->mapz * 256);
		if (y < ds->i->cya)
			pix[y * W + ds->it->x] = color_transoform(ft_get_pixel(p->sdl->textures->arr_tex[tex_i.ceil], ds->i->txtx1 % p->sdl->textures->arr_tex[tex_i.ceil]->w, ds->i->txtz % p->sdl->textures->arr_tex[tex_i.ceil]->h),ds->f->perc_light);
		else
			pix[y * W + ds->it->x] = color_transoform(ft_get_pixel(p->sdl->textures->arr_tex[tex_i.floor], ds->i->txtx1 % p->sdl->textures->arr_tex[tex_i.floor]->w, ds->i->txtz % p->sdl->textures->arr_tex[tex_i.floor]->h), ds->f->perc_light);
		}
	}
/*	for(int y = ds->i->y_top[ds->it->x]; y <= ds->i->y_bottom[ds->it->x]; ++y)
	{
		if (y >= ds->i->cya && y <= ds->i->cyb)
		{
			y = ds->i->cyb;
			continue;
		}
		ds->f->hei = y < ds->i->cya ? ds->f->yceil : ds->f->yfloor;
		ds->f->mapz = ds->f->hei * H * V_FOV / ((H / 2 - (float)y) - p->yaw * H * V_FOV);
		ds->f->mapx = ds->f->mapz * (W / 2 - (float)ds->it->x) / (W * H_FOV);
		ds->f->rtx = ds->f->mapz * ds->f->pcos + ds->f->mapx * ds->f->psin;
		ds->f->rtz = ds->f->mapz * ds->f->psin - ds->f->mapx * ds->f->pcos;
		ds->f->mapx = ds->f->rtx + p->where.x;
		ds->f->mapz = ds->f->rtz + p->where.y;
		ds->i->txtx1 = (unsigned int)(ds->f->mapx * 256);
		ds->i->txtz = (unsigned int)(ds->f->mapz * 256);
		if (y < ds->i->cya)
			pix[y * W + ds->it->x] = color_transoform(ft_get_pixel(p->sdl->textures->arr_tex[tex_i.ceil], ds->i->txtx1 % p->sdl->textures->arr_tex[tex_i.ceil]->w, ds->i->txtz % p->sdl->textures->arr_tex[tex_i.ceil]->h),ds->f->perc_light);
		else
			pix[y * W + ds->it->x] = color_transoform(ft_get_pixel(p->sdl->textures->arr_tex[tex_i.floor], ds->i->txtx1 % p->sdl->textures->arr_tex[tex_i.floor]->w, ds->i->txtz % p->sdl->textures->arr_tex[tex_i.floor]->h), ds->f->perc_light);
	}*/
}

void		render(int draw_mode ,t_tex_i tex_i, t_player *p, t_draw_screen_calc *ds)
{
	if (draw_mode == TOP_PORTAL_WALL)
		vline2(ds->i->cya, ds->i->cnya - 1,
			   scalar_init(ds->i->ya, ds->i->cya, ds->i->yb, 0,
						   p->sdl->textures->arr_tex[tex_i.wall]->w - 1), ds->i->txtx, p, ds, tex_i.wall);
	else if (draw_mode == BOTTOM_PORTAL_WALL)
		vline2(ds->i->cnyb + 1, ds->i->cyb,
			   scalar_init(ds->i->ya, ds->i->cnyb + 1, ds->i->yb, 0,
						   p->sdl->textures->arr_tex[tex_i.wall]->w - 1), ds->i->txtx, p, ds,tex_i.wall);
	else if (draw_mode == FULL_WALL)
		vline2(ds->i->cya, ds->i->cyb,
			   scalar_init(ds->i->ya, ds->i->cya, ds->i->yb, 0,
						   p->sdl->textures->arr_tex[tex_i.wall]->w - 1), ds->i->txtx, p, ds, tex_i.wall);
	else if (draw_mode == CEIL || draw_mode == FLOOR)
		draw_ceil_floor(ds, p, tex_i);
}

void 		vline2(int y1,int y2, t_scaler ty, unsigned txtx, t_player *p, t_draw_screen_calc *ds, int tn)
{
	uint32_t *pix;

	pix = (uint32_t *)p->sdl->buffer;
	y1 = CLAMP(y1, 0, H-1);
	y2 = CLAMP(y2, 0, H-1);
	pix += y1 * W + ds->it->x;
	for(int y = y1; y <= y2; ++y)
	{
		unsigned txty = scaler_next(&ty);
		*pix = color_transoform(ft_get_pixel(p->sdl->textures->arr_tex[tn],
						txtx % p->sdl->textures->arr_tex[tn]->w,
						txty % p->sdl->textures->arr_tex[tn]->w),
						ds->f->perc_light);
		pix += W;
	}
}

void		vline(int y1, int y2, int color, t_player *plr, t_draw_screen_calc *ds)
{
	int x;
	uint32_t *pix;

	x = ds->it->x;
	pix = (uint32_t *)plr->sdl->buffer;
	y1 = CLAMP(y1, 0, H - 1);
	y2 = CLAMP(y2, 0, H - 1);
	if (y2 == y1)
		pix[y1 * W + x] = BLACK_COLOR; //нижня межа вікна
	else if (y2 > y1)
	{
		pix[y1 * W + x] = color; //проміжок секторів
		if (y1 == 0 || y1 == 1)
			pix[y1 * W + x] = BLACK_COLOR; //верхня межа вікна
		for (int y = y1 + 1; y <= y2; ++y)
		{
			pix[y * W + x] = color;
		}
		pix[y2 * W + x] = color;
	}
}

/*
**	Quit
*/

int			exit_doom(t_game *g)
{
	if (g->error)
		ft_putendl_fd("text", 2);
	else
		ft_putendl("text");
	unload_data(g);
	SDL_Quit();
	TTF_Quit();
	exit(0);
}

int			scaler_next(t_scaler *i)
{
	for(i->cache += i->fd; i->cache >= i->ca; i->cache -= i->ca)
		i->result += i->bop;
	return (i->result);
}

t_scaler	scalar_init(int a, int b, int c, int d, int f)
{
	t_scaler	s;

	s.result = d + (b-1 - a) * (f-d) / (c-a);
	s.bop = ((f < d) ^ (c < a)) ? -1 : 1;
	s.fd = abs(f-d);
	s.ca = abs(c-a);
	s.cache = (int)((b-1-a) * abs(f-d)) % abs(c-a);

	return (s);
}

int			ft_get_pixel(SDL_Surface *sur, uint32_t x, uint32_t y)
{
	int		*pixel;

	pixel = sur->pixels + y * sur->pitch + x * sur->format->BytesPerPixel;
	return (*pixel);
}
