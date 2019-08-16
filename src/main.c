/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibohun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:03:03 by ibohun            #+#    #+#             */
/*   Updated: 2019/08/16 19:32:03 by ibohun           ###   ########.fr       */
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
		plr->draw_look = kstate[SDL_SCANCODE_L];
		if (ev.type == SDL_KEYDOWN)
		{
			if (ev.key.keysym.sym == ' ' && plr->ground
				&& plr->where.z == (*sectors)[plr->sector].floor + EyeHeight)
			{
				plr->vlct.z += 0.5;
				plr->falling = 1;
			}

			if (ev.key.keysym.sym == 'p') //TODO: вивід корисної інфи для дебаґу
			{
				/*TTF_Font *font = getFont("../Lato-Regular.ttf", 26);
				plr->sdl->w_surface = renderFontToSurface(font, "xyi");*/
				SDL_UpdateWindowSurface(plr->sdl->window);
				SDL_Delay(20000);
				exit_doom(sectors, plr);

				printf("\n\t---------------------------\n");
				printf("\t\t\t[print msg]\n");
				// поточний сектор
				printf("\tplr->speed: %f\n\n", plr->speed);
				printf("\tcurr sec: %d\n", plr->sector);
				printf("\tceil: %f\n", (*sectors)[plr->sector].ceil);
				printf("\tfloor: %f\n\n", (*sectors)[plr->sector].floor);
				// поточна позиція
				printf("\tx: %f\t\ty: %f\t\tz: %f\n",
						plr->where.x, plr->where.y, plr->where.z);
				// кути погляду
				printf("\tangle: %f\t\tyaw: %f\n",
					   plr->angle, plr->yaw);

				printf("\n\t---------------------------\n\n");
			}

			if (ev.key.keysym.sym == SDLK_LCTRL)
				plr->ducking = !plr->ducking ? 1 : 0;
		}
		if ((*sectors)[plr->sector].ceil < plr->where.z + HeadMargin)
			plr->ducking = true;
		if (plr->ducking)
		{
			plr->falling = 1;
			plr->eyeheight = DuckHeight;
		}
		plr->run = kstate[SDL_SCANCODE_LSHIFT];
		plr->speed = plr->run && plr->eyeheight != DuckHeight ? 0.28f : 0.20f;
		SDL_PumpEvents(); // обработчик событий
	}
}

void		showmsg(t_sdl_main *sdl)
{
	TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24);
	//this opens a font style and sets a size

	SDL_Color White = {255, 255, 255};
	// this is the color in rgb format, maxing out all would give you the color
	// white, and it will be your text's color

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "put your text here", White);
	// as TTF_RenderText_Solid could only be used on SDL_Surface then you have
	// to create the surface first

	//SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer,surfaceMessage);
	//now you can convert it into a texture

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = 0;  //controls the rect's x coordinate
	Message_rect.y = 0; // controls the rect's y coordinte
	Message_rect.w = 100; // controls the width of the rect
	Message_rect.h = 100; // controls the height of the rect

	//Mind you that (0,0) is on the top left of the window/screen, think a rect as
	// the text's box, that way it would be very simple to understance

	//Now since it's a texture, you have to put RenderCopy in your game loop area,
	// the area where the whole code executes

	//SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
	//you put the renderer's name first, the Message, the crop size(you can
	// ignore this if you don't want to dabble with cropping), and the rect
	// which is the size and coordinate of your texture

	//Don't forget too free your surface and texture
}

void		game_loop(t_sdl_main *sdl, t_player *plr, t_sector *sectors)
{
	bool 			quit;

	quit = false;
	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	while(!quit)
	{
		//printf("x: %d\ty: %d\n", plr->ms.x, plr->ms.y);

		/* Очищує буфер чорним кольором */
		//SDL_FillRect(sdl->w_surface, NULL,
		//		SDL_MapRGB(sdl->w_surface->format, 0, 0, 0));

		/* Key Events */
		events(&sectors, plr);
		//printf("fall: %d\tground: %d\n", plr->falling, plr->ground);

		//printf("DUCK: %d \n",plr->ducking);

		//printf("push: %d, w: %d, a: %d, s: %d, d: %d\n",
		//		plr->pushing, plr->key.w, plr->key.a, plr->key.s, plr->key.d);

		/* Камера при присяді і її підняття */
		if (plr->ducking || plr->eyeheight == DuckHeight)
			plr->speed /= 1.5f;
		if (plr->eyeheight != EyeHeight && !plr->ducking &&
			sectors[plr->sector].ceil > sectors[plr->sector].floor + EyeHeight)
			plr->eyeheight += 0.5f;
		else if (plr->eyeheight != DuckHeight && sectors[plr->sector].ceil
					<= sectors[plr->sector].floor + EyeHeight)
			plr->eyeheight -= 0.5f;

		plr->ground = !plr->falling; /* Vertical collision detection */
		if (plr->falling)
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
		/*else // припинення ходьби після відтиску клавіші
			plr->moving = 0;*/

		draw_screen(sectors, *plr);
		//showmsg("Game Loop");
		SDL_UpdateWindowSurface(sdl->window);
		SDL_Delay(20);
	}
}

int 		main(void)
{
	t_player	plr;
	t_sdl_main	sdl;
	t_sector	*sectors;

	sectors = NULL;
	plr = (t_player){ .ground = 0, .falling = 1, .moving = 0, .ducking = 0,
						.eyeheight = EyeHeight };
	plr.key = (t_keys){ .w = 0, .s = 0, .a = 0, .d = 0 };
	plr.sdl = &sdl;
	plr.num_scts = 0;

	//

	//

	load_data(&plr, &sectors);

	if (SDL_Init(SDL_INIT_EVERYTHING != 0) || TTF_Init() == -1)
		printf("init");
	sdl.window = SDL_CreateWindow("Doom Nukem", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, W, H,  SDL_WINDOW_SHOWN);
	if (!sdl.window)
		printf("win");
	sdl.w_surface = SDL_GetWindowSurface(sdl.window);
	plr.ms.yaw = 0;
	game_loop(&sdl, &plr, sectors);
	SDL_DestroyWindow(sdl.window);
	SDL_Quit();
	return (0);
}
