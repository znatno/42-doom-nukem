/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibohun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 19:21:08 by ggavryly          #+#    #+#             */
/*   Updated: 2019/08/23 19:48:20 by ibohun           ###   ########.fr       */
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
# include "SDL_surface.h"
# include "SDL_pixels.h"

/* Define window size */
#define W 1024
#define H 768
#define X_0 0
#define Y_0 1
#define X_1 2
#define Y_1 3
#define RUN					1
#define JUMP				2
#define LANDING				3
#define SEAT_RUN			4
#define FAST_RUN			5

# define YAW(y, z) (y + z * plr.yaw)	// Y-axis angle of player camera
# define MAX_QUE	32					// max num of sectors what will be rendered
# define EYE_H  6					// Camera height from floor when standing
# define DUCK_H 2.5					// And when crouching
# define HEAD_MARGIN 1				// How much room there is above camera before the head hits the ceiling
# define KNEE_H 2					// How tall obstacles the player can simply walk over without jumping
# define HFOV (0.73f * H)			// Affects the horizontal field of vision
# define VFOV (.2f * H)				// Affects the vertical field of vision
# define H_FOV		(1.0 * 0.73f * H / W) //шось з перспективою
# define V_FOV		(1.0 * .2f)
#define ISDIGIT(c) (c >= '0' && c <= '9')
#define SEC_COLOR	0x0000ff00
#define BLACK_COLOR	0x00
#define FILE_NAME "map-clear.txt"
#define GET_ANGLE_V0_V1(xy0, xy1) (radian_to_grades(acosf(angle_vv(scalar_product(xy0, xy1), len_vector(xy0), len_vector(xy1)))))

#define RED					0
#define GREEN				1
#define TOP_PORTAL_WALL	0
#define BLUE				2
#define BOTTOM_PORTAL_WALL 1
#define CEIL				3
#define FULL_WALL			2
#define FLOOR				4
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

typedef struct	s_tex_i
{
	uint32_t	wall;
	uint32_t	ceil;
	uint32_t	floor;
}				t_tex_i;

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

typedef struct	s_xy_int
{
	int			x;
	int			y;
}				t_xy_int;

typedef struct	s_xy_uint
{
	uint32_t	x;
	uint32_t	y;
}				t_xy_uint;

/* Sectors: Floor and ceiling height; list of edge vertices and neighbors */
typedef struct		s_sector
{
	float			floor;
	float			ceil;
	t_xy			*vertex;
	int				*neighbors;       // Each edge may have a corresponding neighboring sector
	unsigned		npoints;          // How many vertexes there are
	t_xy			*vert;
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

typedef struct		s_textures
{
	SDL_Surface		**arr_tex;
	SDL_Surface		**decor_tex;
	uint32_t 		txt_y;
	uint32_t		txt_x;
	float 			perc_x;
	float 			perc_y;
}					t_textures;


typedef struct			s_sdl_main
{
	//SDL_DisplayMode		display_mode;
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Surface			*win_surface;
	t_textures			*textures;
	SDL_Texture			*texture;
	int					*buffer;
}						t_sdl_main;

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
	float tx1;			//
	float tx2;			//
	float tz1;			// якщо більше-рівне 0, то потрапляє в екран
	float tz2;			// якщо більше-рівне 0, то потрапляє в екран
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
	float perc_light;
	float hei;
	float mapx;
	float mapz;
	float rtx;
	float rtz;
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
	int 		u0;
	int 		u1;
	int 		txtx;
	int 		txty;
	int 		pel;
//	unsigned	r1;
//	unsigned 	r2;
//	unsigned	r;
	unsigned	txtz;
	unsigned	txtx1;
	int 		y1;
	int 		y2;
	int 		tn;
}				t_calc_tmp_int;


typedef struct	s_item
{
	int sectorno;
	int sx1;
	int sx2;
}				t_item;

typedef struct		s_scaler
{
	int				result;
	int 			bop;
	int 			fd;
	int 			ca;
	int 			cache;
}					t_scaler;

typedef struct		s_calc_tmp_struct
{
	t_item				now;
	t_scaler			ya_int;
	t_scaler			yb_int;
	t_scaler			nya_int;
	t_scaler			nyb_int;
	const t_sector 		*sect;
	t_xy				i1;
	t_xy				i2;
	t_xy				org1;
	t_xy				org2;
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
	t_item				*queue;
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
	t_xy_int		pos;
	double			seconds;
	double 			start_t;
	bool			constant;
}					t_msg;

/*
t_obj			// прототип структури для об'єкта
{
 	int sector	// номер сектора (звідти ще беремо висоту)
	t_xy_int	// позиція X Y
 	texture_id	// масив текстури для різних боків і знищення

 	hp			// -1 - невразливий
 				// від 1 - потрібна к-сть пострілів/ударів для смерті
 				// 0 - вбито

	animated	// 0 - анімація смерті відтворена
 				// від 1 - к-сть кадрів анімації (циклом пройдеться до нуля)

}
*/

typedef	struct 		s_weapons
{
	int 			***pistol_sprite;
	int 			***lighter_sprite;
	int 			type;
	double 			sprite_counter;
}					t_weapons;

typedef struct		s_sounds
{
	Mix_Music 		*bg_music;
	Mix_Chunk 		*run_sound;
	Mix_Chunk		*jumpbreath;
	Mix_Chunk		*landing;
	Mix_Chunk		*low_run;
	Mix_Chunk		*fast_run;
	Mix_Chunk		*lighter;
	Mix_Chunk		*lighter_close;
}					t_sounds;

// Player: location
typedef struct		s_players
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
	float 			speed;		// швидкість, менша для присяду
	int 			pushing;
	float			aclrt;		// acceleration / прискорення
	t_xy_int			ms;			// mouse aiming
	float 			ms_yaw;
	t_sdl_main		*sdl;
	int				light;
	int 			jump_check;

	bool			draw_look; // для перегляду відмальовування полінійно
}					t_player;

typedef struct		s_game
{
	t_player	plr;
	t_sdl_main	sdl;
	t_sector	*sectors;
	t_font		fonts[FONTS_NUM];
	t_msg		msgs[MAX_MSGS];
	t_weapons	wpn;
	bool		key_down;
	//	t_obj		*objs;		// масив зчитаних об'єктів

	int			error;		// для виводу тексту помилки при виході
}					t_game;

typedef struct		s_reader
{
	t_xy			*vert;
	t_posf			posf;
	t_sector		*sect;
	int 			NuMVertices;
	int				*num;
	int				all;
	int				len;
	int 			n;
}					t_reader;

typedef	struct 		s_math
{
	float a0;
	float a1;
	float b0;
	float b1;
	float x0;
	float x1;
	float y0;
	float y1;
	float x2;
	float y2;
	float x3;
	float y3;
	float px;
	float py;
	float xx0;
	float yy0;
	float xx1;
	float xxx1;
	float yyy1;
	float xxx2;
	float yyy2;
	float xxx3;
	float yyy3;
	float xxx4;
	float yyy4;
}					t_math;

/*
** Initialize functions
*/

void			init_sdl(t_game *g);
void 			load_data(t_player *player, t_sector **sectors);
char			*ft_itof(long double k);

/*
** Draw functions
*/

void			draw_screen(t_game *g, t_draw_screen_calc ds);
void			vline(int y1, int y2, int color, t_player *plr, t_draw_screen_calc *ds);
t_xy			vv_to_v(float x0, float y0, float x1, float y1);
float			len_vector(t_xy		free_vector);
float			scalar_product(t_xy xy0, t_xy xy1);
float			angle_vv(float scalar_product, float len0, float len1);
float			radian_to_grades(float rad);
float			vector_product(t_xy xy0, t_xy xy1);
int				move_or_not(t_xyz where ,t_sector sector, unsigned sect_num, int j);

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
							float dx, float dy, int i);
float			angles(t_xy xy0, t_xy xy1);

void			check_move(t_player *plr, t_sector **sc, unsigned int s);
void			check_fall(t_player *plr, t_sector **sectors);

/*
**	Quit
*/

int				exit_doom(t_game *g);


/*
** Font and text functions
*/

void			load_fonts(t_game *g);
void			clear_font(t_font *t);
void			init_msgs(t_game *g);
void			show_msg(t_game *g, t_msg m, t_font font);
void			get_messages(t_game *g);
t_msg			create_msg(char *text, uint8_t fontname, t_xy_int pos, int sec);
void			clear_msg(t_msg *m);

/*
 * Texture manipulating functions
 */

void	decor_texture(t_sdl_main *sdl, uint32_t t_n, uint32_t d_n, t_xy_uint cords);
void		textures_init(t_sdl_main *sdl);
float		percentage(int start, int end, int curr);
void		render(int draw_mode ,t_tex_i tex_i, t_player *p, t_draw_screen_calc *ds);
int 		scaler_next(t_scaler *i);
t_scaler	scalar_init(int a, int b, int c, int d, int f);
int			ft_get_pixel(SDL_Surface *sur, uint32_t x, uint32_t y);
void 		vline2(t_scaler ty, unsigned txtx, t_player *p, t_draw_screen_calc *ds);
void		vline_texture(int y1, int y2, int text_num, t_player *plr, t_draw_screen_calc *ds);
int		check_file(int fd);
void	*ft_realloc(void *ptr, size_t size);
t_posf	atof_posf(const char *s, t_posf posf, int exp);
void	reader_init(t_reader *read);
void	reader(char *line, int fd, t_player *p, t_sector **sectors);
t_reader	*reader_coroutine1(t_reader *read, char *line);
t_reader	*reader_coroutine2(t_reader *read, t_sector **sectors, t_player *p, char *line);
t_reader	*reader_coroutine3(t_reader *read);
t_reader	*reader_coroutine4(t_reader *read, char *line, t_player *p, t_sector **sectors);
void		unload_data(t_game *g);
float		percentage(int start, int end, int curr);
int			color_transoform(int color, float percent);
void		pix2(t_player *p, t_draw_screen_calc *ds, int y, t_tex_i tex_i);
void		pix1(t_player *p, t_draw_screen_calc *ds, int y, t_tex_i tex_i);
void		draw_ceil_floor(t_draw_screen_calc *ds, t_player *p, t_tex_i tex_i);
int			exit_doom(t_game *g);
int			scaler_next(t_scaler *i);
t_scaler	scalar_init(int a, int b, int c, int d, int f);
int			ft_get_pixel(SDL_Surface *sur, uint32_t x, uint32_t y);
int		draw_screen1(t_game *g, t_draw_screen_calc ds);
void	draw_screen2(t_game *g, t_draw_screen_calc ds);
void	render_sector_walls(t_draw_screen_calc *ds , t_sector *sector,
							t_item queue[MAX_QUE], t_game *g);
void	render_sector_walls1(t_draw_screen_calc *ds,
							 t_sector *sector, t_game *g);
void	render_sector(t_draw_screen_calc *ds, t_player *p, t_game *g);
void	render_ceil_floor(t_draw_screen_calc *ds, t_player *p);
void	ceil_floor_light(t_draw_screen_calc *ds, t_player *p, t_game *g);
void	render_walls(t_draw_screen_calc *ds, t_sector *sector, t_player plr);
void	render_walls2(t_draw_screen_calc *d, t_player plr);
void	perspective(t_draw_screen_calc *ds);
void	find_intersect(t_draw_screen_calc *ds);
void	find_intersect1(t_draw_screen_calc *ds);
void	find_intersect2(t_draw_screen_calc *ds);
void	find_intersect3(t_draw_screen_calc *ds);
void	pick_sector_slice(t_draw_screen_calc *ds);
void	rotate_view(t_draw_screen_calc *ds, t_game *g);
void	init_draw(t_draw_screen_calc *ds, t_player plr);
void		do_fall(t_player *plr, t_sector **sc, t_sounds *sounds);
t_sounds	*init_music_n_sounds(void);
void		load_weapons(t_game *g);
void		load_pistol(t_game *g);
void		load_lighter(t_game *g);
int		load_pistol_sprite(t_game *g, int sprite_count);
int		load_lighter_sprite(t_game *g, int sprite_count);
SDL_Surface		*load_pistol_part(int sprite);
SDL_Surface		*load_lighter_part(int sprite);
void		draw_weapons(t_game *g);
void		draw_pistol(t_game *g);
void		draw_lighter(t_game *g);
void		draw_cur_pistol_sprite(t_game *g, int width,
								   int height, int cur_sprite);
void		draw_cur_lighter_sprite(t_game *g, int width,
									int height, int cur_sprite);
void		events(t_game *g, t_sounds *sounds);
void		events1(const uint8_t *kstate, SDL_Event ev, t_game *g,
					t_sounds *sounds);
void		game_loop(t_game *g, t_player *plr, t_sounds *sounds);
void		game_loop1(t_game *g, t_sounds *sounds);
void		game_loop2(t_game *g);
void		game_loop3(t_game *g, t_player *plr, t_sounds *sounds);
void		events2(SDL_Event ev, t_game *g,
					t_sounds *sounds);
#endif
