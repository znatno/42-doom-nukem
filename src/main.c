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

void	print_data_ds(t_player *p)
{
	printf("\n---------------------\n");
	printf("| player_x = %5f | player_y = %5f |\n", p->where.x, p->where.y);
	printf("| vlct_x = %5f | vlct_y = %5f | vlct_z = %5f|\n", p->vlct.x, p->vlct.y, p->vlct.z);
	printf("| angle = %f | ang_sin = %5f | ang_cos = %5f | yaw = %5f|\n", p->angle, p->anglesin, p->anglecos, p->yaw);
	printf("| cur_s = %u | num_s = %u|\n", p->sector, p->num_scts);
	printf("| ground = %i | falling = %i | moving = %i | ducking = %i | eyeheight = %5f|\n", p->ground, p->falling, p->moving, p->ducking,p->eyeheight);
	printf("| move_x = %5f | move_y = %5f |\n", p->mv.x, p->mv.y);
	printf("| mouse_aim_x = %i | mouse_aim_y = %i | mouse_aim_yaw = %5f |\n", p->ms.x, p->ms.y, p->ms.yaw);
	printf("---------------------\n");
}

void		events(t_sector **sectors, t_player *plr, t_sounds *sounds)
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
			if (ev.key.keysym.sym == ' ')
			{
				Mix_HaltChannel(RUN);
				Mix_HaltChannel(FAST_RUN);
				if (!Mix_Playing(JUMP) && plr->ground && !plr->ducking)
					Mix_PlayChannel(JUMP, sounds->jumpbreath, 0);
			}
			if (ev.key.keysym.sym == ' ' && plr->ground
				&& plr->where.z == (*sectors)[plr->sector].floor + EyeHeight)
			{
				plr->vlct.z += 0.5;
				plr->falling = 1;
				plr->jump_check = true;
			}

			if (ev.key.keysym.sym == 'p') //TODO: вивід корисної інфи для дебаґу
			{
//				TTF_Font *font = getFont("../Lato-Regular.ttf", 26);
//				plr->sdl->w_surface = renderFontToSurface(font, "xyi");
//				SDL_UpdateWindowSurface(plr->sdl->window);
//				SDL_Delay(20000);
//				exit_doom(sectors, plr);

/*				printf("\n\t---------------------------\n");
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

				printf("\n\t---------------------------\n\n");*/

				print_data_ds(plr);
			}

			if (ev.key.keysym.sym == SDLK_LCTRL)
				plr->ducking = !plr->ducking ? 1 : 0;
		}
		if ((*sectors)[plr->sector].ceil <= (*sectors)[plr->sector].floor + EyeHeight)
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

void		game_loop(t_sdl_main *sdl, t_player *plr, t_sector *sectors, t_sounds *sounds)
{
	bool 			quit;

	quit = false;
	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	while(!quit)
	{
//		printf("Duck: %d\n", plr->ducking);
		//printf("x: %d\ty: %d\n", plr->ms.x, plr->ms.y);

		/* Очищує буфер чорним кольором */
		//SDL_FillRect(sdl->w_surface, NULL,
		//		SDL_MapRGB(sdl->w_surface->format, 0, 0, 0));

		/* Key Events */
		events(&sectors, plr, sounds);
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
			do_fall(plr, &sectors, sounds);
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

		if (plr->pushing && !plr->ducking && plr->ground && !plr->run && !Mix_Playing(RUN))
			Mix_PlayChannel(RUN, sounds->run_sound, 0);
		if (plr->ducking && plr->pushing && !Mix_Playing(SEAT_RUN))
			Mix_PlayChannel(SEAT_RUN, sounds->low_run, 0);
		if (plr->speed == 0.28f && !Mix_Playing(FAST_RUN) && plr->pushing && !plr->jump_check)
			Mix_PlayChannel(FAST_RUN, sounds->fast_run, 0);
		if (!plr->pushing || plr->speed != 0.28f)
			Mix_HaltChannel(FAST_RUN);
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

t_sounds *init_music_n_sounds() {
	int audio_rate = 42000;
	Uint16 audio_format = AUDIO_S16SYS;
	int audio_channels = 2;
	int audio_buffers = 4096;
	t_sounds *sounds;

	sounds = (t_sounds *) malloc(sizeof(t_sounds));
	SDL_Init(SDL_INIT_AUDIO);
	Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers);
	sounds->bg_music = Mix_LoadMUS("../sounds/bestmusic.wav");
	sounds->run_sound = Mix_LoadWAV("../sounds/run.wav");
	sounds->jumpbreath = Mix_LoadWAV("../sounds/jumpbreath.wav");
	sounds->landing = Mix_LoadWAV("../sounds/land2.wav");
	sounds->fast_run = Mix_LoadWAV("../sounds/fast_run.wav");
	sounds->low_run = Mix_LoadWAV("../sounds/run.wav");
	Mix_VolumeMusic(30);
	Mix_Volume(RUN, 20);
	Mix_Volume(SEAT_RUN, 10);
	Mix_Volume(FAST_RUN, 20);
	return (sounds);

}

int 		main(void)
{
	t_player	plr;
	t_textures	tex;
	t_sdl_main	sdl;
	t_sector	*sectors;
	t_sounds	*sounds;

	sectors = NULL;
	plr = (t_player){ .ground = 0, .falling = 1, .moving = 0, .ducking = 0,
						.eyeheight = EyeHeight };
	plr.key = (t_keys){ .w = 0, .s = 0, .a = 0, .d = 0 };
	plr.sdl = &sdl;
	sdl.textures = &tex;
	plr.num_scts = 0;

	//

	//

	load_data(&plr, &sectors);
	textures_init(&sdl);

	if (SDL_Init(SDL_INIT_EVERYTHING != 0) || TTF_Init() == -1)
		printf("init");
	sdl.window = SDL_CreateWindow("Doom Nukem", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, W, H,  SDL_WINDOW_SHOWN);
	if (!sdl.window)
		printf("win");
	sounds = init_music_n_sounds();
	sdl.win_surface = SDL_GetWindowSurface(sdl.window);
	plr.ms.yaw = 0;
	Mix_PlayMusic(sounds->bg_music, -1);
	game_loop(&sdl, &plr, sectors, sounds);
	SDL_DestroyWindow(sdl.window);
	SDL_Quit();
	return (0);
}
