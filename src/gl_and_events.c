/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_and_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprokysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:18:02 by tprokysh          #+#    #+#             */
/*   Updated: 2019/09/06 16:18:03 by tprokysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		events2(SDL_Event ev, t_game *g,
					t_sounds *sounds)
{
	if (ev.key.keysym.sym == ' ')
	{
		Mix_HaltChannel(RUN);
		Mix_HaltChannel(FAST_RUN);
		if (!Mix_Playing(JUMP) && g->plr.ground && !g->plr.ducking)
			Mix_PlayChannel(JUMP, sounds->jumpbreath, 0);
	}
	if (ev.key.keysym.sym == 'f' && !g->plr.ducking)
		g->plr.fly = !g->plr.fly ? 1 : 0;
	if (ev.key.keysym.sym == ' ' && g->plr.ground
		&& g->plr.where.z == g->sectors[g->plr.sector].floor + EYE_H)
	{
		g->plr.vlct.z += 0.5;
		g->plr.falling = 1;
	}
	if (ev.key.keysym.sym == 't')
		g->error = g->error == 100 ? 0 : 100;
	if (ev.key.keysym.sym == 'p')
		g->msgs[1] = create_msg("Between two girls & one cup",
								FONT_M_SM, (t_xy_int){64, 96}, 5);
	if (ev.key.keysym.sym == SDLK_LCTRL && !g->plr.fly)
		g->plr.ducking = !g->plr.ducking ? 1 : 0;
}

void		game_loop3(t_game *g, t_player *plr, t_sounds *sounds)
{
	if (g->plr.pushing && !g->plr.ducking && g->plr.ground && !g->plr.run &&
		!Mix_Playing(RUN))
		Mix_PlayChannel(RUN, sounds->run_sound, 0);
	if (g->plr.ducking && plr->pushing && !Mix_Playing(SEAT_RUN))
		Mix_PlayChannel(SEAT_RUN, sounds->low_run, 0);
	if (plr->speed == 0.28f && !Mix_Playing(FAST_RUN) && plr->pushing &&
		!plr->jump_check)
		Mix_PlayChannel(FAST_RUN, sounds->fast_run, 0);
	if (!plr->pushing || plr->speed != 0.28f)
		Mix_HaltChannel(FAST_RUN);
	if (plr->pushing)
		plr->moving = 1;
	if (g->plr.pushing)
		g->plr.moving = 1;
}

void		game_loop2(t_game *g)
{
	if (g->plr.key.s)
		g->plr.mv = (t_move_vec){.x = g->plr.mv.x - g->plr.anglecos *
													g->plr.speed,
				.y = g->plr.mv.y - g->plr.anglesin * g->plr.speed};
	if (g->plr.key.a)
		g->plr.mv = (t_move_vec){.x = g->plr.mv.x + g->plr.anglesin *
													g->plr.speed,
				.y = g->plr.mv.y - g->plr.anglecos * g->plr.speed};
	if (g->plr.key.d)
		g->plr.mv = (t_move_vec){.x = g->plr.mv.x - g->plr.anglesin *
													g->plr.speed,
				.y = g->plr.mv.y + g->plr.anglecos * g->plr.speed};
	g->plr.pushing = g->plr.key.w || g->plr.key.s || g->plr.key.a ||
					g->plr.key.d;
	g->plr.aclrt = g->plr.pushing ? 0.4 : 0.2;
	g->plr.vlct.x = g->plr.vlct.x * (1 - g->plr.aclrt) + g->plr.mv.x *
														g->plr.aclrt;
	g->plr.vlct.y = g->plr.vlct.y * (1 - g->plr.aclrt) + g->plr.mv.y *
														g->plr.aclrt;
}

void		game_loop1(t_game *g, t_sounds *sounds)
{
	if (g->plr.ducking || g->plr.eyeheight == DUCK_H)
		g->plr.speed /= 1.5f;
	if (g->plr.eyeheight != EYE_H && !g->plr.ducking &&
	g->sectors[g->plr.sector].ceil > g->sectors[g->plr.sector].floor + EYE_H)
		g->plr.eyeheight += 0.5f;
	else if (g->plr.eyeheight != DUCK_H && g->sectors[g->plr.sector].ceil
			<= g->sectors[g->plr.sector].floor + EYE_H)
		g->plr.eyeheight -= 0.5f;
	g->plr.ground = !g->plr.falling;
	if (g->plr.falling)
		do_fall(&g->plr, &g->sectors, sounds);
	if (g->plr.moving)
		check_move(&g->plr, &g->sectors, -1);
	g->plr.ms.x = 0;
	g->plr.ms.y = 0;
	SDL_GetRelativeMouseState(&g->plr.ms.x, &g->plr.ms.y);
	g->plr.angle += g->plr.ms.x * 0.03f;
	g->plr.ms_yaw = CLAMP(g->plr.ms_yaw - g->plr.ms.y * 0.05f, -5, 5);
	g->plr.yaw = g->plr.ms_yaw - g->plr.vlct.z * 0.5f;
	g->plr.mv = (t_move_vec){.x = 0.f, .y = 0.f};
	motion(&g->plr, &g->sectors, 0, 0);
	if (g->plr.key.w)
		g->plr.mv = (t_move_vec){.x = g->plr.mv.x + g->plr.anglecos *
			g->plr.speed, .y = g->plr.mv.y + g->plr.anglesin * g->plr.speed};
}

void		game_loop(t_game *g, t_player *plr, t_sounds *sounds)
{
	t_draw_screen_calc ds;

	g->msgs[0] = create_msg("Episode 1", FONT_M_BG, (t_xy_int){40, 64}, 50);
	g->msgs[1] = create_msg("HP: 100/100", FONT_M_MD, (t_xy_int){32, 680}, -1);
	g->msgs[2] = create_msg("Notes: 0/10", FONT_M_MD, (t_xy_int){32, 720}, -1);
	while (true)
	{
		events(g, sounds);
		game_loop1(g, sounds);
		game_loop2(g);
		game_loop3(g, plr, sounds);
		main_draw(g, ds);
		draw_weapons(g);
		SDL_UpdateTexture(g->sdl.texture, NULL, g->sdl.buffer,
						W * (sizeof(int)));
		SDL_RenderCopy(g->sdl.renderer, g->sdl.texture, NULL, NULL);
		get_messages(g);
		SDL_RenderPresent(g->sdl.renderer);
	}
}
