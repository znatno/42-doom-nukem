/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 14:49:16 by ggavryly          #+#    #+#             */
/*   Updated: 2019/08/01 14:49:17 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"


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
	sdl->textures->arr_tex = arr_tex;
}
