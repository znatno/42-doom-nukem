#ifndef DOOM_NUKEM_SDL1_H
#define DOOM_NUKEM_SDL1_H

/* Strange Includes Start */
#include "SDL_main.h"
#include "SDL_stdinc.h"
#include "SDL_audio.h"
#include "SDL_cpuinfo.h"
#include "SDL_endian.h"
#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_loadso.h"
#include "SDL_mutex.h"
#include "SDL_rwops.h"
#include "SDL_thread.h"
#include "SDL_timer.h"
#include "SDL_video.h"
#include "SDL_version.h"
/* End */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "SDL.h"
#include "libft.h"
/* Define window size */
#define W 608
#define H 320
#define Yaw(y, z) (y + z*player.yaw)
#define MaxQue	32
#define EyeHeight  6    // Camera height from floor when standing
#define DuckHeight 2.5  // And when crouching
#define HeadMargin 1    // How much room there is above camera before the head hits the ceiling
#define KneeHeight 2    // How tall obstacles the player can simply walk over without jumping
#define hfov (0.73f*H)  // Affects the horizontal field of vision
#define vfov (.2f*H)    // Affects the vertical field of vision

/* Sectors: Floor and ceiling height; list of edge vertices and neighbors */
static struct sector
{
	float floor, ceil;
	struct xy
	{
		float x, y;
	} *vertex; // Each vertex has an x and y coordinate
	signed char *neighbors;           // Each edge may have a corresponding neighboring sector
	unsigned npoints;                 // How many vertexes there are
} *sectors = NULL;

static unsigned NumSectors = 0;

//Coordinates
typedef struct	s_xyz1
{
	float	x;
	float	y;
	float	z;
}				t_xyz1;


typedef struct	s_xy1
{
	float	x;
	float	y;
}				t_xy1;

// Player: location
typedef struct	s_player1
{
	t_xyz1		where;		// Current position
	t_xyz1		velocity;	// Current motion vector
	float		angle;
	float		anglesin;
	float		anglecos;
	float		yaw;		// Looking towards (and sin() and cos() thereof)
	unsigned	sector;		// Which sector the player is currently in
}				t_player1;

/* Player: location */
struct player
{
	struct xyz
	{
		float x, y, z;
	}	where,      // Current position
			velocity;   // Current motion vector

	float 	angle;
	float	anglesin;
	float	anglecos, yaw;   // Looking towards (and sin() and cos() thereof)
	unsigned sector;         // Which sector the player is currently in
} player;

// Utility functions. Because C doesn't have templates,
// we use the slightly less safe preprocessor macros to
// implement these functions that work with multiple types.
#define min(a, b)             (((a) < (b)) ? (a) : (b)) // min: Choose smaller of two scalars.
#define max(a, b)             (((a) > (b)) ? (a) : (b)) // max: Choose greater of two scalars.
#define clamp(a, mi, ma)      min(max(a,mi),ma)         // clamp: Clamp value into set range.
#define vxs(x0, y0, x1, y1)    ((x0)*(y1) - (x1)*(y0))   // vxs: Vector cross product
// Overlap:  Determine whether the two number ranges overlap.
#define Overlap(a0, a1, b0, b1) (min(a0,a1) <= max(b0,b1) && min(b0,b1) <= max(a0,a1))
// IntersectBox: Determine whether two 2D-boxes intersect.
#define IntersectBox(x0, y0, x1, y1, x2, y2, x3, y3) (Overlap(x0,x1,x2,x3) && Overlap(y0,y1,y2,y3))
// PointSide: Determine which side of a line the point is on. Return value: <0, =0 or >0.
#define PointSide(px, py, x0, y0, x1, y1) vxs((x1)-(x0), (y1)-(y0), (px)-(x0), (py)-(y0))
// Intersect: Calculate the point of intersection between two lines.
#define Intersect(x1, y1, x2, y2, x3, y3, x4, y4) ((struct xy) { \
    vxs(vxs(x1,y1, x2,y2), (x1)-(x2), vxs(x3,y3, x4,y4), (x3)-(x4)) \
    / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)), \
    vxs(vxs(x1,y1, x2,y2), (y1)-(y2), vxs(x3,y3, x4,y4), (y3)-(y4)) \
    / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4))}) \


static SDL_Surface *surface = NULL;

typedef struct	s_tmp_iter
{
	int 		start_do;
	int 		x;
	unsigned 	s;
}				t_tmp_iter;

typedef struct	s_calc_tmp_float
{
	float vx1;
	float vx2;
	float vy1;
	float vy2;
	float pcos;
	float psin;
	float tx1;
	float tx2;
	float tz1;
	float tz2;
	float nearz;
	float farz;
	float nearside;
	float farside;
	float xscale1;
	float xscale2;
	float yscale1;
	float yscale2;
	float yceil;
	float yfloor;
	float nyceil;
	float nyfloor;
}				t_calc_tmp_float;

typedef struct	s_calc_tmp_int
{
	int 		y_top[W];
	int 		y_bottom[W];
	int 		*renderedsectors;
	int 		x1;
	int 		x2;
	int 		neightbor;
	int 		y1a;
	int 		y1b;
	int 		y2a;
	int 		y2b;
	int 		ny1a;
	int 		ny1b;
	int 		ny2a;
	int 		ny2b;
	int 		beginx;
	int 		endx;
	int 		z;
	int 		ya;
	int 		cya;
	int 		yb;
	int 		cyb;
	int 		nya;
	int 		cnya;
	int 		nyb;
	int 		cnyb;
	unsigned	r1;
	unsigned 	r2;
	unsigned	r;
}				t_calc_tmp_int;


typedef struct	s_item
{
	int sectorno;
	int sx1;
	int sx2;
}				t_item;

typedef struct		s_calc_tmp_struct
{
	t_item				now;
	const struct sector *sect;
	struct sector		*sectors;
	struct xy			i1;
	struct xy			i2;
	t_item				*head;
	t_item				*tail;
	struct sector		*sectore;
}					t_cacl_tmp_struct;

typedef struct		s_draw_sreen_calc
{
	t_calc_tmp_int		*i;
	t_calc_tmp_float	*f;
	t_cacl_tmp_struct	*s;
	t_tmp_iter			*it;
	t_item				*que;
}					t_draw_screen_calc;




#define SEC_COLOR 0x0000ff00
#define BLACK_COLOR 0x00

void	draw_screen();
void	vline(int x, int y1, int y2, int color);

#endif
