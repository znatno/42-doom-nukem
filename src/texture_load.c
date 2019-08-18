/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 13:20:27 by ggavryly          #+#    #+#             */
/*   Updated: 2019/08/18 13:20:28 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke_nukem_editor.h"

void	texture_cords(t_env *env)
{
	t_xy	*cords;

	cords = (t_xy *)malloc(sizeof(t_xy) * 10);
	cords[DRAW_MODE].x = 1425;
	cords[DRAW_MODE].y = 65;

	cords[SELECT_MODE].x = 1425;
	cords[SELECT_MODE].y = 130;

	cords[WALL_MODE].x = 1425;
	cords[WALL_MODE].y = 205;

	cords[REFRESH].x = 1425;
	cords[REFRESH].y = 280;

	cords[CEIL].x = 1425;
	cords[CEIL].y = 355;

	cords[FLOOR].x = 1425;
	cords[FLOOR].y = 425;

	cords[LEFT].x = 1425;
	cords[LEFT].y = 500;

	cords[RIGHT].x = 1530;
	cords[RIGHT].y = 500;

	cords[PLAYER].x = 1425;
	cords[PLAYER].y = 575;

	cords[OBJECTS].x = 1470;
	cords[OBJECTS].y = 640;

	env->textures->cords = cords;
}

void	texture_load(t_env *env)
{
	SDL_Surface		**arr_tex;

	arr_tex = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * 10);
	arr_tex[0] = IMG_Load("../textures/ceil.png");
	arr_tex[1] = IMG_Load("../textures/draw_mode.png");
	arr_tex[2] = IMG_Load("../textures/floor.png");
	arr_tex[3] = IMG_Load("../textures/left.png");
	arr_tex[4] = IMG_Load("../textures/objects.png");
	arr_tex[5] = IMG_Load("../textures/player.png");
	arr_tex[6] = IMG_Load("../textures/refresh.png");
	arr_tex[7] = IMG_Load("../textures/right.png");
	arr_tex[8] = IMG_Load("../textures/select_mode.png");
	arr_tex[9] = IMG_Load("../textures/wall_mode.png");

	arr_tex[0] = SDL_ConvertSurfaceFormat(arr_tex[0], SDL_PIXELFORMAT_BGRA32, 0);
	arr_tex[1] = SDL_ConvertSurfaceFormat(arr_tex[1], SDL_PIXELFORMAT_BGRA32, 0);
	arr_tex[2] = SDL_ConvertSurfaceFormat(arr_tex[2], SDL_PIXELFORMAT_BGRA32, 0);
	arr_tex[3] = SDL_ConvertSurfaceFormat(arr_tex[3], SDL_PIXELFORMAT_BGRA32, 0);
	arr_tex[4] = SDL_ConvertSurfaceFormat(arr_tex[4], SDL_PIXELFORMAT_BGRA32, 0);
	arr_tex[5] = SDL_ConvertSurfaceFormat(arr_tex[5], SDL_PIXELFORMAT_BGRA32, 0);
	arr_tex[6] = SDL_ConvertSurfaceFormat(arr_tex[6], SDL_PIXELFORMAT_BGRA32, 0);
	arr_tex[7] = SDL_ConvertSurfaceFormat(arr_tex[7], SDL_PIXELFORMAT_BGRA32, 0);
	arr_tex[8] = SDL_ConvertSurfaceFormat(arr_tex[8], SDL_PIXELFORMAT_BGRA32, 0);
	arr_tex[9] = SDL_ConvertSurfaceFormat(arr_tex[9], SDL_PIXELFORMAT_BGRA32, 0);
	env->textures->arr_tex = arr_tex;
	texture_cords(env);
}
