/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibohun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:03:03 by ibohun            #+#    #+#             */
/*   Updated: 2019/08/23 20:06:51 by ibohun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int			main(void)
{
	t_game		g;
	t_sounds	*sounds;

	g.sectors = NULL;
	g.plr = (t_player){.falling = 1, .eyeheight = EYE_H, .sdl = &g.sdl};
	init_msgs(&g);
	init_sdl(&g);
	load_data(&g.plr, &g.sectors);
	load_fonts(&g);
	load_weapons(&g);
	textures_init(&g.sdl);
	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	sounds = init_music_n_sounds();
	Mix_PlayMusic(sounds->bg_music, -1);
	game_loop(&g, &g.plr, sounds);
	exit_doom(&g);
}
