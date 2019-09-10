/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_load_a.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 16:59:00 by ggavryly          #+#    #+#             */
/*   Updated: 2019/08/31 16:59:01 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke_nukem_editor.h"

void	image_load(SDL_Surface **arr_tex)
{
	arr_tex[0] = IMG_Load("textures/ceil.png");
	arr_tex[1] = IMG_Load("textures/draw_mode.png");
	arr_tex[2] = IMG_Load("textures/floor.png");
	arr_tex[3] = IMG_Load("textures/left.png");
	arr_tex[4] = IMG_Load("textures/objects.png");
	arr_tex[5] = IMG_Load("textures/player.png");
	arr_tex[6] = IMG_Load("textures/refresh.png");
	arr_tex[7] = IMG_Load("textures/right.png");
	arr_tex[8] = IMG_Load("textures/select_mode.png");
	arr_tex[9] = IMG_Load("textures/wall_mode.png");
	arr_tex[10] = IMG_Load("textures/guns_editor.png");
	arr_tex[11] = IMG_Load("textures/kits_editor.png");
	arr_tex[12] = IMG_Load("textures/armor_editor.png");
	arr_tex[13] = IMG_Load("textures/death_editor.png");
	arr_tex[14] = IMG_Load("textures/fly_editor.png");
	arr_tex[15] = IMG_Load("textures/network_editor.png");
	arr_tex[20] = IMG_Load("textures/wood_editor.png");
	arr_tex[21] = IMG_Load("textures/skulls_editor.png");
	arr_tex[22] = IMG_Load("textures/bloody_editor.png");
	arr_tex[23] = IMG_Load("textures/mess_editor.png");
	arr_tex[24] = IMG_Load("textures/forest_editor.png");
	arr_tex[25] = IMG_Load("textures/wall_editor.png");
	arr_tex[26] = IMG_Load("textures/carpet_editor.png");
}

void	convert_surface(SDL_Surface **arr_tex, int num)
{
	SDL_Surface		*tmp;

	tmp = SDL_ConvertSurfaceFormat(arr_tex[num], SDL_PIXELFORMAT_BGRA32, 0);
	SDL_FreeSurface(arr_tex[num]);
	arr_tex[num] = tmp;
}

void	convert_surfaces(SDL_Surface ***arr_tex)
{
	convert_surface(*arr_tex, 0);
	convert_surface(*arr_tex, 1);
	convert_surface(*arr_tex, 2);
	convert_surface(*arr_tex, 3);
	convert_surface(*arr_tex, 4);
	convert_surface(*arr_tex, 5);
	convert_surface(*arr_tex, 6);
	convert_surface(*arr_tex, 7);
	convert_surface(*arr_tex, 8);
	convert_surface(*arr_tex, 9);
	convert_surface(*arr_tex, 10);
	convert_surface(*arr_tex, 11);
	convert_surface(*arr_tex, 12);
	convert_surface(*arr_tex, 13);
	convert_surface(*arr_tex, 14);
	convert_surface(*arr_tex, 15);
	convert_surface(*arr_tex, 20);
	convert_surface(*arr_tex, 21);
	convert_surface(*arr_tex, 22);
	convert_surface(*arr_tex, 23);
	convert_surface(*arr_tex, 24);
	convert_surface(*arr_tex, 25);
	convert_surface(*arr_tex, 26);
}

void	texture_load(t_env *env)
{
	SDL_Surface		**arr_tex;

	arr_tex = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * 27);
	image_load(arr_tex);
	convert_surfaces(&arr_tex);
	env->textures->arr_tex = arr_tex;
	texture_cords(env);
	texture_cords_end(env);
	env->textures->selected = -1;
}

void	texture_cords_end(t_env *e)
{
	t_xy	*cords_end;
	int		i;

	i = 0;
	cords_end = (t_xy *)malloc(sizeof(t_xy) * 17);
	while (i < 16)
	{
		cords_end[i].x = e->textures->cords[i].x + e->textures->arr_tex[i]->w;
		cords_end[i].y = e->textures->cords[i].y + e->textures->arr_tex[i]->h;
		i++;
	}
	e->textures->cords_end = cords_end;
}
