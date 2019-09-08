/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighter_and_sounds2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprokysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:16:22 by tprokysh          #+#    #+#             */
/*   Updated: 2019/09/06 16:16:23 by tprokysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		events1(const uint8_t *kstate, SDL_Event ev, t_game *g,
					t_sounds *sounds)
{
	if (kstate[SDL_SCANCODE_ESCAPE] || ev.type == SDL_QUIT)
		exit_doom(g);
	g->plr.key.w = kstate[SDL_SCANCODE_W];
	g->plr.key.a = kstate[SDL_SCANCODE_A];
	g->plr.key.s = kstate[SDL_SCANCODE_S];
	g->plr.key.d = kstate[SDL_SCANCODE_D];
	g->plr.draw_look = kstate[SDL_SCANCODE_L];
	if (ev.button.button == SDL_SCANCODE_1)
	{
		g->wpn.sprite_counter = 1;
		g->plr.light = 24;
		g->wpn.type = 1;
	}
	if (ev.button.button == SDL_SCANCODE_2)
	{
		g->wpn.sprite_counter = 1;
		g->wpn.type = 2;
	}
	help_events1(ev, &g, sounds);
}

void		events(t_game *g, t_sounds *sounds)
{
	const uint8_t	*kstate;
	SDL_Event		ev;

	kstate = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&ev))
	{
		events1(kstate, ev, g, sounds);
		if (ev.type == SDL_KEYDOWN)
			events2(ev, g, sounds);
		if (g->sectors[g->plr.sector].ceil < g->plr.where.z + HEAD_MARGIN)
			g->plr.ducking = true;
		if (g->plr.ducking)
		{
			g->plr.falling = 1;
			g->plr.eyeheight = DUCK_H;
		}
		g->plr.run = kstate[SDL_SCANCODE_LSHIFT];
		g->plr.speed = g->plr.run && g->plr.eyeheight != DUCK_H ? 0.28f : 0.20f;
		SDL_PumpEvents();
	}
}

void		draw_cur_lighter_sprite(t_game *g, int width,
									int height, int cur_sprite)
{
	int		x;
	int		y;
	int		x_img;
	float	x_num;
	float	y_num;

	(void)((y *= 0 | (int)(y_num *= 0)));
	while (y < 128 && height < H)
	{
		x = 0;
		x_num = 0;
		x_img = width;
		while (x < 128 - 1 && x_img < W)
		{
			x_num += 0.5;
			x = (int)x_num;
			if (g->wpn.lighter_sprite[cur_sprite][y][x] != 255)
				g->sdl.buffer[height * W + x_img] =
						g->wpn.lighter_sprite[cur_sprite][y][x];
			x_img++;
		}
		y_num += 0.5;
		y = (int)y_num;
		height++;
	}
}

void		draw_cur_pistol_sprite(t_game *g, int width,
								int height, int cur_sprite)
{
	int		x;
	int		y;
	int		x_img;
	float	x_num;
	float	y_num;

	(void)((y *= 0 | (int)(y_num *= 0)));
	while (y < 128 && height < H)
	{
		x = 0;
		x_num = 0;
		x_img = width;
		while (x < 128 - 1 && x_img < W)
		{
			x_num += 0.35;
			x = (int)x_num;
			if (g->wpn.pistol_sprite[cur_sprite][y][x] != 0x000000)
				g->sdl.buffer[height * W + x_img] =
						g->wpn.pistol_sprite[cur_sprite][y][x];
			x_img++;
		}
		y_num += 0.5;
		y = (int)y_num;
		height++;
	}
}

void		draw_lighter(t_game *g)
{
	if (g->wpn.sprite_counter == 1)
		draw_cur_lighter_sprite(g, W - 550, H - 250, 0);
	else if (g->wpn.sprite_counter == 2)
		draw_cur_lighter_sprite(g, W - 550, H - 250, 1);
}
