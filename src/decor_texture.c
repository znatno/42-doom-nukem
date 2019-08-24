/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decor_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 16:37:43 by ggavryly          #+#    #+#             */
/*   Updated: 2019/08/24 16:37:45 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"


void	get_pixels_decor(uint32_t d_n, t_sdl_main *sdl)
{
	uint32_t *buf;
	uint32_t size[2];
	char it[2];

	it[Y_0] = 0;
	buf = sdl->textures->decor_tex[d_n]->pixels;
	size[0] = sdl->textures->decor_tex[d_n]->w;
	size[1] = sdl->textures->decor_tex[d_n]->h;
	while (it[Y_0] < size[1])
	{
		it[X_0] = 0;
		while (it[X_0] < size[0])
		{
			printf("%u ", buf[Y_0 * size[0] + X_0]);
			it[X_0]++;
		}
		printf("\n");
		it[Y_0]++;
	}
}


void	decor_texture(t_sdl_main *sdl, uint32_t t_n, uint32_t d_n, t_xy_uint cords)
{
	uint32_t size[4];
	uint32_t it[4];
	uint32_t *buffer[2];

	size[0] = sdl->textures->arr_tex[t_n]->w;
	size[1] = sdl->textures->arr_tex[t_n]->h;
	size[2] = sdl->textures->decor_tex[d_n]->w;
	size[3] = sdl->textures->decor_tex[d_n]->h;
	get_pixels_decor(d_n, sdl);
	if (cords.x >= size[0] || cords.y >= size[1])
		return;
	else
	{
		it[Y_0] = cords.y;
		buffer[0] = (uint32_t *)sdl->textures->arr_tex[t_n]->pixels;
		buffer[1] = (uint32_t *)sdl->textures->decor_tex[d_n]->pixels;
		while (it[Y_0] < size[1] && it[Y_1] < size[3])
		{
			it[X_0] = cords.x;
			it[X_1] = 0;
			while (it[X_0] < size[0] && it[X_1] < size[2])
			{
				if (buffer[1][it[Y_1] * size[2] + X_1] != 0)
					buffer[0][it[Y_0] * size[0] + it[X_0]] = buffer[1][it[Y_1] * size[2] + X_1];
				it[X_0]++;
				it[X_1]++;
			}
			it[Y_0]++;
			it[Y_1]++;
		}
	}
}
