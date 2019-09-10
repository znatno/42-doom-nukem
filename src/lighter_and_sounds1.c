/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music_and_sounds1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprokysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:13:58 by tprokysh          #+#    #+#             */
/*   Updated: 2019/09/06 16:13:59 by tprokysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void			draw_pistol(t_game *g)
{
	if (g->wpn.sprite_counter == 1)
		draw_cur_pistol_sprite(g, W - 400, H - 250, 0);
	else if (g->wpn.sprite_counter > 1)
	{
		draw_cur_pistol_sprite(g, W - 400, H - 250, g->wpn.sprite_counter - 1);
		g->wpn.sprite_counter += 1;
	}
	if (g->wpn.sprite_counter >= 6)
		g->wpn.sprite_counter = 1;
}

void			draw_weapons(t_game *g)
{
	if (g->wpn.type == 1)
		draw_pistol(g);
	else if (g->wpn.type == 2)
		draw_lighter(g);
}

SDL_Surface		*load_lighter_part(int sprite)
{
	SDL_Surface *cur_sprite;
	SDL_Surface	*tmp;

	if (sprite == 0)
		cur_sprite = IMG_Load("sprites/3.png");
	if (sprite == 1)
		cur_sprite = IMG_Load("sprites/1.png");
	tmp = SDL_ConvertSurfaceFormat(cur_sprite,
										SDL_PIXELFORMAT_ARGB32, 0);
	SDL_FreeSurface(cur_sprite);
	cur_sprite = tmp;
	return (cur_sprite);
}

SDL_Surface		*load_pistol_part(int sprite)
{
	SDL_Surface *cur_sprite;
	SDL_Surface *tmp;

	if (sprite == 0)
		cur_sprite = IMG_Load("sprites/pistol1.png");
	else if (sprite == 1)
		cur_sprite = IMG_Load("sprites/pistol2.png");
	else if (sprite == 2)
		cur_sprite = IMG_Load("sprites/pistol3.png");
	else if (sprite == 3)
		cur_sprite = IMG_Load("sprites/pistol4.png");
	else if (sprite == 4)
		cur_sprite = IMG_Load("sprites/pistol5.png");
	else if (sprite == 5)
		cur_sprite = IMG_Load("sprites/pistol6.png");
	tmp = SDL_ConvertSurfaceFormat(cur_sprite,
										SDL_PIXELFORMAT_ARGB32, 0);
	SDL_FreeSurface(cur_sprite);
	cur_sprite = tmp;
	return (cur_sprite);
}

int				load_lighter_sprite(t_game *g, int sprite_count)
{
	SDL_Surface		*cur_sprite;
	unsigned int	*pixels;
	int				x;
	int				y;

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		ft_putendl(IMG_GetError());
	cur_sprite = load_lighter_part(sprite_count);
	y = -1;
	pixels = (unsigned int *)cur_sprite->pixels;
	while (++y < 128)
	{
		x = -1;
		while (++x < 128)
			g->wpn.lighter_sprite[sprite_count][y][x] =
					pixels[(y * cur_sprite->w) + x];
	}
	SDL_FreeSurface(cur_sprite);
	return (1);
}
