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
	SDL_Texture	*texture;

	texture = IMG_LoadTexture(sdl->renderer, path);
	return (texture);
}

