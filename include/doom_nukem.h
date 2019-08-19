/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibohun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 19:21:08 by ggavryly          #+#    #+#             */
/*   Updated: 2019/08/19 19:25:10 by ibohun           ###   ########.fr       */
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
# include <time.h>
# include <sys/wait.h>
# include "libft.h"
# include "SDL.h"
# include "SDL_mixer.h"
# include "SDL_image.h"
# include "SDL_ttf.h"

/* Define window size */
#define W 640
#define H 480

#define YAW(y, z) (y + z * plr.yaw) // Y-axis angle of player camera
#define MAX_QUE	32			// max num of sectors what will be rendered
#define EYE_H  6		// Camera height from floor when standing
#define DUCK_H 2.5		// And when crouching
#define HEAD_MARGIN 1		// How much room there is above camera before the head hits the ceiling
#define KNEE_H 2		// How tall obstacles the player can simply walk over without jumping
#define HFOV (0.73f * H)	// Affects the horizontal field of vision
#define VFOV (.2f * H)		// Affects the vertical field of vision
#define ISDIGIT(c) (c >= '0' && c <= '9')
#define SEC_COLOR	0x0000ff00
#define BLACK_COLOR	0x00
#define FILE_NAME "../test.txt"
#define GET_ANGLE_V0_V1(xy0, xy1) (radian_to_grades(acosf(angle_vv(scalar_product(xy0, xy1), len_vector(xy0), len_vector(xy1)))))

//	Utility functions. Because C doesn't have templates,
//	we use the slightly less safe preprocessor macros to
//	implement these functions that work with multiple types.
//	TODO: DELETE ALL OF THESE — MAKE FUNCTIONS

#define MIN(a, b)             (((a) < (b)) ? (a) : (b))		// min: Choose smaller of two scalars.
#define MAX(a, b)             (((a) > (b)) ? (a) : (b))		// max: Choose greater of two scalars.

// мінімальне з {"ma", максимальне з {a, mi}}
#define CLAMP(a, mi, ma)      MIN(MAX(a,mi),ma)				// clamp: Clamp
// value into set range.x

// Векторний добуток
#define VXS(x0, y0, x1, y1)   ((x0)*(y1) - (x1)*(y0))		// vxs: Vector cross product

//	Overlap:  Determine whether the two number ranges overlap.
//	Overlap(a0, a1, b0, b1) (min(a0,a1) <= max(b0,b1) && min(b0,b1) <= max(a0,a1))

#define MAX_MSGS 100

typedef enum	e_fonts
{
	FONT_M_SM = 0,
	FONT_M_MD,
	FONT_M_BG,
	FONT_S_SM,
	FONT_S_MD,
	FONT_S_BG,
	FONTS_NUM
}				t_fonts;

//Coordinates
typedef struct	s_xyz
{
	float	x;
	float	y;
	float	z;
}				t_xyz;

typedef struct s_posf_t
{
	int     pos;
	bool    is_y;
	float   value;
	float   y;
}				t_posf;


typedef struct	s_xy
{
	float	x;
	float	y;
}				t_xy;

typedef struct	s_xy_i
{
	int			x;
	int			y;
}				t_xy_i;

/* Sectors: Floor and ceiling height; list of edge vertices and neighbors */
typedef struct		s_sector
{
	float			floor;
	float			ceil;
	t_xy			*vertex;
	int				*neighbors;       // Each edge may have a corresponding neighboring sector
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
	//SDL_DisplayMode		display_mode;
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Surface			*w_surface;

	SDL_Texture			*texture;
	int					*buffer;
}						t_sdl_main;

// Player: location
typedef struct		s_player
{
	t_xyz			where;		// Current position
	t_xyz			vlct;		// velocity, curr motion vector / швидкість
	float			angle;		// камера по X-осі, yaw — по Y-осі
	float			anglesin;
	float			anglecos;
	float			yaw;		// Looking towards (and sin() and cos() thereof)
	unsigned		sector;		// Which sector the player is currently in
	unsigned int	num_scts;	// Number of Sectors
	bool			ground;
	bool			falling;
	bool			moving;
	bool			ducking;	// присяд
	bool 			run;		// пришвидшення
	bool 			fly;		// політ
	float			eyeheight;
	t_keys			key;		// WASD провірка натиску клавіш
	t_move_vec		mv;			// вектор руху
	float 			speed;		// швидкість, менша для присяду, todo більша shift
	int 			pushing;
	float			aclrt;		// acceleration / прискорення
	t_xy_i			ms;			// mouse aiming
	float 			ms_yaw;
	t_sdl_main		*sdl;

	bool			draw_look; // для перегляду відмальовування полінійно
}					t_player;

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
	t_sector			*sector;
}					t_calc_tmp_struct;

typedef struct		s_draw_screen_calc
{
	t_calc_tmp_int		*i;
	t_calc_tmp_float	*f;
	t_calc_tmp_struct	*s;
	t_tmp_iter			*it;
	t_item				*que;
}					t_draw_screen_calc;

typedef struct		s_font
{
	TTF_Font		*ttf;
	char 			*name;
	int 			size;
	SDL_Color		color;
}					t_font;

typedef struct		s_msg
{
	char			*text;
	uint8_t 		font_num;
	t_xy_i			pos;
	double			seconds;
	double 			start_t;
}					t_msg;

typedef struct		s_game
{
	t_player	plr;
	t_sdl_main	sdl;
	t_sector	*sectors;
	t_font		fonts[FONTS_NUM];
	t_msg		msgs[MAX_MSGS];

	int			error;		// для виводу тексту помилки при виході

	int			tmp; //todo delete
}					t_game;


/*
** Initialize functions
*/

void			init_sdl(t_sdl_main *sdl);
void 			load_data(t_player *player, t_sector **sectors);
char			*ft_itof(long double k);

/*
** Draw functions
*/

void			draw_screen(t_sector *sector, t_player plr);
void			vline(int x, int y1, int y2, int color, t_player *player);
t_xy			vv_to_v(float x0, float y0, float x1, float y1);
float			len_vector(t_xy		free_vector);
float			scalar_product(t_xy xy0, t_xy xy1);
float			angle_vv(float scalar_product, float len0, float len1);
float			radian_to_grades(float rad);
float			vector_product(t_xy xy0, t_xy xy1);
int				move_or_not(t_xyz where ,t_sector sector, unsigned sect_num);

/*
**  "math_fts.c" Math functions for vectors and other things
**	Define various vision related constants
*/

bool 			overlap(float a0, float a1, float b0, float b1);

bool 			intersect_box(float x0, float y0, float x1, float y1,
							  float x2, float y2, float x3, float y3);

t_xy 			intersect(float x1, float y1, float x2, float y2, float x3,
						  float y3, float x4, float y4);

float			point_side(float px, float py, float x0, float y0,
							float x1, float y1);

/*
**  "move.c"
*/

void			move_player(t_player *plr, t_sector **sectors,
							float dx, float dy);

void			check_move(t_player *plr, t_sector **sc);
void			check_fall(t_player *plr, t_sector **sectors);

/*
**	Quit
*/

int				exit_doom(t_game *g);


/*
** Font and text functions
*/

void			load_fonts(t_game *g);
void			init_msgs(t_game *g);
void			show_msg(t_game *g, t_msg m, t_font font);
void			get_messages(t_game *g);
t_msg			create_msg(char *text, uint8_t fontname, t_xy_i pos, int sec);


#endif
