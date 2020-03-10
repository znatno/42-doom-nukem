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

void	init_decor(uint32_t size[1][4], uint32_t *buf[1][2],
		t_sdl_main *sdl, t_ui dt)
{
	(*size)[0] = sdl->textures->arr_tex[dt.t_n]->w;
	(*size)[1] = sdl->textures->arr_tex[dt.t_n]->h;
	(*size)[2] = sdl->textures->arr_tex[dt.d_n]->w;
	(*size)[3] = sdl->textures->arr_tex[dt.d_n]->h;
	(*buf)[0] = (uint32_t *)sdl->textures->arr_tex[dt.t_n]->pixels;
	(*buf)[1] = (uint32_t *)sdl->textures->arr_tex[dt.d_n]->pixels;
}

void	decor_texture(t_sdl_main *sdl, uint32_t t_n, uint32_t d_n,
		t_xy_uint cords)
{
	uint32_t size[4];
	uint32_t it[4];
	uint32_t *buffer[2];

	init_decor(&size, &buffer, sdl, (t_ui){.t_n = t_n, .d_n = d_n});
	if (cords.x >= size[0] || cords.y >= size[1])
		return ;
	else
	{
		it[Y_0] = cords.y;
		while (it[Y_0] < size[1] && it[Y_1] < size[3])
		{
			it[X_0] = cords.x;
			it[X_1] = 0;
			while (it[X_0] < size[0] && it[X_1] < size[2])
			{
				if (buffer[1][it[Y_1] * size[2] + it[X_1]] != 0)
					buffer[0][it[Y_0] * size[0] + it[X_0]] = buffer[1][it[Y_1]
														* size[2] + it[X_1]++];
				it[X_0]++;
			}
			it[Y_0]++;
			it[Y_1]++;
		}
	}
}

void	help_events1(SDL_Event ev, t_game **g, t_sounds *sounds)
{
	if (ev.type == SDL_MOUSEBUTTONDOWN &&
			(*g)->wpn.sprite_counter == 1 && (*g)->wpn.type == 1)
	{
		Mix_PlayChannel(7, sounds->gun_fire, 0);
		(*g)->wpn.sprite_counter += 1;
	}
	if (ev.type == SDL_MOUSEBUTTONDOWN && (*g)->wpn.sprite_counter == 1
		&& (*g)->wpn.type == 2)
	{
		if (!Mix_Playing(6))
			Mix_PlayChannel(6, sounds->lighter, 0);
		if ((*g)->wpn.sprite_counter == 1)
			(*g)->wpn.sprite_counter += 1;
		(*g)->plr.light = 16;
	}
	if (ev.type == SDL_MOUSEBUTTONUP && (*g)->wpn.sprite_counter == 2
		&& (*g)->wpn.type == 2)
	{
		if (!Mix_Playing(7))
			Mix_PlayChannel(7, sounds->lighter_close, 0);
		(*g)->wpn.sprite_counter = 1;
		(*g)->plr.light = 24;
	}
}
