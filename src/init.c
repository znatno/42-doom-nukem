/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibohun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 20:18:22 by ggavryly          #+#    #+#             */
/*   Updated: 2019/08/18 23:10:05 by ibohun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	init_sdl(t_sdl_main *sdl)
{
	if (SDL_Init(SDL_INIT_EVERYTHING != 0) || TTF_Init() == -1)
		printf("SDL_Init || TTF_Init error");
	sdl->window = SDL_CreateWindow("Doom Nukem", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, W, H,  SDL_WINDOW_SHOWN);
	sdl->renderer = SDL_CreateRenderer(sdl->window, 0, 0);
	sdl->texture = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_ARGB32,
			SDL_TEXTUREACCESS_STREAMING, W, H);
	sdl->buffer = (int *)malloc(sizeof(int) * W * H);
	if (!sdl->window || !sdl->renderer || !sdl->buffer || !sdl->texture)
	{
		printf("SDL error");
		exit_doom(NULL);
	}
}
