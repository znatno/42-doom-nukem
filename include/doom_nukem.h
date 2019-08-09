/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom-nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 19:21:08 by ggavryly          #+#    #+#             */
/*   Updated: 2019/07/31 19:21:09 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# include <unistd.h>
# include <errno.h>
# include <math.h>
# include <pthread.h>
# include <stdio.h>
# include <stdbool.h>
# include "libft.h"
# include "SDL.h"
# include "SDL_mixer.h"
# include "SDL_image.h"

/* Define window size */
#define W 640
#define H 480
#define Yaw(y, z) (y + z * plr.yaw)
#define MaxQue	32
#define EyeHeight  6    // Camera height from floor when standing
#define DuckHeight 2.5  // And when crouching
#define HeadMargin 1    // How much room there is above camera before the head hits the ceiling
#define KneeHeight 2    // How tall obstacles the player can simply walk over without jumping
#define hfov (0.73f * H)  // Affects the horizontal field of vision
#define vfov (.2f * H)    // Affects the vertical field of vision
#define isdigit(c) (c >= '0' && c <= '9')
#define SEC_COLOR 0x0000ff00
#define BLACK_COLOR 0x00
#define FILE_NAME "map-clear.txt"

//Coordinates
typedef struct	s_xyz
{
	float	x;
	float	y;
	float	z;
}				t_xyz;

typedef struct s_posf_t {
	int     pos;
	bool    is_y;
	float   value;
	float   y;
}				t_posf;


typedef struct	s_xy1
{
	float	x;
	float	y;
}				t_xy;

typedef struct	s_xy_i
{
	int			x;
	int			y;
	float 		yaw;
}				t_xy_i;

/* Sectors: Floor and ceiling height; list of edge vertices and neighbors */
typedef struct		s_sector
{
	float			floor;
	float			ceil;
	t_xy			*vertex;
	signed char		*neighbors;       // Each edge may have a corresponding neighboring sector
	unsigned		npoints;          // How many vertexes there are
	t_xy		*vert;
}					t_sector;

typedef struct		s_keys
{
	bool			w;
	bool			s;
	bool			a;
	bool			d;
}					t_keys;

typedef struct		s_move_vec
{
	float 			x;
	float 			y;
}					t_move_vec;

typedef struct			s_sdl_main
{
	SDL_DisplayMode		display_mode;
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Surface			*surface;
	SDL_Texture			*texture;
	SDL_Rect			src_rect;
	SDL_Rect			dst_rect;
	int					*buffer;
}						t_sdl_main;

// Player: location
typedef struct		s_player
{
	t_xyz			where;		// Current position
	t_xyz			vlct;		// velocity, Current motion vector
	float			angle;
	float			anglesin;
	float			anglecos;
	float			yaw;		// Looking towards (and sin() and cos() thereof)
	unsigned		sector;		// Which sector the player is currently in
	unsigned int	num_scts;	// Number of Sectors
	int				ground;
	int				falling;
	int				moving;
	int				ducking;
	float			eyeheight;
	t_keys			key;
	t_move_vec		mv;
	float 			speed;
	int 			pushing;
	float			aclrt;		// acceleration
	t_xy_i			ms;			// mouse aiming
	t_sdl_main		*sdl;
}					t_player;

// Utility functions. Because C doesn't have templates,
// we use the slightly less safe preprocessor macros to
// implement these functions that work with multiple types.
//TODO: DELETE ALL OF THESE — MAKE FUNCTIONS
#define min(a, b)             (((a) < (b)) ? (a) : (b)) // min: Choose smaller of two scalars.
#define max(a, b)             (((a) > (b)) ? (a) : (b)) // max: Choose greater of two scalars.
#define clamp(a, mi, ma)      min(max(a,mi),ma)         // clamp: Clamp value into set range.
#define vxs(x0, y0, x1, y1)    ((x0)*(y1) - (x1)*(y0))   // vxs: Vector cross product
// Overlap:  Determine whether the two number ranges overlap.
//#define Overlap(a0, a1, b0, b1) (min(a0,a1) <= max(b0,b1) && min(b0,b1) <= max(a0,a1))

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
	int			z;
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
	const t_sector 		*sect;
	t_xy				i1;
	t_xy				i2;
	t_item				*head;
	t_item				*tail;
	t_sector			*sectore;
}					t_calc_tmp_struct;

typedef struct		s_draw_sreen_calc
{
	t_calc_tmp_int		*i;
	t_calc_tmp_float	*f;
	t_calc_tmp_struct	*s;
	t_tmp_iter			*it;
	t_item				*que;
}					t_draw_screen_calc;

void		draw_screen(t_sector *sector, t_player plr);
void 		load_data(t_player *player, t_sector **sectors);
char		*ft_itof(long double k);
void		vline(int x, int y1, int y2, int color, t_player *player);
t_xy Intersect(float x1, float y1, float x2, float y2, float x3, float y3,
			   float x4, float y4);
void					init_sdl(t_sdl_main *sdl);
SDL_Texture				*load_texture(char *path, t_sdl_main *sdl);

#endif
