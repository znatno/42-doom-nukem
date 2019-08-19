/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibohun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 18:32:05 by ibohun            #+#    #+#             */
/*   Updated: 2019/08/19 15:35:53 by ibohun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

SDL_Color black = {0, 0, 0};
//SDL_Color white = {255, 255, 255};

TTF_Font *get_font(char *filename, int size)
{
	TTF_Font *font;

	if (!(font = TTF_OpenFont(filename, size))) //todo remake
	{
		fprintf(stderr, "Unable to load ttf file: %s\n", SDL_GetError());
		exit(1);
	}
	return (font);
}

t_font	init_font(char *fontname, int size, SDL_Color color)
{
	t_font	t;

	t.ttf = get_font(fontname, size);
	t.name = fontname;
	t.size = size;
	t.color = color;
	return (t);
}

void		show_msg(t_sdl_main *sdl, char *text, t_xy_i pos)
{
	static SDL_Color white = {255, 255, 255, 255};
	SDL_Surface *surface_msg;
	SDL_Texture *msg;
	SDL_Rect msg_rect;

	TTF_Font *font;

	font = get_font("../Lato-Regular.ttf", 32);
	surface_msg = TTF_RenderText_Solid(font, text, white);
	msg = SDL_CreateTextureFromSurface(sdl->renderer, surface_msg);
	msg_rect.x = pos.x;
	msg_rect.y = pos.y;
	TTF_SizeText(font, text, &msg_rect.w, &msg_rect.h);
	//SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
	SDL_FreeSurface(surface_msg);
	SDL_DestroyTexture(msg);
}
