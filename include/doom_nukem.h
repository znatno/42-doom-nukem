/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom-nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 19:21:08 by ggavryly          #+#    #+#             */
/*   Updated: 2019/07/31 19:21:09 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# include <unistd.h>
# include <errno.h>
# include <math.h>
# include <pthread.h>
# include <stdio.h>
# include <stdbool.h>
# include "libft.h"
# include "SDL.h"
# include "SDL_mixer.h"
# include "SDL_image.h"

# define WIN_HEIGHT		1000
# define WIN_WIDTH		1000
# define ERROR(x)		printf("Ah SHIT, here we go again %s", x)
# define TEXTURE_SCALE	1.0

typedef struct			s_sdl_main
{
	SDL_DisplayMode		display_mode;
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Surface			surface;
	SDL_Texture			*texture;
	SDL_Rect			src_rect;
	SDL_Rect			dst_rect;
	SDL_Event           event;
	SDL_bool            done;
}						t_sdl_main;



void					init_sdl(t_sdl_main *sdl);
SDL_Texture				*load_texture(char *path, t_sdl_main *sdl);

#endif
