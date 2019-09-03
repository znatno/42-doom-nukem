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

void	get_decor_textures(SDL_Surface **arr_tex)
{
	arr_tex[0] = IMG_Load("../doom_decor/blood_hand_decor.png");
	arr_tex[1] = IMG_Load("../doom_decor/face_decor.png");
	arr_tex[2] = IMG_Load("../doom_decor/scary_decor.png");
	arr_tex[3] = IMG_Load("../doom_decor/illuminate_decor.png");
	arr_tex[4] = IMG_Load("../doom_decor/eye_decor.png");
	arr_tex[0] = SDL_ConvertSurfaceFormat(arr_tex[0],
			SDL_PIXELFORMAT_ARGB32, 0);
	arr_tex[1] = SDL_ConvertSurfaceFormat(arr_tex[1],
			SDL_PIXELFORMAT_ARGB32, 0);
	arr_tex[2] = SDL_ConvertSurfaceFormat(arr_tex[2],
			SDL_PIXELFORMAT_ARGB32, 0);
	arr_tex[3] = SDL_ConvertSurfaceFormat(arr_tex[3],
			SDL_PIXELFORMAT_ARGB32, 0);
	arr_tex[4] = SDL_ConvertSurfaceFormat(arr_tex[4],
			SDL_PIXELFORMAT_ARGB32, 0);
}

void	decor_init(t_sdl_main *sdl)
{
	SDL_Surface		**arr_tex;

	arr_tex = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * 4);
	get_decor_textures(arr_tex);
	sdl->textures->decor_tex = arr_tex;
}

void	get_mandatory_textures(SDL_Surface **arr_tex)
{
	arr_tex[0] = IMG_Load("../doom_textures/bloody_game.jpg");
	arr_tex[1] = IMG_Load("../doom_textures/carpet_game.jpg");
	arr_tex[2] = IMG_Load("../doom_textures/forest_game.jpg");
	arr_tex[3] = IMG_Load("../doom_textures/mess_game.jpg");
	arr_tex[4] = IMG_Load("../doom_textures/scull_game.jpg");
	arr_tex[5] = IMG_Load("../doom_textures/wall_game.jpg");
	arr_tex[6] = IMG_Load("../doom_textures/ground.jpg");
	arr_tex[0] = SDL_ConvertSurfaceFormat(arr_tex[0],
			SDL_PIXELFORMAT_ARGB32, 0);
	arr_tex[1] = SDL_ConvertSurfaceFormat(arr_tex[1],
			SDL_PIXELFORMAT_ARGB32, 0);
	arr_tex[2] = SDL_ConvertSurfaceFormat(arr_tex[2],
			SDL_PIXELFORMAT_ARGB32, 0);
	arr_tex[3] = SDL_ConvertSurfaceFormat(arr_tex[3],
			SDL_PIXELFORMAT_ARGB32, 0);
	arr_tex[4] = SDL_ConvertSurfaceFormat(arr_tex[4],
			SDL_PIXELFORMAT_ARGB32, 0);
	arr_tex[5] = SDL_ConvertSurfaceFormat(arr_tex[5],
			SDL_PIXELFORMAT_ARGB32, 0);
	arr_tex[6] = SDL_ConvertSurfaceFormat(arr_tex[6],
			SDL_PIXELFORMAT_ARGB32, 0);
}

void	textures_init(t_sdl_main *sdl)
{
	SDL_Surface		**arr_tex;

	arr_tex = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * 6);
	get_mandatory_textures(arr_tex);
	sdl->textures->arr_tex = arr_tex;
	decor_init(sdl);
	decor_texture(sdl, 5, 4, (t_xy_uint){.x = 50, .y = 50});
}
