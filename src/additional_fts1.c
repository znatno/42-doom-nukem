/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_fts1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 12:46:20 by ggavryly          #+#    #+#             */
/*   Updated: 2019/09/08 12:46:22 by ggavryly         ###   ########.fr       */
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

void		pix2(t_player *p, t_draw_screen_calc *ds, int y, t_tex_i tex_i)
{
	uint32_t *pix;

	pix = (uint32_t *)p->sdl->buffer;
	pix[y * W + ds->it->x] = color_transoform(ft_get_pixel(
			p->sdl->textures->arr_tex[tex_i.floor],
					ds->i->txtx1 % p->sdl->textures->arr_tex[tex_i.floor]->w,
					ds->i->txtz % p->sdl->textures->arr_tex[tex_i.floor]->h),
					ds->f->perc_light);
}

void		pix1(t_player *p, t_draw_screen_calc *ds, int y, t_tex_i tex_i)
{
	uint32_t *pix;

	pix = (uint32_t *)p->sdl->buffer;
	pix[y * W + ds->it->x] = color_transoform(ft_get_pixel(
			p->sdl->textures->arr_tex[tex_i.ceil],
					ds->i->txtx1 % p->sdl->textures->arr_tex[tex_i.ceil]->w,
					ds->i->txtz % p->sdl->textures->arr_tex[tex_i.ceil]->h),
					ds->f->perc_light);
}
