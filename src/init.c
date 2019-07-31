/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 20:18:22 by ggavryly          #+#    #+#             */
/*   Updated: 2019/07/31 20:18:23 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	init_sdl(t_sdl_main *sdl)
{
	sdl->src_rect.x = 0;
	sdl->src_rect.y = 0;
	sdl->src_rect.w = 250;
	sdl->src_rect.h = 200;

	sdl->dst_rect.x = 0;
	sdl->dst_rect.y = 0;
	sdl->dst_rect.w  = sdl->display_mode.w;
	sdl->dst_rect.h = sdl->display_mode.h;

	if (SDL_Init(SDL_INIT_EVERYTHING != 0))
		ERROR("init");
	int request = SDL_GetDesktopDisplayMode(0, &sdl->display_mode);
	sdl->window = SDL_CreateWindow("Gena_test",0,0,WIN_WIDTH, WIN_HEIGHT,  SDL_WINDOW_SHOWN);
	if (!sdl->window)
		ERROR("win");
	sdl->renderer = SDL_CreateRenderer(sdl->window, -1, SDL_RENDERER_ACCELERATED);
	if (!sdl->renderer)
		ERROR("renderer");
}

