/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibohun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 18:32:05 by ibohun            #+#    #+#             */
/*   Updated: 2019/08/19 19:44:51 by ibohun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_font		get_font(char *name, int size, SDL_Color color)
{
	t_font	t;

	t.name = name;
	t.size = size;
	t.color = color;
	if (!(t.ttf = TTF_OpenFont(name, size)))
		t.ttf = NULL;
	return (t);
}

void		load_fonts(t_game *g)
{
	static SDL_Color white = {255, 255, 255};

	g->fonts[FONT_M_SM] = get_font("fonts/main.ttf", 14, white);
	g->fonts[FONT_M_MD] = get_font("fonts/main.ttf", 21, white);
	g->fonts[FONT_M_BG] = get_font("fonts/main.ttf", 32, white);
	g->fonts[FONT_S_SM] = get_font("fonts/script.ttf", 14, white);
	g->fonts[FONT_S_MD] = get_font("fonts/script.ttf", 21, white);
	g->fonts[FONT_S_BG] = get_font("fonts/script.ttf", 32, white);
}

void		clear_font(t_font *t)
{
	t->name = 0;
	t->size = 0;
	t->color = (SDL_Color){0, 0, 0, 0};
	TTF_CloseFont(t->ttf);
}
