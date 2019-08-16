/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibohun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 18:32:05 by ibohun            #+#    #+#             */
/*   Updated: 2019/08/16 19:30:46 by ibohun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

SDL_Color black = { .r = 0, .g = 0, .b = 0 };
SDL_Color white = { .r = 255, .g = 255, .b = 255 };

SDL_Surface *renderFontToSurface(TTF_Font *font, char *text)
{
	// Create a text texture with a shadow effect
	SDL_Surface *textb = TTF_RenderText_Solid(font, text, black);
	SDL_Surface *textw = TTF_RenderText_Solid(font, text, white);

	/* Create a 32-bit surface with the bytes of each pixel in R,G,B,A order,
	   as expected by OpenGL for textures */
	SDL_Surface *surface;
	Uint32 rmask, gmask, bmask, amask;

	/* SDL interprets each pixel as a 32-bit number, so our masks must depend
	   on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
#endif

	// with amask = 0, I see the image, with amask = 0xff000000, I see nothing
	surface = SDL_CreateRGBSurface(0, textw->w + 8, textw->h + 8, 32,
								   rmask, gmask, bmask, amask);

	SDL_Rect text_rect;
	text_rect.x = 2;
	text_rect.y = 1;
	text_rect.w = textw->w;
	text_rect.h = textw->h;

	SDL_UpperBlit(textw, NULL, surface, &text_rect);
	text_rect.x = 0;
	text_rect.y = 0;
	SDL_UpperBlit(textb, NULL, surface, &text_rect);

	//SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

	// This important to free the surface to avoid leaks
	SDL_FreeSurface(textw);
	SDL_FreeSurface(textb);
	//SDL_FreeSurface(surface);
	//return (texture);
	return (surface);
}

TTF_Font *getFont(char *filename, int size)
{
	TTF_Font *font;

	font = TTF_OpenFont(filename, size);
	if (font == NULL) //todo remake
	{
		fprintf(stderr, "Unable to load ttf file: %s\n", SDL_GetError());
		exit(1);
	}
	return (font);
}