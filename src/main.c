#include <AppleTextureEncoder.h>
#include "sdl1.h"

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

/* VOPOLONC PART START */
/* Define various vision related constants */

static void LoadData(t_player *plr, t_sector **sectors)
{
	FILE *fp = fopen("test.txt", "rt");
	if (!fp)
	{
		perror("map-clear.txt");
		exit(1);
	}
	char Buf[256], word[256], *ptr;

	t_xy *vert;
	t_xy v;

	vert = NULL;

	int n, m, NumVertices = 0;

	while (fgets(Buf, sizeof Buf, fp))
		switch (sscanf(ptr = Buf, "%32s%n", word, &n) == 1 ? word[0] : '\0')
		{
			case 'v': // vertex
				for (sscanf(ptr += n, "%f%n", &v.y, &n);
					 sscanf(ptr += n, "%f%n", &v.x, &n) == 1;)
				{
					vert = realloc(vert, ++NumVertices * sizeof(*vert));
					vert[NumVertices - 1] = v;
				}
				break;
			case 's': // sector
				*sectors = realloc(*sectors, ++plr->num_scts * sizeof
				(**sectors));
				t_sector *sect;
				sect = &(*sectors)[plr->num_scts - 1];
				int *num = NULL;
				sscanf(ptr += n, "%f%f%n", &sect->floor, &sect->ceil, &n);
				for (m = 0; sscanf(ptr += n, "%32s%n", word, &n) == 1 &&
							word[0] != '#';)
				{
					num = realloc(num, ++m * sizeof(*num));
					num[m - 1] = word[0] == 'x' ? -1 : atoi(word);
				}
				sect->npoints = m /= 2;
				sect->neighbors = malloc((m) * sizeof(*sect->neighbors));
				sect->vertex = malloc((m + 1) * sizeof(*sect->vertex));
				for (n = 0; n < m; ++n) sect->neighbors[n] = num[m + n];
				for (n = 0; n < m; ++n)
					sect->vertex[n + 1] = vert[num[n]]; // T0D0: Range checking
				sect->vertex[0] = sect->vertex[m]; // Ensure the vertexes form a
				// loop
				free(num);
				break;
			case 'p':; // player
				float angle;
				sscanf(ptr += n, "%f %f %f %d", &v.x, &v.y, &angle, &n);
				*plr = (t_player){{v.x, v.y, 0}, {0, 0, 0}, \
						angle, 0, 0, 0, n, plr->num_scts};
				// T0D0: Range checking
				plr->where.z = sectors[plr->sector]->floor + EyeHeight;
		}
	fclose(fp);
	free(vert);
}

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
/* VOPOLONC PART END */

/* IBOHUN PART 1 START */
/* vline: Draw a vertical line on screen, with a different color pixel in top & bottom */
void vline(int x, int y1, int y2, int color)
{
	int *pix = (int *) surface->pixels;
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
/* IBOHUN PART 1 END */
/* IBOHUN (& somebody else) PART 2 START */
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

void		chholebump(t_sector **sectors, t_sector sect, unsigned int *s,
					   t_player *plr, t_xy **vert, float *dx, float *dy)
{
	float hole_low; /* Check where the hole is. */
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

void		events(SDL_Event ev, t_sector **sectors, t_player *plr)
{
	if (ev.type)
	{
		if (ev.key.keysym.sym == 'w')
			plr->key.w = ev.type == SDL_KEYDOWN;
		else if (ev.key.keysym.sym == 'a')
			plr->key.a = ev.type == SDL_KEYDOWN;
		else if (ev.key.keysym.sym == 's')
			plr->key.s = ev.type == SDL_KEYDOWN;
		else if (ev.key.keysym.sym == 'd')
			plr->key.d = ev.type == SDL_KEYDOWN;
		else if (ev.key.keysym.sym == ' ' && plr->ground)
		{
				plr->vlct.z += 0.5;
				plr->falling = 1;
		}
		else if (ev.key.keysym.sym == 'q')
			exit_doom(sectors, plr);
		else if (ev.key.keysym.sym == SDLK_LCTRL)
		{
			plr->ducking = ev.type == SDL_KEYDOWN;
			plr->falling = 1;
		}
		else if (ev.type == SDL_QUIT)
			exit_doom(sectors, plr);
	}
}

int 		main()
{
	t_player	plr;
	t_sector	*sectors;


	sectors = NULL;
	plr.num_scts = 0;
	plr = (t_player){ .ground = 0, .falling = 1, .moving = 0, .ducking = 0 };
	plr.key = (t_keys){ .w = 0, .s = 0, .a = 0, .d = 0 };

	LoadData(&plr, &sectors);

	surface = SDL_SetVideoMode(W, H, 32, 0);

	SDL_EnableKeyRepeat(150, 30);
	SDL_ShowCursor(SDL_DISABLE);

	plr.ms.yaw = 0;
	while (1)
	{
		SDL_LockSurface(surface);
		draw_screen(sectors, plr);
		SDL_UnlockSurface(surface);
		SDL_Flip(surface);
		plr.eyeheight = plr.ducking ? DuckHeight : EyeHeight; /* Vertical collision detection */
		plr.ground = !plr.falling;
		if (plr.falling) //TODO: make ducking unreversable if стеля згори
			do_fall(&plr, &sectors);
		if (plr.moving) /* Horizontal collision detection */
			do_move(&plr, &sectors);
		SDL_Event ev;
		while (SDL_PollEvent(&ev))
			if (ev.type)
				events(ev, &sectors, &plr); /* events(); */
		/* mouse aiming */
		plr.ms.x = 0;
		plr.ms.y = 0;
		SDL_GetRelativeMouseState(&plr.ms.x, &plr.ms.y);
		plr.angle += plr.ms.x * 0.03f;
		plr.ms.yaw = clamp(plr.ms.yaw - plr.ms.y * 0.05f, -5, 5);
		plr.yaw = plr.ms.yaw - plr.vlct.z * 0.5f;
		MovePlayer(&plr, &sectors, 0, 0);
		plr.mv = (t_move_vec){.x = 0.f, .y = 0.f};
		if (plr.key.w)
			plr.mv = (t_move_vec){.x = plr.mv.x + plr.anglecos * 0.2f,
						 			.y = plr.mv.y + plr.anglesin * 0.2f};
		if (plr.key.s)
			plr.mv = (t_move_vec){.x = plr.mv.x - plr.anglecos * 0.2f,
						 			.y = plr.mv.y - plr.anglesin * 0.2f};
		if (plr.key.a)
			plr.mv = (t_move_vec){.x = plr.mv.x + plr.anglesin * 0.2f,
						 			.y = plr.mv.y - plr.anglecos * 0.2f};
		if (plr.key.d)
			plr.mv = (t_move_vec){.x = plr.mv.x - plr.anglesin * 0.2f,
						 			.y = plr.mv.y + plr.anglecos * 0.2f};
		plr.pushing = plr.key.w || plr.key.s || plr.key.a || plr.key.d;
		plr.aclrt = plr.pushing ? 0.4 : 0.2;
		plr.vlct.x = plr.vlct.x * (1 - plr.aclrt) + plr.mv.x * plr.aclrt;
		plr.vlct.y = plr.vlct.y * (1 - plr.aclrt) + plr.mv.y * plr.aclrt;
		if (plr.pushing)
			plr.moving = 1;
		SDL_Delay(10);
	}
}
/* IBOHUN (& somebody else) PART 2 END */
