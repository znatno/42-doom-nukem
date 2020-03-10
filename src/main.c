/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibohun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:03:03 by ibohun            #+#    #+#             */
/*   Updated: 2019/08/24 22:24:27 by ibohun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define FILE_NAME "test2.map"
#include "doom_nukem.h"



void		events(t_game *g)
{
	const uint8_t	*kstate;	//	array of keyboard keys states
	SDL_Event		ev;
	Uint8 			mouse_state = 0;
	kstate = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&ev))
	{
		mouse_state = 0;
		if (kstate[SDL_SCANCODE_ESCAPE] || ev.type == SDL_QUIT)
			exit_doom(g);

		g->plr.key.w = kstate[SDL_SCANCODE_W];
		g->plr.key.a = kstate[SDL_SCANCODE_A];
		g->plr.key.s = kstate[SDL_SCANCODE_S];
		g->plr.key.d = kstate[SDL_SCANCODE_D];
		g->plr.draw_look = kstate[SDL_SCANCODE_L];

//		if (ev.button.button == SDL_BUTTON_LEFT && g->wpn.sprite_counter == 1 && g->wpn.type == 1)
//		{
//			if (g->wpn.sprite_counter == 1)
//				g->wpn.sprite_counter += 0.5;
//			printf("hello");
//		}
//		if (SDL_MOUSEBUTTONDOWN || SDL_MOUSEBUTTONUP) {
//			mouse_state = ev.button.state;
//			printf("MOUSE STAT = %d\n", mouse_state);
//		}
//		if (SDL_MOUSEMOTION) {
//			mouse_state = ev.motion.state;
//			printf("MOUTION STAT = %d\n", mouse_state);
//		}
//		if (ev.button.state &&  g->wpn.sprite_counter == 1 && g->wpn.type == 2)
//		{
//			if (g->wpn.sprite_counter == 1)
//				g->wpn.sprite_counter += 1;
//			g->plr.light = 8;
//		}
//		if (!ev.button.state && g->wpn.sprite_counter == 2 && g->wpn.type == 2)
//		{
//			g->wpn.sprite_counter = 1;
//			g->plr.light = 16;
//		}
		if (ev.type == SDL_MOUSEBUTTONDOWN && g->wpn.sprite_counter == 1 && g->wpn.type == 2)
		{

//			g->key_down = 1;
			if (g->wpn.sprite_counter == 1)
				g->wpn.sprite_counter += 1;
			g->plr.light = 8;
		}
		if (ev.type == SDL_MOUSEBUTTONUP && g->wpn.sprite_counter == 2 && g->wpn.type == 2)
		{
//			g->key_down = 0;
			g->wpn.sprite_counter = 1;
			g->plr.light = 16;
		}
		printf("key_down = %d\n", g->key_down);
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

			if (ev.key.keysym.sym == 'p')
			{
				printf("Position\n");
				printf("%f\t%f\t%f\n\n",
						g->plr.where.x, g->plr.where.y, g->plr.where.z);
				if (g->plr.sector == 0)
				{
					printf("Object\n");
					printf("sector: %u, x: %f, y: %f, a: %u, hp: %d\n\n",
						   g->sectors[g->plr.sector].objects[0]->sector,
						   g->sectors[g->plr.sector].objects[0]->pos.x,
						   g->sectors[g->plr.sector].objects[0]->pos.y,
						   g->sectors[g->plr.sector].objects[0]->animated,
						   g->sectors[g->plr.sector].objects[0]->hp);
				}

				//g->msgs[1] = create_msg("Between two girls & one cup",
				//		FONT_M_SM, (t_xy_int){64, 96}, 5);

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

void		draw_cur_lighter_sprite(t_game *g, int width, int height, int curSprite)
{
	int		x;
	int		y;
	int		x_img;
	float	x_num;
	float	y_num;

	y = 0;
	y_num = 0;
	while (y < 128 && height < H)
	{
		x = 0;
		x_num = 0;
		x_img = width;
		while (x < 128 - 1 && x_img < W)
		{
			x_num += 0.5;
			x = (int)x_num;
			if (g->wpn.lighter_sprite[curSprite][y][x] != 255)
				g->sdl.buffer[height * W + x_img] = g->wpn.lighter_sprite[curSprite][y][x];
//			printf("%d ", g->wpn.lighter_sprite[curSprite][y][x]);
			x_img++;
		}
//		printf("\n");
		y_num += 0.5;
		y = (int)y_num;
		height++;
	}
}

void		draw_cur_pistol_sprite(t_game *g, int width, int height, int curSprite)
{
	int		x;
	int		y;
	int		x_img;
	float	x_num;
	float	y_num;

	y = 0;
	y_num = 0;
	while (y < 128 && height < H)
	{
		x = 0;
		x_num = 0;
		x_img = width;
		while (x < 128 - 1 && x_img < W)
		{
			x_num += 0.35;
			x = (int)x_num;
			if (g->wpn.pistol_sprite[curSprite][y][x] != 0x000000)
				g->sdl.buffer[height * W + x_img] = g->wpn.pistol_sprite[curSprite][y][x];
			x_img++;
		}
		y_num += 0.5;
		y = (int)y_num;
		height++;
	}
}

void		draw_lighter(t_game *g)
{
	if (g->wpn.sprite_counter == 1)
		draw_cur_lighter_sprite(g, W - 550, H - 250, 0);
	else if (g->wpn.sprite_counter == 2)
		draw_cur_lighter_sprite(g, W - 550, H - 250, 1);
}

void		draw_pistol(t_game *g)
{
	if (g->wpn.sprite_counter == 1)
		draw_cur_pistol_sprite(g, W - 400, H - 250, 0);
	else if (g->wpn.sprite_counter > 1)
	{
		draw_cur_pistol_sprite(g, W - 400, H - 250, g->wpn.sprite_counter - 1);
		g->wpn.sprite_counter += 0.5;
	}
	if (g->wpn.sprite_counter >= 6)
		g->wpn.sprite_counter = 1;
}

void		draw_weapons(t_game *g)
{
	if (g->wpn.type == 1)
		draw_pistol(g);
	else if (g->wpn.type == 2)
		draw_lighter(g);
}

void		game_loop(t_game *g)
{
	g->msgs[0] = create_msg("Episode 1", FONT_M_BG, (t_xy_int){40, 64}, 5);
	g->msgs[1] = create_msg("HP: 100/100", FONT_M_MD, (t_xy_int){32, 680}, -1);
	g->msgs[2] = create_msg("Notes: 0/10", FONT_M_MD, (t_xy_int){32, 720}, -1);
	while (true)
	{

		/* Очищує буфер чорним кольором */
		//SDL_RenderClear(g->sdl.renderer);
		//SDL_FillRect(g->sdl.texture, NULL, SDL_MapRGB(g->sdl.w_surface->format, 0, 0, 0));


		//SDL_Fill

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
		draw_screen(g);

		draw_weapons(g);
		/* update window */
		SDL_UpdateTexture(g->sdl.texture, NULL, g->sdl.buffer, W * (sizeof(int)));
		SDL_RenderCopy(g->sdl.renderer, g->sdl.texture, NULL, NULL);

		/* place texts */
		get_messages(g);

		SDL_RenderPresent(g->sdl.renderer);
		//SDL_Delay(20);
	}
}

SDL_Surface		*load_lighter_part(int sprite)
{
	SDL_Surface *curSprite;

	curSprite = (SDL_Surface *)malloc(sizeof(SDL_Surface));
	if (sprite == 0)
		curSprite = IMG_Load("../sprites/3.png");
	if (sprite == 1)
		curSprite = IMG_Load("../sprites/1.png");
	curSprite = SDL_ConvertSurfaceFormat(curSprite, SDL_PIXELFORMAT_ARGB32, 0);
	return (curSprite);
}

SDL_Surface		*load_pistol_part(int sprite)
{
	SDL_Surface *curSprite;

	curSprite = (SDL_Surface *)malloc(sizeof(SDL_Surface));
	if (sprite == 0)
		curSprite = IMG_Load("../sprites/pistol1.png");
	if (sprite == 1)
		curSprite = IMG_Load("../sprites/pistol2.png");
	if (sprite == 2)
		curSprite = IMG_Load("../sprites/pistol3.png");
	if (sprite == 3)
		curSprite = IMG_Load("../sprites/pistol4.png");
	if (sprite == 4)
		curSprite = IMG_Load("../sprites/pistol5.png");
	if (sprite == 5)
		curSprite = IMG_Load("../sprites/pistol6.png");
	curSprite = SDL_ConvertSurfaceFormat(curSprite, SDL_PIXELFORMAT_ARGB32, 0);
	return (curSprite);
}

int		load_lighter_sprite(t_game *g, int spriteCount)
{
	SDL_Surface		*curSprite;
	unsigned int	*pixels;
	int				x;
	int				y;

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		ft_putendl(IMG_GetError());
	curSprite = load_lighter_part(spriteCount);
	y = -1;
	pixels = (unsigned int *)curSprite->pixels;
	while (++y < 128)
	{
		x = -1;
		while (++x < 128)
			g->wpn.lighter_sprite[spriteCount][y][x] = pixels[(y * curSprite->w) + x];
	}
	SDL_FreeSurface(curSprite);
	ft_putendl("Lighter Part Loaded!");
	return (1);
}

int		load_pistol_sprite(t_game *g, int spriteCount)
{
	SDL_Surface		*curSprite;
	unsigned int	*pixels;
	int				x;
	int				y;

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		ft_putendl(IMG_GetError());
	curSprite = load_pistol_part(spriteCount);
	y = -1;
	pixels = (unsigned int *)curSprite->pixels;
	while (++y < 128)
	{
		x = -1;
		while (++x < 128)
			g->wpn.pistol_sprite[spriteCount][y][x] = pixels[(y * curSprite->w) + x];
	}
	SDL_FreeSurface(curSprite);
	ft_putendl("Pistol Part Loaded!");
	return (1);
}

void		load_lighter(t_game *g)
{
	int y;
	int sprite;
	int maxSprites;

	maxSprites = 2;
	g->wpn.lighter_sprite = (int***)malloc(sizeof(int **) * maxSprites);
	sprite = 0;
	while (sprite < maxSprites)
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
	int maxSprites;

	maxSprites = 6;
	g->wpn.pistol_sprite = (int***)malloc(sizeof(int **) * maxSprites);
	sprite = 0;
	while (sprite < maxSprites)
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
	g->wpn.type = 2;
	load_pistol(g);
	load_lighter(g);
}

int 		main(void)
{
	t_game	g;

	//Structs initialization
	g.sectors = NULL;
	g.plr = (t_player){.falling = 1, .eyeheight = EYE_H, .sdl = &g.sdl};

	init_msgs(&g);

	//Framework initialization
	init_sdl(&g);

	//Load map
	load_data(&g.plr, &g.sectors);

	/**/
	//object test
	g.sectors[0].objs = 2;
	g.sectors[0].objects = ft_memalloc(sizeof(t_obj*));
	for (int i = 0; i < g.sectors->objs; i++)
		g.sectors[0].objects[i] = ft_memalloc(sizeof(t_obj));

	g.sectors[0].objects[0]->pos.x = 4;
	g.sectors[0].objects[0]->pos.y = 8;
	//z = 6
	g.sectors[0].objects[0]->sector = 0;
	g.sectors[0].objects[0]->texture = (SDL_Surface **)malloc(sizeof
	(SDL_Surface *) * 6);
	g.sectors[0].objects[0]->texture[0] = IMG_Load("../sprites/barrel.png");
	g.sectors[0].objects[0]->hp = -1;
	g.sectors[0].objects[0]->animated = 0;
	/**/

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
