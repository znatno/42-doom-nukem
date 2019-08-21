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
	cords[DRAW_MODE].y = 10;

	printf("draw_mode_x - %d| draw_mode_y - %d\n", cords[DRAW_MODE].x, cords[DRAW_MODE].y);

	cords[SELECT_MODE].x = 1425;
	cords[SELECT_MODE].y = 70;

	cords[WALL_MODE].x = 1425;
	cords[WALL_MODE].y = 130;

	cords[REFRESH].x = 1425;
	cords[REFRESH].y = 190;

	cords[CEIL].x = 1425;
	cords[CEIL].y = 300;

	cords[FLOOR].x = 1425;
	cords[FLOOR].y = 360;

	cords[LEFT].x = 1425;
	cords[LEFT].y = 450;

	cords[RIGHT].x = 1530;
	cords[RIGHT].y = 450;

	cords[PLAYER].x = 1420;
	cords[PLAYER].y = 520;

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
	texture_cords_end(env);
	env->textures->pre = -1;
	env->textures->selected = -1;
}

void	texture_cords_end(t_env *env)
{
	t_xy	*cords_end;
	int 	i;

	i = 0;
	cords_end = (t_xy *)malloc(sizeof(t_xy) * 10);
	while (i < 10)
	{
		cords_end[i].x = env->textures->cords[i].x + env->textures->arr_tex[i]->w;
		cords_end[i].y = env->textures->cords[i].y + env->textures->arr_tex[i]->h;
		printf("draw_mode_end_x - %d| draw_mode_end_y - %d\n", cords_end[i].x, cords_end[i].y);
		printf("draw_mode_x - %d| draw_mode_y - %d\n", env->textures->cords[i].x, env->textures->cords[i].y);
		i++;
	}
	env->textures->cords_end = cords_end;
}
