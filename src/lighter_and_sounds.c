/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music_and_sounds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprokysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:12:54 by tprokysh          #+#    #+#             */
/*   Updated: 2019/09/06 16:12:55 by tprokysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int			load_pistol_sprite(t_game *g, int sprite_count)
{
	SDL_Surface		*cur_sprite;
	unsigned int	*pixels;
	int				x;
	int				y;

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		ft_putendl(IMG_GetError());
	cur_sprite = load_pistol_part(sprite_count);
	y = -1;
	pixels = (unsigned int *)cur_sprite->pixels;
	while (++y < 128)
	{
		x = -1;
		while (++x < 128)
			g->wpn.pistol_sprite[sprite_count][y][x] =
					pixels[(y * cur_sprite->w) + x];
	}
	SDL_FreeSurface(cur_sprite);
	return (1);
}

void		load_lighter(t_game *g)
{
	int y;
	int sprite;
	int max_sprites;

	max_sprites = 2;
	g->wpn.lighter_sprite = (int***)malloc(sizeof(int **) * max_sprites);
	sprite = 0;
	while (sprite < max_sprites)
	{
		g->wpn.lighter_sprite[sprite] = (int**)malloc(sizeof(int *) * 128);
		y = 0;
		while (y < 128)
		{
			g->wpn.lighter_sprite[sprite][y] = (int*)malloc(sizeof(int) * 128);
			y++;
		}
		load_lighter_sprite(g, sprite);
		sprite++;
	}
}

void		load_pistol(t_game *g)
{
	int y;
	int sprite;
	int max_sprites;

	max_sprites = 6;
	g->wpn.pistol_sprite = (int***)malloc(sizeof(int **) * max_sprites);
	sprite = 0;
	while (sprite < max_sprites)
	{
		g->wpn.pistol_sprite[sprite] = (int**)malloc(sizeof(int *) * 128);
		y = 0;
		while (y < 128)
		{
			g->wpn.pistol_sprite[sprite][y] = (int*)malloc(sizeof(int) * 128);
			y++;
		}
		load_pistol_sprite(g, sprite);
		sprite++;
	}
}

void		load_weapons(t_game *g)
{
	g->wpn.sprite_counter = 1;
	g->wpn.type = 1;
	load_pistol(g);
	load_lighter(g);
}

t_sounds	*init_music_n_sounds(void)
{
	t_sounds *sounds;

	sounds = (t_sounds *)malloc(sizeof(t_sounds));
	SDL_Init(SDL_INIT_AUDIO);
	Mix_OpenAudio(42000, AUDIO_S16SYS, 2, 4096);
	sounds->bg_music = Mix_LoadMUS("sounds/bestmusic.wav");
	sounds->run_sound = Mix_LoadWAV("sounds/run.wav");
	sounds->jumpbreath = Mix_LoadWAV("sounds/jumpbreath.wav");
	sounds->landing = Mix_LoadWAV("sounds/land2.wav");
	sounds->fast_run = Mix_LoadWAV("sounds/fast_run.wav");
	sounds->low_run = Mix_LoadWAV("sounds/run.wav");
	sounds->lighter = Mix_LoadWAV("sounds/lighter.wav");
	sounds->lighter_close = Mix_LoadWAV("sounds/lighter_close.wav");
	sounds->gun_fire = Mix_LoadWAV("sounds/gun_fire.wav");
	Mix_VolumeMusic(30);
	Mix_Volume(RUN, 20);
	Mix_Volume(SEAT_RUN, 10);
	Mix_Volume(FAST_RUN, 20);
	return (sounds);
}
