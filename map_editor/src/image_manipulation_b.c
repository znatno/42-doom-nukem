/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_manipulation_b.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 21:41:27 by ggavryly          #+#    #+#             */
/*   Updated: 2019/08/30 21:41:28 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke_nukem_editor.h"

uint32_t	get_pixel(SDL_Surface *sur, uint32_t x, uint32_t y, uint32_t color)
{
	uint32_t		*pixel;

	pixel = sur->pixels + y * sur->pitch + x * sur->format->BytesPerPixel;
	if (*pixel == 0)
		return (0);
	else
		return (color);
}

uint32_t	get_pixel_wall(SDL_Surface *sur, uint32_t x, uint32_t y)
{
	uint32_t		*pixel;

	pixel = sur->pixels + y * sur->pitch + x * sur->format->BytesPerPixel;
	return (*pixel);
}

void		draw_text_black(uint32_t c_x, uint32_t c_y, char *text, t_env *env)
{
	t_font font;

	open_font(&font.font, &font.color, &font.font_surface, text);
	font.it_y = 0;
	font.size_h = font.font_surface->h;
	font.size_w = font.font_surface->w;
	while (font.it_y < font.size_h)
	{
		font.it_x = 0;
		while (font.it_x < font.size_w)
		{
			env->buffer[(c_y + font.it_y) * W_WIDTH + (c_x + font.it_x)] =
					get_pixel(font.font_surface, font.it_x, font.it_y, 0x0);
			font.it_x++;
		}
		font.it_y++;
	}
	SDL_FreeSurface(font.font_surface);
	TTF_CloseFont(font.font);
}

void		open_font(TTF_Font **f, SDL_Color *color, SDL_Surface **fs, char *t)
{
	SDL_Surface *f2;

	*f = TTF_OpenFont("fonts/FiraSans-Regular.ttf", 32);
	(*color).r = 255;
	(*color).g = 255;
	(*color).b = 255;
	(*color).a = 0;
	*fs = TTF_RenderText_Solid(*f, t, *color);
	f2 = SDL_ConvertSurfaceFormat(*fs, SDL_PIXELFORMAT_BGRA32, 0);
	SDL_FreeSurface(*fs);
	*fs = f2;
}
