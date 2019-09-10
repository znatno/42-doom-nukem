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

# define W						1024
# define H						768
# define X_0					0
# define Y_0					1
# define X_1					2
# define Y_1					3
# define RUN					1
# define JUMP					2
# define SEAT_RUN				4
# define FAST_RUN				5
# define GUN_FIRE				6
# define YAW(y, z)				(y + z * plr.yaw)
# define MAX_QUE				32
# define EYE_H 					6
# define DUCK_H					2.5
# define HEAD_MARGIN			1
# define KNEE_H					2
# define HFOV					(0.73f * H)
# define VFOV					(.2f * H)
# define H_FOV					(1.0 * 0.73f * H / W)
# define V_FOV					(1.0 * .2f)
# define ISDIGIT(c)				(c >= '0' && c <= '9')
# define RED					0
# define GREEN					1
# define TOP_PORTAL_WALL		0
# define BLUE					2
# define BOTTOM_PORTAL_WALL		1
# define CEIL					3
# define FULL_WALL				2
# define FLOOR					4
# define MIN(a, b)             (((a) < (b)) ? (a) : (b))
# define MAX(a, b)             (((a) > (b)) ? (a) : (b))
# define CLAMP(a, mi, ma)      MIN(MAX(a,mi),ma)
# define VXS(x0, y0, x1, y1)   ((x0)*(y1) - (x1)*(y0))
# define MAX_MSGS				100

typedef enum			e_fonts
{
	FONT_M_SM = 0,
	FONT_M_MD,
	FONT_M_BG,
	FONT_S_SM,
	FONT_S_MD,
	FONT_S_BG,
	FONTS_NUM
}						t_fonts;

typedef struct			s_xyz
{
	float				x;
	float				y;
	float				z;
}						t_xyz;

typedef struct			s_tex_i
{
	uint32_t			wall;
	uint32_t			ceil;
	uint32_t			floor;
}						t_tex_i;

typedef struct			s_posf_t
{
	int					pos;
	bool				is_y;
	float				value;
	float				y;
}						t_posf;

typedef struct			s_xy
{
	float				x;
	float				y;
}						t_xy;

typedef struct			s_xy_int
{
	int					x;
	int					y;
}						t_xy_int;

typedef struct			s_xy_uint
{
	uint32_t			x;
	uint32_t			y;
}						t_xy_uint;

typedef struct			s_sector
{
	float				floor;
	float				ceil;
	t_xy				*vertex;
	int					*neighbors;
	unsigned			npoints;
	t_xy				*vert;
}						t_sector;

typedef struct			s_keys
{
	bool				w;
	bool				s;
	bool				a;
	bool				d;
}						t_keys;

typedef struct			s_move_vec
{
	float				x;
	float				y;
}						t_move_vec;

typedef struct			s_textures
{
	SDL_Surface			**arr_tex;
	SDL_Surface			**decor_tex;
	uint32_t			txt_y;
	uint32_t			txt_x;
	float				perc_x;
	float				perc_y;
}						t_textures;

typedef struct			s_sdl_main
{
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Surface			*win_surface;
	t_textures			*textures;
	SDL_Texture			*texture;
	int					*buffer;
}						t_sdl_main;

typedef struct			s_tmp_iter
{
	int					start_do;
	int					x;
	unsigned			s;
}						t_tmp_iter;

typedef struct			s_calc_tmp_float
{
	float				vx1;
	float				vx2;
	float				vy1;
	float				vy2;
	float				pcos;
	float				psin;
	float				tx1;
	float				tx2;
	float				tz1;
	float				tz2;
	float				nearz;
	float				farz;
	float				nearside;
	float				farside;
	float				xscale1;
	float				xscale2;
	float				yscale1;
	float				yscale2;
	float				yceil;
	float				yfloor;
	float				nyceil;
	float				nyfloor;
	float				perc_light;
	float				hei;
	float				mapx;
	float				mapz;
	float				rtx;
	float				rtz;
}						t_calc_tmp_float;

typedef struct			s_calc_tmp_int
{
	int					y_top[W];
	int					y_bottom[W];
	int					*renderedsectors;
	int					x1;
	int					x2;
	int					neightbor;
	int					y1a;
	int					y1b;
	int					y2a;
	int					y2b;
	int					ny1a;
	int					ny1b;
	int					ny2a;
	int					ny2b;
	int					beginx;
	int					endx;
	int					z;
	int					ya;
	int					cya;
	int					yb;
	int					cyb;
	int					nya;
	int					cnya;
	int					nyb;
	int					cnyb;
	int					u0;
	int					u1;
	int					txtx;
	int					txty;
	int					pel;
	unsigned			txtz;
	unsigned			txtx1;
	int					y1;
	int					y2;
	int					tn;
}						t_calc_tmp_int;

typedef struct			s_item
{
	int					sectorno;
	int					sx1;
	int					sx2;
}						t_item;

typedef struct			s_scaler
{
	int					result;
	int					bop;
	int					fd;
	int					ca;
	int					cache;
}						t_scaler;

typedef struct			s_calc_tmp_struct
{
	t_item				now;
	t_scaler			ya_int;
	t_scaler			yb_int;
	t_scaler			nya_int;
	t_scaler			nyb_int;
	const t_sector		*sect;
	t_xy				i1;
	t_xy				i2;
	t_xy				org1;
	t_xy				org2;
	t_item				*head;
	t_item				*tail;
	t_sector			*sector;
}						t_calc_tmp_struct;

typedef struct			s_draw_screen_calc
{
	t_calc_tmp_int		*i;
	t_calc_tmp_float	*f;
	t_calc_tmp_struct	*s;
	t_tmp_iter			*it;
	t_item				*queue;
}						t_draw_screen_calc;

typedef struct			s_font
{
	TTF_Font			*ttf;
	char				*name;
	int					size;
	SDL_Color			color;
}						t_font;

typedef struct			s_msg
{
	char				*text;
	uint8_t				font_num;
	t_xy_int			pos;
	double				seconds;
	double				start_t;
	bool				constant;
}						t_msg;

typedef	struct			s_weapons
{
	int					***pistol_sprite;
	int					***lighter_sprite;
	int					type;
	double				sprite_counter;
}						t_weapons;

typedef struct			s_scri
{
	int					a;
	int					b;
	int					c;
	int					d;
	int					f;
}						t_scri;

typedef struct			s_sounds
{
	Mix_Music			*bg_music;
	Mix_Chunk			*run_sound;
	Mix_Chunk			*jumpbreath;
	Mix_Chunk			*landing;
	Mix_Chunk			*low_run;
	Mix_Chunk			*fast_run;
	Mix_Chunk			*lighter;
	Mix_Chunk			*lighter_close;
	Mix_Chunk			*gun_fire;
}						t_sounds;

typedef	struct			s_math
{
	float				a0;
	float				a1;
	float				b0;
	float				b1;
	float				x0;
	float				x1;
	float				y0;
	float				y1;
	float				x2;
	float				y2;
	float				x3;
	float				y3;
	float				px;
	float				py;
	float				xx0;
	float				yy0;
	float				xx1;
	float				yy1;
	float				xxx1;
	float				yyy1;
	float				xxx2;
	float				yyy2;
	float				xxx3;
	float				yyy3;
	float				xxx4;
	float				yyy4;
}						t_math;

typedef struct			s_moca
{
	t_sector			*sect;
	t_xy				*vert;
	float				px;
	float				py;
	int					flag[2];
}						t_moca;

typedef struct			s_ui
{
	uint32_t			t_n;
	uint32_t			d_n;
}						t_ui;

typedef struct			s_players
{
	t_xyz				where;
	t_xyz				vlct;
	float				angle;
	float				anglesin;
	float				anglecos;
	float				yaw;
	unsigned			sector;
	unsigned int		num_scts;
	bool				ground;
	bool				falling;
	bool				moving;
	bool				ducking;
	bool				run;
	bool				fly;
	float				eyeheight;
	t_keys				key;
	t_move_vec			mv;
	float				speed;
	int					pushing;
	float				aclrt;
	t_xy_int			ms;
	float				ms_yaw;
	t_sdl_main			*sdl;
	t_moca				mc;
	int					light;
	int					jump_check;
	bool				draw_look;
}						t_player;

typedef struct			s_game
{
	t_player			plr;
	t_sdl_main			sdl;
	t_sector			*sectors;
	t_font				fonts[FONTS_NUM];
	t_msg				msgs[MAX_MSGS];
	t_weapons			wpn;
	bool				key_down;
	int					error;
}						t_game;

typedef struct			s_reader
{
	t_xy				*vert;
	t_posf				posf;
	t_sector			*sect;
	int					num_vertices;
	int					*num;
	int					all;
	int					len;
	int					n;
}						t_reader;

typedef struct			s_chloe
{
	t_sector			*sectors;
	t_sector			sect;
	unsigned int		s;
	t_player			**plr;
	t_xy				*vert;
}						t_chloe;

void					init_sdl(t_game *g);
void					load_data(t_player *player, t_sector **sectors);
char					*ft_itof(long double k);
void					main_draw(t_game *g, t_draw_screen_calc ds);
t_xy					vv_to_v(float x0, float y0, float x1, float y1);
float					len_vector(t_xy		free_vector);
float					scalar_product(t_xy xy0, t_xy xy1);
float					angle_vv(float scalar_product, float len0, float len1);
float					radian_to_grades(float rad);
float					vector_product(t_xy xy0, t_xy xy1);
int						move_or_not(t_xyz where, t_sector sector,
						unsigned sect_num, int j);
bool					overflow(float a0, float a1, float b0, float b1);
bool					surface_in(t_math m);
t_xy					crossing(t_math m);
float					point_basis(t_math m);
void					motion(t_player *plr, t_sector **sectors,
						float dx, float dy);
float					angles(t_xy xy0, t_xy xy1);
void					check_move(t_player *p, t_sector **sc, unsigned int s);
void					check_fall(t_player *plr, t_sector **sectors);
int						exit_doom(t_game *g);
void					load_fonts(t_game *g);
void					clear_font(t_font *t);
void					init_msgs(t_game *g);
void					show_msg(t_game *g, t_msg m, t_font font);
void					get_messages(t_game *g);
t_msg					create_msg(char *text, uint8_t fontname,
						t_xy_int pos, int sec);
void					clear_msg(t_msg *m);
int						inter_point(unsigned int s, t_sector **sc, t_player *p);
void					move_init(t_player **p, t_sector **s, float d, float z);
void					check_sector(t_player **p,
						t_sector **s, float x, float y);
void					check_dia(t_player **plr,
						t_sector **sectors, float dx, float dy);
void					textures_init(t_sdl_main *sdl);
float					percentage(int start, int end, int curr);
void					render(int d, t_tex_i t, t_player *p,
						t_draw_screen_calc *ds);
int						scr_nxt(t_scaler *i);
t_scaler				scalar_create(t_scri r);
int						ft_get_pixel(SDL_Surface *sur, uint32_t x, uint32_t y);
void					vertl(t_scaler ty, unsigned txtx, t_player *p,
							t_draw_screen_calc *ds);
int						check_file(int fd);
void					*ft_realloc(void *ptr, size_t size);
t_posf					atof_posf(const char *s, t_posf posf, int exp);
void					reader_init(t_reader *read);
void					reader(char *line,
						int fd, t_player *p, t_sector **sectors);
t_reader				*reader_coroutine1(t_reader *read, char *line);
t_reader				*reader_coroutine2(t_reader *read,
						t_sector **sectors, t_player *p, char *line);
t_reader				*reader_coroutine3(t_reader *read);
t_reader				*reader_coroutine4(t_reader *read,
						char *line, t_player *p, t_sector **sectors);
void					unload_data(t_game *g);
float					percentage(int start, int end, int curr);
int						color_transoform(int color, float percent);
void					pix2(t_player *p, t_draw_screen_calc *ds,
						int y, t_tex_i tex_i);
void					pix1(t_player *p,
						t_draw_screen_calc *ds, int y, t_tex_i tex_i);
void					draw_ceil_floor(t_draw_screen_calc *ds,
						t_player *p, t_tex_i tex_i);
int						exit_doom(t_game *g);
void					help_events1(SDL_Event ev, t_game **g, t_sounds *s);
int						scr_nxt(t_scaler *i);
int						ft_get_pixel(SDL_Surface *sur, uint32_t x, uint32_t y);
int						main_draw1(t_game *g, t_draw_screen_calc ds);
void					main_draw2(t_game *g, t_draw_screen_calc ds);
void					rsw(t_draw_screen_calc *ds, t_sector *sector,
						t_item *queue, t_game *g);
void					render_sector_walls1(t_draw_screen_calc *ds,
						t_sector *sector, t_game *g);
void					render_sector(t_draw_screen_calc *ds,
						t_player *p, t_game *g);
void					render_ceil_floor(t_draw_screen_calc *ds, t_player *p);
void					ceil_floor_light(t_draw_screen_calc *ds,
						t_player *p, t_game *g);
void					render_walls(t_draw_screen_calc *ds, t_sector *sector,
						t_player plr);
void					render_walls2(t_draw_screen_calc *d, t_player plr);
void					perspective(t_draw_screen_calc *ds);
void					find_intersect(t_draw_screen_calc *ds);
void					find_intersect1(t_draw_screen_calc *ds);
void					find_intersect2(t_draw_screen_calc *ds);
void					find_intersect3(t_draw_screen_calc *ds);
void					pick_sector_slice(t_draw_screen_calc *ds);
void					rotate_view(t_draw_screen_calc *ds, t_game *g);
void					init_draw(t_draw_screen_calc *ds, t_player plr);
void					do_fall(t_player *plr, t_sector **sc, t_sounds *sounds);
t_sounds				*init_music_n_sounds(void);
void					load_weapons(t_game *g);
void					load_pistol(t_game *g);
void					load_lighter(t_game *g);
int						load_pistol_sprite(t_game *g, int sprite_count);
int						load_lighter_sprite(t_game *g, int sprite_count);
SDL_Surface				*load_pistol_part(int sprite);
SDL_Surface				*load_lighter_part(int sprite);
void					draw_weapons(t_game *g);
void					draw_pistol(t_game *g);
void					draw_lighter(t_game *g);
void					draw_cur_pistol_sprite(t_game *g, int width,
						int height, int cur_sprite);
void					draw_cur_lighter_sprite(t_game *g, int width,
						int height, int cur_sprite);
void					events(t_game *g, t_sounds *sounds);
void					events1(const uint8_t *kstate, SDL_Event ev, t_game *g,
						t_sounds *sounds);
void					game_loop(t_game *g, t_player *plr, t_sounds *sounds);
void					game_loop1(t_game *g, t_sounds *sounds);
void					game_loop2(t_game *g);
void					game_loop3(t_game *g, t_player *plr, t_sounds *sounds);
void					events2(SDL_Event ev, t_game *g, t_sounds *sounds);

#endif
