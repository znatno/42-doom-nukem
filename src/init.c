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
	sdl
	if (SDL_Init(SDL_INIT_EVERYTHING != 0))
		ERROR("init");
	int request = SDL_GetDesktopDisplayMode(0, &sdl->display_mode);
	sdl->win = SDL_CreateWindow("Gena_test",0,0,WIN_WIDTH, WIN_HEIGHT,  SDL_WINDOW_SHOWN);
	if (!sdl->win)
		ERROR("win");
	sdl->renderer = SDL_CreateRenderer(sdl->win, -1, SDL_RENDERER_ACCELERATED);
	if (!sdl->renderer)
		ERROR("renderer");
}

