/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibohun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:03:03 by ibohun            #+#    #+#             */
/*   Updated: 2019/08/12 18:57:03 by ibohun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		events(t_sector **sectors, t_player *plr)
{
	const Uint8		*kstate;	//	array of keyboard keys states
	SDL_Event		ev;

	kstate = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&ev))
	{
		if (kstate[SDL_SCANCODE_ESCAPE] || ev.type == SDL_QUIT)
			exit_doom(sectors, plr);
		plr->key.w = kstate[SDL_SCANCODE_W];
		plr->key.a = kstate[SDL_SCANCODE_A];
		plr->key.s = kstate[SDL_SCANCODE_S];
		plr->key.d = kstate[SDL_SCANCODE_D];
		if (ev.type == SDL_KEYDOWN)
		{
			if (ev.key.keysym.sym == ' ' && plr->ground)
			{
				plr->vlct.z += 0.5;
				plr->falling = 1;
			}
			if (ev.key.keysym.sym == 'p') //TODO: вивід корисної інфи для дебаґу
				printf("p\n");
		}
		plr->ducking = kstate[SDL_SCANCODE_LCTRL];
		if (plr->ducking)
			plr->falling = 1;

		SDL_PumpEvents(); // обработчик событий
	}
}

void		game_loop(t_sdl_main *sdl, t_player *plr, t_sector *sectors)
{
	bool 			quit;

	quit = false;
	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	while(!quit)
	{
		events(&sectors, plr);
		if ((g_x++ % 10) == 7)
			printf("x: %f\t\ty: %f\t\tz: %f\n",
			   plr->where.x, plr->where.y, plr->where.z);
		plr->eyeheight = plr->ducking ? DuckHeight : EyeHeight; /* Vertical collision detection */
		plr->ground = !plr->falling;
		if (plr->falling) //TODO: make ducking unreversable if стеля згори
			do_fall(plr, &sectors);
		if (plr->moving) /* Horizontal collision detection */
			do_move(plr, &sectors);
		plr->ms.x = 0; /* mouse aiming */
		plr->ms.y = 0;
		SDL_GetRelativeMouseState(&plr->ms.x, &plr->ms.y);
		plr->angle += plr->ms.x * 0.03f;
		plr->ms.yaw = clamp(plr->ms.yaw - plr->ms.y * 0.05f, -5, 5);
		plr->yaw = plr->ms.yaw - plr->vlct.z * 0.5f;
		plr->mv = (t_move_vec){.x = 0.f, .y = 0.f};
		move_player(plr, &sectors, 0, 0);
		plr->speed = 0.2f;
		if (plr->ducking)
			plr->speed /= 2;
		if (plr->key.w)
			plr->mv = (t_move_vec){.x = plr->mv.x + plr->anglecos * plr->speed,
					.y = plr->mv.y + plr->anglesin * plr->speed};
		if (plr->key.s)
			plr->mv = (t_move_vec){.x = plr->mv.x - plr->anglecos * plr->speed,
					.y = plr->mv.y - plr->anglesin * plr->speed};
		if (plr->key.a)
			plr->mv = (t_move_vec){.x = plr->mv.x + plr->anglesin * plr->speed,
					.y = plr->mv.y - plr->anglecos * plr->speed};
		if (plr->key.d)
			plr->mv = (t_move_vec){.x = plr->mv.x - plr->anglesin * plr->speed,
					.y = plr->mv.y + plr->anglecos * plr->speed};
		plr->pushing = plr->key.w || plr->key.s || plr->key.a || plr->key.d;
		plr->aclrt = plr->pushing ? 0.4 : 0.2;
		plr->vlct.x = plr->vlct.x * (1 - plr->aclrt) + plr->mv.x * plr->aclrt;
		plr->vlct.y = plr->vlct.y * (1 - plr->aclrt) + plr->mv.y * plr->aclrt;
		if (plr->pushing)
			plr->moving = 1;
		//else
		//	plr->moving = 0; // для рівномірного руху
		draw_screen(sectors, *plr);
		SDL_UpdateTexture(sdl->texture, NULL, sdl->buffer,W *(sizeof(int)));
		SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
		SDL_RenderPresent(sdl->renderer);
		SDL_Delay(15);
	}
}

int 		main(void)
{
	t_player	plr;
	t_sdl_main	sdl;
	t_sector	*sectors;
	int 		*buffer;
	//int		request;

	sectors = NULL;
	buffer = (int *)malloc(sizeof(int) * W * H);
	plr = (t_player){ .ground = 0, .falling = 1, .moving = 0, .ducking = 0 };
	plr.key = (t_keys){ .w = 0, .s = 0, .a = 0, .d = 0 };
	sdl.buffer = buffer;
	plr.sdl = &sdl;
	plr.num_scts = 0;

	load_data(&plr, &sectors);

	if (SDL_Init(SDL_INIT_EVERYTHING != 0))
		printf("init");
	//request = SDL_GetDesktopDisplayMode(0, &sdl.display_mode);
	sdl.window = SDL_CreateWindow("Doom Nukem", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, W, H,  SDL_WINDOW_SHOWN);
	if (!sdl.window)
		printf("win");
	sdl.renderer = SDL_CreateRenderer(sdl.window, -1, SDL_RENDERER_ACCELERATED);
	if (!sdl.renderer)
		printf("renderer");
	sdl.texture = SDL_CreateTexture(sdl.renderer, SDL_PIXELFORMAT_ARGB32, SDL_TEXTUREACCESS_STREAMING, W, H);
	plr.ms.yaw = 0;
	game_loop(&sdl, &plr, sectors);
	SDL_DestroyWindow(sdl.window);
	SDL_Quit();
	return (0);
}
