/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_fts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibohun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:05:45 by ibohun            #+#    #+#             */
/*   Updated: 2019/08/12 16:07:41 by ibohun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
**	Needs to prevent leaks on exit
*/

void	UnloadData(t_sector **sectors, t_player *plr)
{
	for (unsigned a = 0; a < plr->num_scts; ++a)
		free((*sectors)[a].vertex);
	for (unsigned a = 0; a < plr->num_scts; ++a)
		free((*sectors)[a].neighbors);
	free(*sectors);
	*sectors = NULL;
	plr->num_scts = 0;
}

/*
** vline:
** Draw a vertical line on screen, with a different color pixel in top & bottom
*/

float		percentage(int start, int end, int curr)
{
	float place;
	float dist;

	place = curr - start;
	dist = end - start;
	return ((dist == 0) ? 1.0 : (place / dist));
}

int		color_transoform(int	color, float percent)
{
	int		rgb[3];

	rgb[RED] = ((color >> 16) & 0xFF) * percent;
	rgb[GREEN] = ((color >> 8) & 0xFF) * percent;
	rgb[BLUE] = ((color) & 0xFF) * percent;
	color = ((rgb[RED] << 16) | (rgb[GREEN] << 8) | rgb[BLUE]);

	return (color);
}

void	render(int draw_mode ,int texture_num, t_player *p, t_draw_screen_calc *ds)
{
	if (draw_mode == TOP_PORTAL_WALL)
		vline2(ds->i->cya, ds->i->cnya - 1,
			   scaler_init(ds->i->ya, ds->i->cya, ds->i->yb, 0,
						   p->sdl->textures->arr_tex[2]->w - 1), ds->i->txtx, p, ds, texture_num);
	else if (draw_mode == BOTTOM_PORTAL_WALL)
		vline2(ds->i->cnyb + 1, ds->i->cyb,
			   scaler_init(ds->i->ya, ds->i->cnyb + 1, ds->i->yb, 0,
						   p->sdl->textures->arr_tex[2]->w - 1), ds->i->txtx, p, ds,texture_num);
	else if (draw_mode == FULL_WALL)
		vline2(ds->i->cya, ds->i->cyb,
			   scaler_init(ds->i->ya, ds->i->cya, ds->i->yb, 0,
						   p->sdl->textures->arr_tex[2]->w - 1), ds->i->txtx, p, ds, 5);
	else if (draw_mode == CEIL)
		vline(ds->i->y_top[ds->it->x], ds->i->cya - 1, 0xFFFFFF, p, ds);
	else if (draw_mode == FLOOR)
		vline(ds->i->cyb + 1, ds->i->y_bottom[ds->it->x], 0x32a852, p, ds);
}

void vline2(int y1,int y2, t_scaler ty, unsigned txtx, t_player *p, t_draw_screen_calc *ds, int tn)
{
	uint32_t *pix = (uint32_t *) p->sdl->win_surface->pixels;
	y1 = clamp(y1, 0, H-1);
	y2 = clamp(y2, 0, H-1);
	pix += y1 * W + ds->it->x;

	for(int y = y1; y <= y2; ++y)
	{
		unsigned txty = scaler_next(&ty);
		*pix = color_transoform(ft_get_pixel(p->sdl->textures->arr_tex[tn], txtx % p->sdl->textures->arr_tex[tn]->w, txty % p->sdl->textures->arr_tex[tn]->w), ds->f->perc_light);
		pix += W;
	}
}

void	vline(int y1, int y2, int color, t_player *plr, t_draw_screen_calc *ds)
{
	int x = ds->it->x;

	uint32_t *pix = (uint32_t *)plr->sdl->win_surface->pixels;
	y1 = clamp(y1, 0, H - 1);
	y2 = clamp(y2, 0, H - 1);
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

int		exit_doom(t_sector **sectors, t_player *plr)
{
	UnloadData(&(*sectors), &(*plr));
	SDL_Quit();
	exit(0);
}

int scaler_next(t_scaler *i)
{
	for(i->cache += i->fd; i->cache >= i->ca; i->cache -= i->ca)
		i->result += i->bop;
	return (i->result);
}

t_scaler scaler_init(int a, int b, int c, int d, int f)
{
	t_scaler	s;

	s.result = d + (b-1 - a) * (f-d) / (c-a);
	s.bop = ((f<d) ^ (c<a)) ? -1 : 1;
	s.fd = abs(f-d);
	s.ca = abs(c-a);
	s.cache = (int)((b-1-a) * abs(f-d)) % abs(c-a);

	return (s);
}

int		ft_get_pixel(SDL_Surface *sur, uint32_t x, uint32_t y)
{
	int32_t		*pixel;

	pixel = 0;
	pixel = sur->pixels + y * sur->pitch + x * sur->format->BytesPerPixel;
	return (*pixel);
}
