/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 21:38:26 by ggavryly          #+#    #+#             */
/*   Updated: 2019/08/02 21:38:27 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl1.h"

void	draw_screen(struct sector *sectore, unsigned int num_sectors)
{
	t_tmp_iter			t_ti;
	t_item				queue[MaxQue];
	t_calc_tmp_int		t_cti;
	t_calc_tmp_float	t_ctf;
	t_cacl_tmp_struct	t_cts;

	t_cts.head = queue;
	t_cts.tail = queue;
	enum
	{
		MaxQueue = 32
	};  // maximum number of pending portal renders
	int ytop[W] = {0}, ybottom[W], renderedsectors[num_sectors];
	for (unsigned x = 0; x < W; ++x) ybottom[x] = H - 1;
	for (unsigned n = 0; n < num_sectors; ++n) renderedsectors[n] = 0;

	/* Begin whole-screen rendering from where the player is. */
	*t_cts.head = (t_item) { player.sector, 0, W-1 };
	if (++t_cts.head  == queue + MaxQue)
		t_cts.head  = queue;
	do
	{
		/* Pick a sector & slice from the queue to draw */
		t_cts.now = *t_cts.tail;
		if (++t_cts.tail == queue + MaxQue)
			t_cts.tail = queue;
		if (renderedsectors[t_cts.now.sectorno] & 0x21)
			continue; // Odd = still rendering, 0x20 = give up
		++renderedsectors[t_cts.now.sectorno];
		t_cts.sect = &sectore[t_cts.now.sectorno];
		/* Render each wall of this sector that is facing towards player. */
		for (unsigned s = 0; s < t_cts.sect->npoints; ++s)
		{
			/* Acquire the x,y coordinates of the two endpoints (vertices) of this edge of the sector */
			t_ctf.vx1 = t_cts.sect->vertex[s + 0].x - player.where.x;
			t_ctf.vy1 = t_cts.sect->vertex[s + 0].y - player.where.y;

			t_ctf.vx2 = t_cts.sect->vertex[s + 1].x - player.where.x;
			t_ctf.vy2 = t_cts.sect->vertex[s + 1].y - player.where.y;

			/* Rotate them around the player's view */
			t_ctf.pcos = player.anglecos;
			t_ctf.psin = player.anglesin;

			t_ctf.tx1 = t_ctf.vx1 * t_ctf.psin - t_ctf.vy1 * t_ctf.pcos;
			t_ctf.tz1 = t_ctf.vx1 * t_ctf.pcos + t_ctf.vy1 * t_ctf.psin;

			t_ctf.tx2 = t_ctf.vx2 * t_ctf.psin - t_ctf.vy2 * t_ctf.pcos;
			t_ctf.tz2 = t_ctf.vx2 * t_ctf.pcos + t_ctf.vy2 * t_ctf.psin;

			/* Is the wall at least partially in front of the player? */
			if (t_ctf.tz1 <= 0 && t_ctf.tz2 <= 0)
				continue;
			/* If it's partially behind the player, clip it against player's view frustrum */
			if (t_ctf.tz1 <= 0 || t_ctf.tz2 <= 0)
			{
				t_ctf.nearz = 1e-4f;
				t_ctf.farz = 5;
				t_ctf.nearside = 1e-5f;
				t_ctf.farside = 20.f;
				// Find an intersection between the wall and the approximate edges of player's view
				t_cts.i1 = Intersect(t_ctf.tx1, t_ctf.tz1, t_ctf.tx2, t_ctf.tz2, -t_ctf.nearside, t_ctf.nearz,
									 -t_ctf.farside, t_ctf.farz);
				t_cts.i2 = Intersect(t_ctf.tx1, t_ctf.tz1, t_ctf.tx2, t_ctf.tz2, t_ctf.nearside, t_ctf.nearz,
									 t_ctf.farside, t_ctf.farz);

				if (t_ctf.tz1 < t_ctf.nearz)
				{
					if (t_cts.i1.y > 0)
					{
						t_ctf.tx1 = t_cts.i1.x;
						t_ctf.tz1 = t_cts.i1.y;
					} else
					{
						t_ctf.tx1 = t_cts.i2.x;
						t_ctf.tz1 = t_cts.i2.y;
					}
				}
				if (t_ctf.tz2 < t_ctf.nearz)
				{
					if (t_cts.i1.y > 0)
					{
						t_ctf.tx2 = t_cts.i1.x;
						t_ctf.tz2 = t_cts.i1.y;
					} else
					{
						t_ctf.tx2 = t_cts.i2.x;
						t_ctf.tz2 = t_cts.i2.y;
					}
				}
			}
			/* Do perspective transformation */
			t_ctf.xscale1 = hfov / t_ctf.tz1;
			t_ctf.yscale1 = vfov / t_ctf.tz1;

			t_cti.x1 = W / 2 - (int)(t_ctf.tx1 * t_ctf.xscale1);

			t_ctf.xscale2 = hfov / t_ctf.tz2;
			t_ctf.yscale2 = vfov / t_ctf.tz2;

			t_cti.x2 = W / 2 - (int)(t_ctf.tx2 * t_ctf.xscale2);
			if (t_cti.x1 >= t_cti.x2 || t_cti.x2 < t_cts.now.sx1 || t_cti.x1 > t_cts.now.sx2)
				continue; // Only render if it's visible
			/* Acquire the floor and ceiling heights, relative to where the player's view is */
			t_ctf.yceil = t_cts.sect->ceil - player.where.z;
			t_ctf.yfloor = t_cts.sect->floor - player.where.z;
			/* Check the edge type. neighbor=-1 means wall, other=boundary between two sectors. */
			t_cti.neightbor = t_cts.sect->neighbors[s];

			t_ctf.nyceil = 0;
			t_ctf.nyfloor = 0;
			if (t_cti.neightbor >= 0) // Is another sector showing through this portal?
			{
				t_ctf.nyceil = sectore[t_cti.neightbor].ceil - player.where.z;
				t_ctf.nyfloor = sectore[t_cti.neightbor].floor - player.where.z;
			}
			/* Project our ceiling & floor heights into screen coordinates (Y coordinate) */
			t_cti.y1a = H / 2 - (int)(Yaw(t_ctf.yceil, t_ctf.tz1) * t_ctf.yscale1);
			t_cti.y1b = H / 2 - (int)(Yaw(t_ctf.yfloor, t_ctf.tz1) * t_ctf.yscale1);

			t_cti.y2a = H / 2 - (int)(Yaw(t_ctf.yceil, t_ctf.tz2) * t_ctf.yscale2);
			t_cti.y2b = H / 2 - (int)(Yaw(t_ctf.yfloor, t_ctf.tz2) * t_ctf.yscale2);

			/* The same for the neighboring sector */
			t_cti.ny1a = H / 2 - (int)(Yaw(t_ctf.nyceil, t_ctf.tz1) * t_ctf.yscale1);
			t_cti.ny1b = H / 2 - (int)(Yaw(t_ctf.nyfloor, t_ctf.tz1) * t_ctf.yscale1);

			t_cti.ny2a = H / 2 - (int)(Yaw(t_ctf.nyceil, t_ctf.tz2) * t_ctf.yscale2);
			t_cti.ny2b = H / 2 - (int)(Yaw(t_ctf.nyfloor, t_ctf.tz2) * t_ctf.yscale2);

			/* Render the wall. */
			t_cti.beginx = max(t_cti.x1, t_cts.now.sx1);
			t_cti.endx = min(t_cti.x2, t_cts.now.sx2);
			t_ti.x = t_cti.beginx;
			for (int x = t_cti.beginx; x <= t_cti.endx; ++x)
			{
				/* Calculate the Z coordinate for this point. (Only used for lighting.) */
				t_cti.z = ((t_ti.x - t_cti.x1) * (t_ctf.tz2 - t_ctf.tz1) / (t_cti.x2 - t_cti.x1) + t_ctf.tz1);//Maybe delete this?
				/* Acquire the Y coordinates for our ceiling & floor for this X coordinate. Clamp them. */
				t_cti.ya = (t_ti.x - t_cti.x1) * (t_cti.y2a - t_cti.y1a) / (t_cti.x2 - t_cti.x1) + t_cti.y1a;
				t_cti.cya = clamp(t_cti.ya, t_cti.y_top[t_ti.x], t_cti.y_bottom[t_ti.x]); // top

				t_cti.yb = (t_ti.x - t_cti.x1) * (t_cti.y2b - t_cti.y1b) / (t_cti.x2 - t_cti.x1) + t_cti.y1b;
				t_cti.cyb = clamp(t_cti.yb, t_cti.y_top[t_ti.x], t_cti.y_bottom[t_ti.x]); // bottom

				/* Render ceiling: everything above this sector's ceiling height. */
				vline(t_ti.x, t_cti.y_top[t_ti.x], t_cti.cya - 1, 0x111111);
				/* Render floor: everything below this sector's floor height. */
				vline(t_ti.x, t_cti.cyb + 1, t_cti.y_bottom[t_ti.x], 0x0000FF);

				/* Is there another sector behind this edge? */
				if (t_cti.neightbor >= 0)
				{
					/* Same for _their_ floor and ceiling */
					t_cti.nya = (t_ti.x - t_cti.x1) * (t_cti.ny2a - t_cti.ny1a) / (t_cti.x2 - t_cti.x1) + t_cti.ny1a;
					t_cti.cnya = clamp(t_cti.nya, t_cti.y_top[t_ti.x], t_cti.y_bottom[t_ti.x]);

					t_cti.nyb = (t_ti.x - t_cti.x1) * (t_cti.ny2b - t_cti.ny1b) / (t_cti.x2 - t_cti.x1) + t_cti.ny1b;
					t_cti.cnyb = clamp(t_cti.nyb, t_cti.y_top[t_ti.x], t_cti.y_bottom[t_ti.x]);

					/* If our ceiling is higher than their ceiling, render upper wall */
					t_cti.r1 = 0x010101 * (255 - t_cti.z);
					t_cti.r2 = 0x040007 * (31 - t_cti.z / 8);

					vline(t_ti.x, t_cti.cya, t_cti.cnya - 1, (t_ti.x == t_cti.x1 || t_ti.x == t_cti.x2) ? (0) : (t_cti.r1)); // Between our and their ceiling

					t_cti.y_top[t_ti.x] = clamp(max(t_cti.cya, t_cti.cnya), t_cti.y_top[t_ti.x], H - 1); // Shrink the remaining window below these ceilings
					/* If our floor is lower than their floor, render bottom wall */
					vline(t_ti.x, t_cti.cnyb + 1, t_cti.cyb, (t_ti.x == t_cti.x1 || t_ti.x == t_cti.x2) ? (0) : (t_cti.r2)); // Between their and our floor

					t_cti.y_bottom[t_ti.x] = clamp(min(t_cti.cyb, t_cti.cnyb), 0, t_cti.y_bottom[t_ti.x]); // Shrink the remaining window above these floors
				}
				else
				{
					/* There's no neighbor. Render wall from top (cya = ceiling level) to bottom (cyb = floor level). */
					t_cti.r = 0x010101 * (255 - t_cti.z);
					vline(t_ti.x, t_cti.cya, t_cti.cyb, (t_ti.x == t_cti.x1 || t_ti.x == t_cti.x2) ? (0) : (t_cti.r));
				}
				t_ti.x++;
			}
			/* Schedule the neighboring sector for rendering within the window formed by this wall. */
			if (t_cti.neightbor >= 0 && t_cti.endx >= t_cti.beginx && (t_cts.head  + MaxQue + 1 - t_cts.tail) % MaxQue)
			{
				*t_cts.head  = (t_item) {t_cti.neightbor, t_cti.beginx, t_cti.endx};
				if (++t_cts.head  == queue + MaxQue)
					t_cts.head  = queue;
			}
			t_ti.s++;
		} // for s in sector's edges
		++renderedsectors[t_cts.now.sectorno];
	} while (t_cts.head  != t_cts.tail);
}