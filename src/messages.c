/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibohun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 17:10:24 by ibohun            #+#    #+#             */
/*   Updated: 2019/08/19 19:44:51 by ibohun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	show_msg(t_game *g, t_msg m, t_font font)
{
	SDL_Surface	*surface_msg;
	SDL_Texture	*msg;
	SDL_Rect	msg_rect;

	surface_msg = TTF_RenderText_Blended(font.ttf, m.text, font.color);
	msg = SDL_CreateTextureFromSurface(g->sdl.renderer, surface_msg);
	msg_rect.x = m.pos.x;
	msg_rect.y = m.pos.y;
	TTF_SizeText(font.ttf, m.text, &msg_rect.w, &msg_rect.h);
	SDL_RenderCopy(g->sdl.renderer, msg, NULL, &msg_rect);
	SDL_FreeSurface(surface_msg);
	SDL_DestroyTexture(msg);
}

t_msg	create_msg(char *text, uint8_t fontname, t_xy_int pos, int sec)
{
	t_msg	m;

	m.start_t = clock();
	m.constant = false;
	if (sec == -1)
	{
		m.seconds = 1;
		m.constant = true;
	}
	else
		m.seconds = sec * 250000;
	m.text = text;
	m.pos = pos;
	m.font_num = fontname;
	return (m);
}

void	clear_msg(t_msg *m)
{
	m->start_t = 0;
	m->seconds = 0;
	m->text = 0;
	m->pos = (t_xy_int){0, 0};
	m->font_num = 0;
}

void	get_messages(t_game *g)
{
	int		i;
	double	cur_t;

	i = -1;
	cur_t = clock();
	while (++i < MAX_MSGS)
	{
		if (cur_t > g->msgs[i].start_t + g->msgs[i].seconds
			&& g->msgs[i].seconds && !g->msgs[i].constant)
			clear_msg(&g->msgs[i]);
		else
			show_msg(g, g->msgs[i], g->fonts[g->msgs[i].font_num]);
	}
}

void	init_msgs(t_game *g)
{
	int i;

	i = -1;
	while (++i < MAX_MSGS)
	{
		g->msgs[i].start_t = 0;
		g->msgs[i].seconds = 0;
		g->msgs[i].text = 0;
		g->msgs[i].pos = (t_xy_int){0, 0};
		g->msgs[i].font_num = 0;
	}
}
