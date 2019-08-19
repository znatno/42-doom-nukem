/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibohun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:03:03 by ibohun            #+#    #+#             */
/*   Updated: 2019/08/19 19:23:26 by ibohun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"



void		events(t_game *g)
{
	const uint8_t	*kstate;	//	array of keyboard keys states
	SDL_Event		ev;

	kstate = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&ev))
	{
		if (kstate[SDL_SCANCODE_ESCAPE] || ev.type == SDL_QUIT)
			exit_doom(g);

		g->plr.key.w = kstate[SDL_SCANCODE_W];
		g->plr.key.a = kstate[SDL_SCANCODE_A];
		g->plr.key.s = kstate[SDL_SCANCODE_S];
		g->plr.key.d = kstate[SDL_SCANCODE_D];
		g->plr.draw_look = kstate[SDL_SCANCODE_L];
		if (ev.type == SDL_KEYDOWN)
		{
			if (ev.key.keysym.sym == 'f' && !g->plr.ducking)
				g->plr.fly = !g->plr.fly ? 1 : 0;
			if (ev.key.keysym.sym == ' ' && g->plr.ground
				&& g->plr.where.z == g->sectors[g->plr.sector].floor + EYE_H)
			{
				g->plr.vlct.z += 0.5;
				g->plr.falling = 1;
			}

			if (ev.key.keysym.sym == 'p') //TODO: вивід корисної інфи для дебаґу
			{
				g->msgs[1] = create_msg("Between two girls & one cup",
						FONT_M_SM, (t_xy_i){64, 96}, 5);

				//create_msg(text, font, seconds);

				/*
				printf("\n\t---------------------------\n");
				printf("\t\t\t[print msg]\n");
				// поточний сектор
				printf("\tg->plr.speed: %f\n\n", g->plr.speed);
				printf("\tcurr sec: %d\n", g->plr.sector);
				printf("\tceil: %f\n", g->sectors[g->plr.sector].ceil);
				printf("\tfloor: %f\n\n", g->sectors[g->plr.sector].floor);
				// поточна позиція
				printf("\tx: %f\t\ty: %f\t\tz: %f\n",
						g->plr.where.x, g->plr.where.y, g->plr.where.z);
				// кути погляду
				printf("\tangle: %f\t\tyaw: %f\n",
					   g->plr.angle, g->plr.yaw);
				printf("\n\t---------------------------\n\n");
				*/
			}

			if (ev.key.keysym.sym == SDLK_LCTRL && !g->plr.fly)
				g->plr.ducking = !g->plr.ducking ? 1 : 0;
		}
		if (g->sectors[g->plr.sector].ceil < g->plr.where.z + HEAD_MARGIN)
			g->plr.ducking = true;
		if (g->plr.ducking)
		{
			g->plr.falling = 1;
			g->plr.eyeheight = DUCK_H;
		}
		g->plr.run = kstate[SDL_SCANCODE_LSHIFT];
		g->plr.speed = g->plr.run && g->plr.eyeheight != DUCK_H ? 0.28f : 0.20f;
		SDL_PumpEvents(); // обработчик событий
	}
}



void		game_loop(t_game *g)
{
	g->msgs[0] = create_msg("Episode 1", FONT_M_MD, (t_xy_i){64, 64}, 5);
	while (true)
	{
		/* Очищує буфер чорним кольором */
		//SDL_FillRect(sdl->w_surface, NULL,
		//		SDL_MapRGB(sdl->w_surface->format, 0, 0, 0));

		/* Key Events */
		events(g);

		/* Камера при присяді і її підняття */
		if (g->plr.ducking || g->plr.eyeheight == DUCK_H)
			g->plr.speed /= 1.5f;
		if (g->plr.eyeheight != EYE_H && !g->plr.ducking &&
				g->sectors[g->plr.sector].ceil > g->sectors[g->plr.sector].floor + EYE_H)
			g->plr.eyeheight += 0.5f;
		else if (g->plr.eyeheight != DUCK_H && g->sectors[g->plr.sector].ceil
					<= g->sectors[g->plr.sector].floor + EYE_H)
			g->plr.eyeheight -= 0.5f;

		/* Vertical collision detection */
		g->plr.ground = !g->plr.falling;
		if (g->plr.falling)
			check_fall(&g->plr, &g->sectors);

		/* Horizontal collision detection */
		if (g->plr.moving)
			check_move(&g->plr, &g->sectors);

		/* mouse aiming */
		g->plr.ms.x = 0;
		g->plr.ms.y = 0;
		SDL_GetRelativeMouseState(&g->plr.ms.x, &g->plr.ms.y);
		g->plr.angle += g->plr.ms.x * 0.03f;
		g->plr.ms_yaw = CLAMP(g->plr.ms_yaw - g->plr.ms.y * 0.05f, -5, 5);
		g->plr.yaw = g->plr.ms_yaw - g->plr.vlct.z * 0.5f;

		/* player moving */
		g->plr.mv = (t_move_vec){.x = 0.f, .y = 0.f};
		move_player(&g->plr, &g->sectors, 0, 0);
		if (g->plr.key.w)
			g->plr.mv = (t_move_vec){.x = g->plr.mv.x + g->plr.anglecos * g->plr.speed,
						  .y = g->plr.mv.y + g->plr.anglesin * g->plr.speed};
		if (g->plr.key.s)
			g->plr.mv = (t_move_vec){.x = g->plr.mv.x - g->plr.anglecos * g->plr.speed,
						  .y = g->plr.mv.y - g->plr.anglesin * g->plr.speed};
		if (g->plr.key.a)
			g->plr.mv = (t_move_vec){.x = g->plr.mv.x + g->plr.anglesin * g->plr.speed,
						  .y = g->plr.mv.y - g->plr.anglecos * g->plr.speed};
		if (g->plr.key.d)
			g->plr.mv = (t_move_vec){.x = g->plr.mv.x - g->plr.anglesin * g->plr.speed,
						  .y = g->plr.mv.y + g->plr.anglecos * g->plr.speed};
		g->plr.pushing = g->plr.key.w || g->plr.key.s || g->plr.key.a || g->plr.key.d;
		g->plr.aclrt = g->plr.pushing ? 0.4 : 0.2;
		g->plr.vlct.x = g->plr.vlct.x * (1 - g->plr.aclrt) + g->plr.mv.x * g->plr.aclrt;
		g->plr.vlct.y = g->plr.vlct.y * (1 - g->plr.aclrt) + g->plr.mv.y * g->plr.aclrt;
		if (g->plr.pushing)
			g->plr.moving = 1;

		/* Draw frame */
		draw_screen(g->sectors, g->plr);

		/* update window */
		SDL_UpdateTexture(g->sdl.texture, NULL, g->sdl.buffer, W * (sizeof(int)));
		SDL_RenderCopy(g->sdl.renderer, g->sdl.texture, NULL, NULL);
		//SDL_RenderPresent(sdl->renderer);

		//get_msgs
		//if (g->tmp)
		//init_font();
		//show_msg(&g->sdl, "Test", pos);
		get_messages(g);
		SDL_RenderPresent(g->sdl.renderer);
		SDL_Delay(15);
		//printf("clock: %lu\n", clock());
	}
}

int 		main(void)
{
	t_game	g;

	//Structs initialization
	g.sectors = NULL;
	g.plr = (t_player){ .ground = 0, .falling = 1, .moving = 0, .ducking = 0,
				   .eyeheight = EYE_H, .num_scts = 0, .ms_yaw = 0,
				   .sdl = &g.sdl, .key = { .w = 0, .s = 0, .a = 0, .d = 0 }};
	init_msgs(&g);

	//Framework initialization
	init_sdl(&g.sdl);

	//Load map
	load_data(&g.plr, &g.sectors);

	//Load fonts
	load_fonts(&g);

	//Cursor lock
	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	//Loop
	game_loop(&g);

	//Before quit
	exit_doom(&g);
}
