#include <AppleTextureEncoder.h>
#include "doom_nukem.h"

bool Overlap(float a0, float a1, float b0, float b1)
{
	if ((min(a0,a1) <= max(b0,b1) && min(b0,b1) <= max(a0,a1)))
		return (true);
	else
		return (false);
}

float IntersectBox(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3)
{
	float result;
	result = (Overlap(x0,x1,x2,x3) && Overlap(y0,y1,y2,y3));
	return (result);
}

float PointSide(float px, float py, float x0, float y0, float x1, float y1)
{
	float result;
	result = vxs((x1)-(x0), (y1)-(y0), (px)-(x0), (py)-(y0));
	return (result);
}

t_xy Intersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
	t_xy result;

	result = (t_xy) {.x = vxs(vxs(x1,y1, x2,y2), (x1)-(x2), vxs(x3,y3, x4,y4), (x3)-(x4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)), \
	.y = vxs(vxs(x1,y1, x2,y2), (y1)-(y2), vxs(x3,y3, x4,y4), (y3)-(y4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4))};
	return (result);
}

/* Define various vision related constants */
static void UnloadData(t_sector **sectors, t_player *plr)
{
	for (unsigned a = 0; a < plr->num_scts; ++a)
		free((*sectors)[a].vertex);
	for (unsigned a = 0; a < plr->num_scts; ++a)
		free((*sectors)[a].neighbors);
	free(*sectors);
	*sectors = NULL;
	plr->num_scts = 0;
}

/* vline: Draw a vertical line on screen, with a different color pixel in top & bottom */
void vline(int x, int y1, int y2, int color, t_player *player)
{
	int *pix = (int *)player->sdl->buffer;
	y1 = clamp(y1, 0, H - 1);
	y2 = clamp(y2, 0, H - 1);
	if (y2 == y1)
		pix[y1 * W + x] = BLACK_COLOR; //нижня межа вікна
	else if (y2 > y1)
	{
		pix[y1 * W + x] = SEC_COLOR; //проміжок секторів
		if (y1 == 0 || y1 == 1)
			pix[y1 * W + x] = BLACK_COLOR; //верхня межа вікна
		for (int y = y1 + 1; y <= y2; ++y)
			pix[y * W + x] = color;
		pix[y2 * W + x] = color;
	}
}

/* MovePlayer(dx,dy): Moves the player by (dx,dy) in the map, and
 * also updates their anglesin/anglecos/sector properties properly.
 */
static void MovePlayer(t_player *plr, t_sector **sectors, float dx, float dy)
{
	t_sector	*sect;
	t_xy		*vert;
	float		px;
	float		py;
	unsigned	s;

	px = plr->where.x;
	py = plr->where.y;
	sect = &(*sectors)[plr->sector];
	vert = sect->vertex;
	s = 0;
	while (s < sect->npoints)
	{
		if (sect->neighbors[s] >= 0 &&
			IntersectBox(px, py, px + dx, py + dy, vert[s + 0].x,
					vert[s + 0].y, vert[s + 1].x, vert[s + 1].y) &&
		 	PointSide(px + dx, py + dy, vert[s + 0].x, vert[s + 0].y,
					  vert[s + 1].x, vert[s + 1].y) < 0)
		{
			plr->sector = sect->neighbors[s];
			break;
		}
		s++;
	}
	plr->where.x += dx;
	plr->where.y += dy;
	plr->anglesin = sinf(plr->angle);
	plr->anglecos = cosf(plr->angle);
}

int 		exit_doom(t_sector **sectors, t_player *plr)
{
	printf("NO-NO-NO-NO\n");
	printf("%d NO-NO-NO-NO\n", plr->num_scts);
	UnloadData(&(*sectors), &(*plr));
	SDL_Quit();
	exit(0);
}

void		do_fall(t_player *plr, t_sector **sectors)
{
	float nextz;

	plr->vlct.z -= 0.05f; /* Add gravity */
	nextz = plr->where.z + plr->vlct.z;
	if (plr->vlct.z < 0 && nextz < (*sectors)[plr->sector].floor + plr->eyeheight) // When going down
	{
		plr->where.z = (*sectors)[plr->sector].floor + plr->eyeheight; /* Fix to ground */
		plr->vlct.z = 0;
		plr->falling = 0;
		plr->ground = 1;
	}
	else if (plr->vlct.z > 0 && nextz > (*sectors)[plr->sector].ceil) // When going up
	{
		plr->vlct.z = 0; /* Prevent jumping above ceiling */
		plr->falling = 1;
	}
	if (plr->falling)
	{
		plr->where.z += plr->vlct.z;
		plr->moving = 1;
	}
}

void		chholebump(t_sector **sectors, t_sector sect, const unsigned int *s,
					   t_player *plr, t_xy **vert, float *dx, float *dy)
{
	/* Check where the hole is. */
	float hole_low;
	float hole_high;

	hole_low = sect.neighbors[*s] < 0 ?
			   9e9 : max(sect.floor, (*sectors)[sect.neighbors[*s]].floor);
	hole_high = sect.neighbors[*s] < 0 ?
				-9e9 : min(sect.ceil, (*sectors)[sect.neighbors[*s]].ceil);
	/* Check whether we're bumping into a wall. */
	if (hole_high < plr->where.z + HeadMargin || hole_low > plr->where.z - plr->eyeheight + KneeHeight)
	{
		float xd;
		float yd;

		xd = (*vert)[*s + 1].x - (*vert)[*s + 0].x;
		yd = (*vert)[*s + 1].y - (*vert)[*s + 0].y;

		*dx = xd * (*dx * xd + yd * *dy) / (xd * xd + yd * yd);
		*dy = yd * (*dx * xd + yd * *dy) / (xd * xd + yd * yd);
		plr->moving = 0;
	}
}

void		do_move(t_player *plr, t_sector **sc)
{
	unsigned int	s;
	float 			px;
	float 			py;
	float 			dx;
	float 			dy;

	px = plr->where.x;
	py = plr->where.y;
	dx = plr->vlct.x;
	dy = plr->vlct.y;
	(*sc)->vert = (*sc)[plr->sector].vertex;
	s = -1;
	while (++s < (*sc)[plr->sector].npoints)
	{
		if (IntersectBox(px, py, px + dx, py + dy, (*sc)->vert[s + 0].x,
			(*sc)->vert[s + 0].y, (*sc)->vert[s + 1].x, (*sc)->vert[s + 1].y)
			&& PointSide(px + dx, py + dy, (*sc)->vert[s + 0].x,
			(*sc)->vert[s + 0].y, (*sc)->vert[s + 1].x, (*sc)->vert[s + 1].y) < 0)
			chholebump(sc, (*sc)[plr->sector], &s, plr, &(*sc)->vert, &dx, &dy);
	}
	MovePlayer(plr, sc, dx, dy);
	plr->falling = 1;
}

int g_x = 0;

void		events(t_sector **sectors, t_player *plr, bool *quit)
{
	const Uint8		*kstate; // array of keyboard keys states
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
			if (ev.key.keysym.sym == SDLK_SPACE && plr->ground)
			{
				plr->vlct.z += 0.5;
				plr->falling = 1;
			}
		}
//		if (kstate[SDL_SCANCODE_SPACE] && plr->ground)
//		{
//			printf("%d SPACE CODE: %d\n", ++g_x, kstate[SDL_SCANCODE_SPACE]);
//			plr->vlct.z += 0.25;
//			plr->falling = 1;
//		}
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
		events(&sectors, plr, &quit);
		plr->eyeheight = plr->ducking ? DuckHeight : EyeHeight; /* Vertical collision detection */
		plr->ground = !plr->falling;
		if (plr->falling) //TODO: make ducking unreversable if стеля згори
			do_fall(plr, &sectors);
		if (plr->moving) /* Horizontal collision detection */
			do_move(plr, &sectors);
		/* mouse aiming */
		plr->ms.x = 0;
		plr->ms.y = 0;
		SDL_GetRelativeMouseState(&plr->ms.x, &plr->ms.y);
		plr->angle += plr->ms.x * 0.03f;
		plr->ms.yaw = clamp(plr->ms.yaw - plr->ms.y * 0.05f, -5, 5);
		plr->yaw = plr->ms.yaw - plr->vlct.z * 0.5f;
		plr->mv = (t_move_vec){.x = 0.f, .y = 0.f};
		MovePlayer(plr, &sectors, 0, 0);
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
		draw_screen(sectors, *plr);
		SDL_UpdateTexture(sdl->texture, NULL, sdl->buffer,W *(sizeof(int)));
		SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
		SDL_RenderPresent(sdl->renderer);
		SDL_Delay(15);
	}
}

int 		main(void)
{
	t_player		plr;
	t_sdl_main		sdl;
	t_sector	*sectors;
	int 		*buffer;

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
	int request = SDL_GetDesktopDisplayMode(0, &sdl.display_mode);
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
