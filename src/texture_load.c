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

SDL_Texture		*load_texture(char *path, t_sdl_main *sdl)
{
	SDL_Surface	*load_me;
	SDL_Texture	*texture;

	load_me = NULL;
	texture = NULL;
	load_me = IMG_Load(path);
	if (!load_me)
		ERROR("load texture");
	else
	{
		texture = SDL_CreateTextureFromSurface(sdl->renderer, load_me);
		SDL_FreeSurface(load_me);
	}
	return (texture);
}

