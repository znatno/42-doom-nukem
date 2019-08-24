/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibohun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 14:49:16 by ggavryly          #+#    #+#             */
/*   Updated: 2019/08/23 19:43:07 by ibohun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	decor_init(t_sdl_main *sdl)
{
	SDL_Surface		**arr_tex;

	arr_tex = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * 1);
	arr_tex[0] = IMG_Load("../textures-doom/ahegao.jpg");

	arr_tex[0] = SDL_ConvertSurfaceFormat(arr_tex[0], SDL_PIXELFORMAT_ABGR32, 0);
//	arr_tex[1] = SDL_ConvertSurfaceFormat(arr_tex[1], SDL_PIXELFORMAT_ARGB32, 0);
	sdl->textures->decor_tex = arr_tex;
}

void	textures_init(t_sdl_main *sdl)
{
	SDL_Surface		**arr_tex;

	arr_tex = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * 6);
	arr_tex[0] = IMG_Load("../textures-doom/brick.jpg");
	arr_tex[1] = IMG_Load("../textures-doom/steel_0.jpg");
	arr_tex[2] = IMG_Load("../textures-doom/steel_1.jpg");
	arr_tex[3] = IMG_Load("../textures-doom/wall_grey.jpg");
	arr_tex[4] = IMG_Load("../textures-doom/wood_white_0.jpg");
	arr_tex[5] = IMG_Load("../textures-doom/wood_white_1.jpg");

	arr_tex[0] = SDL_ConvertSurfaceFormat(arr_tex[0], SDL_PIXELFORMAT_ARGB32, 0);
	arr_tex[1] = SDL_ConvertSurfaceFormat(arr_tex[1], SDL_PIXELFORMAT_ARGB32, 0);
	arr_tex[2] = SDL_ConvertSurfaceFormat(arr_tex[2], SDL_PIXELFORMAT_ARGB32, 0);
	arr_tex[3] = SDL_ConvertSurfaceFormat(arr_tex[3], SDL_PIXELFORMAT_ARGB32, 0);
	arr_tex[4] = SDL_ConvertSurfaceFormat(arr_tex[4], SDL_PIXELFORMAT_ARGB32, 0);
	arr_tex[5] = SDL_ConvertSurfaceFormat(arr_tex[5], SDL_PIXELFORMAT_ARGB32, 0);
	sdl->textures->arr_tex = arr_tex;
	decor_init(sdl);
	decor_texture(sdl,5,0, (t_xy_uint){.x = 50, .y = 50});
}
