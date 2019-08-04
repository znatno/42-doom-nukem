#include "sdl1.h"

/* VOPOLONC PART START */
/* Define various vision related constants */

static void LoadData()
{
	FILE *fp = fopen("map-clear.txt", "rt");
	if (!fp)
	{
		perror("map-clear.txt");
		exit(1);
	}
	char Buf[256], word[256], *ptr;
	struct xy *vert = NULL, v;
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
				sectors = realloc(sectors, ++NumSectors * sizeof(*sectors));
				struct sector *sect = &sectors[NumSectors - 1];
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
				sect->vertex[0] = sect->vertex[m]; // Ensure the vertexes form a loop
				free(num);
				break;
			case 'p':; // player
				float angle;
				sscanf(ptr += n, "%f %f %f %d", &v.x, &v.y, &angle, &n);
				player = (struct player) {{v.x, v.y, 0}, {0, 0, 0}, angle, 0, 0,
										  0, n}; // T0D0: Range checking
				player.where.z = sectors[player.sector].floor + EyeHeight;
		}
	fclose(fp);
	free(vert);
}

static void UnloadData()
{
	for (unsigned a = 0; a < NumSectors; ++a) free(sectors[a].vertex);
	for (unsigned a = 0; a < NumSectors; ++a) free(sectors[a].neighbors);
	free(sectors);
	sectors = NULL;
	NumSectors = 0;
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
		pix[y1 * W + x] = BLACK_COLOR; //верхня і нижня межа екрану
	else if (y2 > y1)
	{
		pix[y1 * W + x] = SEC_COLOR; //проміжок секторів
		for (int y = y1 + 1; y < y2; ++y) pix[y * W + x] = color;
		pix[y2 * W + x] = color;
	}
}

/* MovePlayer(dx,dy): Moves the player by (dx,dy) in the map, and
 * also updates their anglesin/anglecos/sector properties properly.
 */
static void MovePlayer(float dx, float dy)
{
	float px = player.where.x, py = player.where.y;
	/* Check if this movement crosses one of this sector's edges
	 * that have a neighboring sector on the other side.
	 * Because the edge vertices of each sector are defined in
	 * clockwise order, PointSide will always return -1 for a point
	 * that is outside the sector and 0 or 1 for a point that is inside.
	 */
	const struct sector *const sect = &sectors[player.sector];
	const struct xy *const vert = sect->vertex;
	for (unsigned s = 0; s < sect->npoints; ++s)
		if (sect->neighbors[s] >= 0
			&&
			IntersectBox(px, py, px + dx, py + dy, vert[s + 0].x, vert[s + 0].y,
						 vert[s + 1].x, vert[s + 1].y)
			&& PointSide(px + dx, py + dy, vert[s + 0].x, vert[s + 0].y,
						 vert[s + 1].x, vert[s + 1].y) < 0)
		{
			player.sector = sect->neighbors[s];
			break;
		}

	player.where.x += dx;
	player.where.y += dy;
	player.anglesin = sinf(player.angle);
	player.anglecos = cosf(player.angle);
}
/* IBOHUN PART 1 END */
/* IBOHUN (& somebody else) PART 2 START */
int main()
{
	LoadData();

	surface = SDL_SetVideoMode(W, H, 32, 0);

	SDL_EnableKeyRepeat(150, 30);
	SDL_ShowCursor(SDL_DISABLE);

	int wsad[4] = {0, 0, 0, 0}, \
	ground = 0, falling = 1, moving = 0, ducking = 0;

	float yaw = 0;
	for (;;)
	{
		SDL_LockSurface(surface);
		draw_screen(sectors, NumSectors);
		SDL_UnlockSurface(surface);
		SDL_Flip(surface);

		/* Vertical collision detection */
		float eyeheight = ducking ? DuckHeight : EyeHeight;
		ground = !falling;
		if (falling)
		{
			player.velocity.z -= 0.05f; /* Add gravity */
			float nextz = player.where.z + player.velocity.z;
			if (player.velocity.z < 0 && nextz < sectors[player.sector].floor +
												 eyeheight) // When going down
			{
				/* Fix to ground */
				player.where.z = sectors[player.sector].floor + eyeheight;
				player.velocity.z = 0;
				falling = 0;
				ground = 1;
			} else if (player.velocity.z > 0 &&
					   nextz > sectors[player.sector].ceil) // When going up
			{
				/* Prevent jumping above ceiling */
				player.velocity.z = 0;
				falling = 1;
			}
			if (falling)
			{
				player.where.z += player.velocity.z;
				moving = 1;
			}
		}
		/* Horizontal collision detection */
		if (moving)
		{
			float px = player.where.x, py = player.where.y;
			float dx = player.velocity.x, dy = player.velocity.y;

			const struct sector *const sect = &sectors[player.sector];
			const struct xy *const vert = sect->vertex;
			/* Check if the player is about to cross one of the sector's edges */
			for (unsigned s = 0; s < sect->npoints; ++s)
				if (IntersectBox(px, py, px + dx, py + dy, vert[s + 0].x,
								 vert[s + 0].y, vert[s + 1].x, vert[s + 1].y)
					&& PointSide(px + dx, py + dy, vert[s + 0].x, vert[s + 0].y,
								 vert[s + 1].x, vert[s + 1].y) < 0)
				{
					/* Check where the hole is. */
					float hole_low =
							sect->neighbors[s] < 0 ? 9e9 : max(sect->floor,
															   sectors[sect->neighbors[s]].floor);
					float hole_high =
							sect->neighbors[s] < 0 ? -9e9 : min(sect->ceil,
																sectors[sect->neighbors[s]].ceil);
					/* Check whether we're bumping into a wall. */
					if (hole_high < player.where.z + HeadMargin
						|| hole_low > player.where.z - eyeheight + KneeHeight)
					{
						/* Bumps into a wall! Slide along the wall. */
						/* This formula is from Wikipedia article "vector projection". */
						float xd = vert[s + 1].x - vert[s + 0].x, yd =
								vert[s + 1].y - vert[s + 0].y;
						dx = xd * (dx * xd + yd * dy) / (xd * xd + yd * yd);
						dy = yd * (dx * xd + yd * dy) / (xd * xd + yd * yd);
						moving = 0;
					}
				}
			MovePlayer(dx, dy);
			falling = 1;
		}

		SDL_Event ev;
		while (SDL_PollEvent(&ev))
			switch (ev.type)
			{
				case SDL_KEYDOWN:
				case SDL_KEYUP:
					switch (ev.key.keysym.sym)
					{
						case 'w':
							wsad[0] = ev.type == SDL_KEYDOWN;
							break;
						case 's':
							wsad[1] = ev.type == SDL_KEYDOWN;
							break;
						case 'a':
							wsad[2] = ev.type == SDL_KEYDOWN;
							break;
						case 'd':
							wsad[3] = ev.type == SDL_KEYDOWN;
							break;
						case 'q':
							goto done;
						case ' ': /* jump */
							if (ground)
							{
								player.velocity.z += 0.5;
								falling = 1;
							}
							break;
						case SDLK_LCTRL: /* duck */
						case SDLK_RCTRL:
							ducking = ev.type == SDL_KEYDOWN;
							falling = 1;
							break;
						default:
							break;
					}
					break;
				case SDL_QUIT:
					goto done;
			}

		/* mouse aiming */
		int x, y;
		SDL_GetRelativeMouseState(&x, &y);
		player.angle += x * 0.03f;
		yaw = clamp(yaw - y * 0.05f, -5, 5);
		player.yaw = yaw - player.velocity.z * 0.5f;
		MovePlayer(0, 0);

		float move_vec[2] = {0.f, 0.f};
		if (wsad[0])
		{
			move_vec[0] += player.anglecos * 0.2f;
			move_vec[1] += player.anglesin * 0.2f;
		}
		if (wsad[1])
		{
			move_vec[0] -= player.anglecos * 0.2f;
			move_vec[1] -= player.anglesin * 0.2f;
		}
		if (wsad[2])
		{
			move_vec[0] += player.anglesin * 0.2f;
			move_vec[1] -= player.anglecos * 0.2f;
		}
		if (wsad[3])
		{
			move_vec[0] -= player.anglesin * 0.2f;
			move_vec[1] += player.anglecos * 0.2f;
		}
		int pushing = wsad[0] || wsad[1] || wsad[2] || wsad[3];
		float acceleration = pushing ? 0.4 : 0.2;

		player.velocity.x = player.velocity.x * (1 - acceleration) +
							move_vec[0] * acceleration;
		player.velocity.y = player.velocity.y * (1 - acceleration) +
							move_vec[1] * acceleration;

		if (pushing) moving = 1;

		SDL_Delay(10);
	}
	done:
	UnloadData();
	SDL_Quit();
	return 0;
}
/* IBOHUN (& somebody else) PART 2 END */