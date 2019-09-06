/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibohun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 20:18:22 by ggavryly          #+#    #+#             */
/*   Updated: 2019/08/23 19:40:02 by ibohun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	init_sdl(t_game *g)
{
	if (SDL_Init(SDL_INIT_EVERYTHING != 0) || TTF_Init() == -1)
		printf("SDL_Init || TTF_Init error");
	g->sdl.window = SDL_CreateWindow("Doom Nukem", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, W, H, SDL_WINDOW_SHOWN);
	g->sdl.renderer = SDL_CreateRenderer(g->sdl.window, 0, 0);
	g->sdl.texture = SDL_CreateTexture(g->sdl.renderer, SDL_PIXELFORMAT_ARGB32,
			SDL_TEXTUREACCESS_STREAMING, W, H);
	g->sdl.buffer = (int *)malloc(sizeof(int) * W * H);
	if (!g->sdl.window || !g->sdl.renderer || !g->sdl.buffer || !g->sdl.texture)
		exit_doom(g);
	g->sdl.textures = (t_textures*)malloc(sizeof(t_textures));
	SDL_UpdateTexture(g->sdl.texture, NULL, g->sdl.buffer, W * (sizeof(int)));
	SDL_RenderCopy(g->sdl.renderer, g->sdl.texture, NULL, NULL);
	SDL_RenderPresent(g->sdl.renderer);
	g->plr.light = 24;
	SDL_Delay(1000);
}
