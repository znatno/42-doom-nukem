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
# include <stdio.h>
# include <pthread.h>
# include <math.h>
# include "libft.h"
# include <stdio.h>
# include "/Users/ggavryly/.brew/Cellar/sdl2/2.0.9_1/include/SDL2/SDL.h"
# define WIN_HEIGHT		1000
# define WIN_WIDTH		1000
# define ERROR(x)		printf("Ah SHIT, here we go again %s", x)

typedef struct			s_sdl_image
{
	SDL_Rect			text_rect;
	u_int32_t			p_offset_x;
	u_int32_t			p_offset_y;
	u_int32_t			p_width_x;
	u_int32_t			p_height_y;
	u_int32_t			b_offset_x;
	u_int32_t			b_offset_y;
	u_int32_t			b_width_x;
	u_int32_t			b_height_y;
}						t_sdl_image;

typedef struct			s_sdl_main
{
	SDL_DisplayMode		display_mode;
	SDL_Window			*win;
	SDL_Renderer		*renderer;
	t_sdl_image			*sdl_img;
}						t_sdl_main;


void					init_sdl(t_sdl_main *sdl);

#endif
