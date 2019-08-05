#include <AppleTextureEncoder.h>
#include "sdl1.h"

/* VOPOLONC PART START */
/* Define various vision related constants */

static void LoadData(t_player *plr, t_sector **sectors)
{
	FILE *fp = fopen("map-clear.txt", "rt");
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
				*sectors = realloc(*sectors, ++plr->NumSectors * sizeof
				(**sectors));
				t_sector *sect;
				sect = &(*sectors)[plr->NumSectors - 1];
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
						angle, 0, 0, 0, n, plr->NumSectors};
				// T0D0: Range checking
				plr->where.z = sectors[plr->sector]->floor + EyeHeight;
		}
	fclose(fp);
	free(vert);
}

static void UnloadData(t_sector **sectors, t_player *plr)
{
	for (unsigned a = 0; a < plr->NumSectors; ++a)
		free((*sectors)[a].vertex);
	for (unsigned a = 0; a < plr->NumSectors; ++a)
		free((*sectors)[a].neighbors);
	free(*sectors);
	*sectors = NULL;
	plr->NumSectors = 0;
}
/* VOPOLONC PART END */

/* IBOHUN PART 1 START */
/* vline: Draw a vertical line on screen, with a different color pixel in top & bottom */
static void vline(int x, int y1, int y2, int color)
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

/* GGAVRYLY PART START */
static void DrawScreen(t_player *plr, t_sector **sectors)
{
	enum
	{
		MaxQueue = 32
	};  // maximum number of pending portal renders

	struct item
	{
		int sectorno, sx1, sx2;
	} queue[MaxQueue], *head = queue, *tail = queue;

	int ytop[W] = {0}, ybottom[W], renderedsectors[plr->NumSectors];

	for (unsigned x = 0; x < W; ++x)
		ybottom[x] = H - 1;
	for (unsigned n = 0; n < plr->NumSectors; ++n)
		renderedsectors[n] = 0;

	/* Begin whole-screen rendering from where the player is. */
	*head = (struct item) {plr->sector, 0, W - 1};
	if (++head == queue + MaxQueue) head = queue;

	do
	{
		/* Pick a sector & slice from the queue to draw */
		const struct item now = *tail;
		if (++tail == queue + MaxQueue) tail = queue;

		if ((unsigned)renderedsectors[now.sectorno] & 0x21u)
			continue; // Odd = still rendering, 0x20 = give up
		++renderedsectors[now.sectorno];


		t_sector *sect;

		sect = &(*sectors)[now.sectorno];


		/* Render each wall of this sector that is facing towards player. */
		for (unsigned s = 0; s < sect->npoints; ++s)
		{
			/* Acquire the x,y coordinates of the two endpoints (vertices) of this edge of the sector */
			float vx1 = sect->vertex[s + 0].x - plr->where.x, vy1 =
					sect->vertex[s + 0].y - plr->where.y;
			float vx2 = sect->vertex[s + 1].x - plr->where.x, vy2 =
					sect->vertex[s + 1].y - plr->where.y;
			/* Rotate them around the plr's view */
			float pcos = plr->anglecos, psin = plr->anglesin;
			float tx1 = vx1 * psin - vy1 * pcos, tz1 = vx1 * pcos + vy1 * psin;
			float tx2 = vx2 * psin - vy2 * pcos, tz2 = vx2 * pcos + vy2 * psin;
			/* Is the wall at least partially in front of the player? */
			if (tz1 <= 0 && tz2 <= 0) continue;
			/* If it's partially behind the player, clip it against player's view frustrum */
			if (tz1 <= 0 || tz2 <= 0)
			{
				float nearz = 1e-4f, farz = 5, nearside = 1e-5f, farside = 20.f;
				// Find an intersection between the wall and the approximate edges of player's view
				struct s_xy i1 = Intersect(tx1, tz1, tx2, tz2, -nearside,
						nearz, -farside, farz);
				struct s_xy i2 = Intersect(tx1, tz1, tx2, tz2, nearside,
						nearz, farside, farz);
				if (tz1 < nearz)
				{
					if (i1.y > 0)
					{
						tx1 = i1.x;
						tz1 = i1.y;
					}
					else
					{
						tx1 = i2.x;
						tz1 = i2.y;
					}
				}
				if (tz2 < nearz)
				{
					if (i1.y > 0)
					{
						tx2 = i1.x;
						tz2 = i1.y;
					}
					else
					{
						tx2 = i2.x;
						tz2 = i2.y;
					}
				}
			}
			/* Do perspective transformation */
			float xscale1 = hfov / tz1, yscale1 = vfov / tz1;
			int x1 = W / 2 - (int) (tx1 * xscale1);
			float xscale2 = hfov / tz2, yscale2 = vfov / tz2;
			int x2 = W / 2 - (int) (tx2 * xscale2);
			if (x1 >= x2 || x2 < now.sx1 || x1 > now.sx2)
				continue; // Only render if it's visible
			/* Acquire the floor and ceiling heights, relative to where the player's view is */
			float yceil = sect->ceil - plr->where.z;
			float yfloor = sect->floor - plr->where.z;
			/* Check the edge type. neighbor=-1 means wall, other=boundary between two sectors. */
			int neighbor = sect->neighbors[s];
			float nyceil = 0, nyfloor = 0;
			if (neighbor >= 0) // Is another sector showing through this portal?
			{
				nyceil = (*sectors)[neighbor].ceil - plr->where.z;
				nyfloor = (*sectors)[neighbor].floor - plr->where.z;
			}
			/* Project our ceiling & floor heights into screen coordinates (Y coordinate) */
#define Yaw(y, z) (y + z*plr->yaw)
			int y1a = H / 2 - (int) (Yaw(yceil, tz1) * yscale1), y1b =
					H / 2 - (int) (Yaw(yfloor, tz1) * yscale1);
			int y2a = H / 2 - (int) (Yaw(yceil, tz2) * yscale2), y2b =
					H / 2 - (int) (Yaw(yfloor, tz2) * yscale2);
			/* The same for the neighboring sector */
			int ny1a = H / 2 - (int) (Yaw(nyceil, tz1) * yscale1), ny1b =
					H / 2 - (int) (Yaw(nyfloor, tz1) * yscale1);
			int ny2a = H / 2 - (int) (Yaw(nyceil, tz2) * yscale2), ny2b =
					H / 2 - (int) (Yaw(nyfloor, tz2) * yscale2);

			/* Render the wall. */
			int beginx = max(x1, now.sx1), endx = min(x2, now.sx2);
			for (int x = beginx; x <= endx; ++x)
			{
				/* Calculate the Z coordinate for this point. (Only used for lighting.) */
				int z = (int)(((x - x1) * (tz2 - tz1) / (x2 - x1) + tz1) * 8);
				/* Acquire the Y coordinates for our ceiling & floor for this X coordinate. Clamp them. */
				int ya = (x - x1) * (y2a - y1a) / (x2 - x1) + y1a, cya = clamp(
						ya, ytop[x], ybottom[x]); // top
				int yb = (x - x1) * (y2b - y1b) / (x2 - x1) + y1b, cyb = clamp(
						yb, ytop[x], ybottom[x]); // bottom

				/* Render ceiling: everything above this sector's ceiling height. */
				vline(x, ytop[x], cya - 1, 0x222222);
				/* Render floor: everything below this sector's floor height. */
				vline(x, cyb + 1, ybottom[x], 0x0000AA);

				/* Is there another sector behind this edge? */
				if (neighbor >= 0)
				{
					/* Same for _their_ floor and ceiling */
					int nya = (x - x1) * (ny2a - ny1a) / (x2 - x1) +
							  ny1a, cnya = clamp(nya, ytop[x], ybottom[x]);
					int nyb = (x - x1) * (ny2b - ny1b) / (x2 - x1) +
							  ny1b, cnyb = clamp(nyb, ytop[x], ybottom[x]);
					/* If our ceiling is higher than their ceiling, render upper wall */
					unsigned r1 = 0x010101 * (255 - z), r2 =
							0x040007 * (31 - z / 8);
					vline(x, cya, cnya - 1, x == x1 || x == x2 ? SEC_COLOR : r1); //
					// Between our and their ceiling
					ytop[x] = clamp(max(cya, cnya), ytop[x], H -
															 1);   // Shrink the remaining window below these ceilings
					/* If our floor is lower than their floor, render bottom wall */
					vline(x, cnyb + 1, cyb, x == x1 || x == x2 ? SEC_COLOR : r2); // Between their and our floor
					ybottom[x] = clamp(min(cyb, cnyb), 0,
									   ybottom[x]); // Shrink the remaining window above these floors
				} else
				{
					/* There's no neighbor. Render wall from top (cya = ceiling level) to bottom (cyb = floor level). */
					unsigned r = 0x010101 * (255 - z);
					vline(x, cya, cyb, x == x1 || x == x2 ? SEC_COLOR : r);
				}
			}
			/* Schedule the neighboring sector for rendering within the window formed by this wall. */
			if (neighbor >= 0 && endx >= beginx &&
				(head + MaxQueue + 1 - tail) % MaxQueue)
			{
				*head = (struct item) {neighbor, beginx, endx};
				if (++head == queue + MaxQueue) head = queue;
			}
		} // for s in sector's edges
		++renderedsectors[now.sectorno];
	} while (head != tail); // render any other queued sectors
}
/* GGAVRYLY PART END */

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
	return (0);
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
	switch (ev.type)
	{
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			switch (ev.key.keysym.sym)
			{
				case 'w':
					plr->key.w = ev.type == SDL_KEYDOWN;
					break;
				case 's':
					plr->key.s = ev.type == SDL_KEYDOWN;
					break;
				case 'a':
					plr->key.a = ev.type == SDL_KEYDOWN;
					break;
				case 'd':
					plr->key.d = ev.type == SDL_KEYDOWN;
					break;
				case 'q':
					exit_doom(sectors, plr);
					exit(0);
				case ' ': /* jump */
					if (plr->ground)
					{
						plr->vlct.z += 0.5;
						plr->falling = 1;
					}
					break;
				case SDLK_LCTRL: /* duck */
				case SDLK_RCTRL:
					plr->ducking = ev.type == SDL_KEYDOWN;
					plr->falling = 1;
					break;
				default:
					break;
			}
			break;
		case SDL_QUIT:
			exit_doom(sectors, plr);
			exit(0);
	}
}

int 		main()
{
	t_player	plr;
	t_sector	*sectors;


	sectors = NULL;
	plr.NumSectors = 0;
	plr = (t_player){ .ground = 0, .falling = 1, .moving = 0, .ducking = 0 };
	plr.key = (t_keys){ .w = 0, .s = 0, .a = 0, .d = 0 };

	LoadData(&plr, &sectors);

	surface = SDL_SetVideoMode(W, H, 32, 0);

	SDL_EnableKeyRepeat(150, 30);
	SDL_ShowCursor(SDL_DISABLE);

	//plr.ground = 0, plr.falling = 1, plr.moving = 0, plr.ducking = 0;

	float yaw;
	yaw = 0;

	while (1)
	{
		SDL_LockSurface(surface);
		DrawScreen(&plr, &sectors);
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
		int x;
		int y;

		SDL_GetRelativeMouseState(&x, &y);
		plr.angle += x * 0.03f;
		yaw = clamp(yaw - y * 0.05f, -5, 5);
		plr.yaw = yaw - plr.vlct.z * 0.5f;
		MovePlayer(&plr, &sectors, 0, 0);


		plr.mv = (t_move_vec){ .x = 0.f, .y = 0.f};
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
