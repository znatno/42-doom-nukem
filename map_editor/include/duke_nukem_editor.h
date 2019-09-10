/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duke_nukem_editor.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopolonc <vopolonc@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 20:54:36 by vopolonc          #+#    #+#             */
/*   Updated: 2019/08/31 20:54:36 by vopolonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DUKE_NUKEM_EDITOR_H
# define DUKE_NUKEM_EDITOR_H

# include "SDL.h"
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
# include "SDL_ttf.h"

# define KOSTYL_1 draw->s_mode && (draw->head != NULL)
# define KOSTYL_2 (draw->place_p.y > 4) && draw->head && draw->s_mode
# define WALL_MOD_CONDITION draw->w_mode && !draw->d_mode && KOSTYL_1
# define PLAYER_PLACEMENT_CONDITION draw->place_p.x > 4 && KOSTYL_2
# define OBJ_COND click_to_text(env) >= 10 && click_to_text(env) <= 12
# define OBJ draw->save->object[click_to_text(env) % 10]
# define ACT_COND click_to_text(env) >= 12 && click_to_text(env) <= 15
# define ACT draw->save->action[click_to_text(env) % 10 - SHIFT]
# define DRAW_OBJ draw->save && draw->head && draw->cur_s > 0 && !draw->d_mode
# define K_R draw->kstate[SDL_SCANCODE_RIGHT]
# define K_U draw->kstate[SDL_SCANCODE_UP]
# define K_D draw->kstate[SDL_SCANCODE_DOWN]
# define K_ENTER draw->kstate[SDL_SCANCODE_RETURN]
# define N_H (draw->head != NULL)
# define N_H_N (draw->head->next != NULL)
# define W_WIDTH 1600
# define W_HEIGHT 950
# define W_DRAW 1400
# define H_DRAW 940
# define X        0
# define Y        1
# define CEIL        0
# define DRAW_MODE    1
# define FLOOR        2
# define LEFT        3
# define OBJECTS        4
# define PLAYER        5
# define REFRESH        6
# define RIGHT        7
# define SELECT_MODE 8
# define WALL_MODE    9
# define SHIFT 3
# define GUNS_OBJ    10
# define KITS_OBJ    11
# define ARMOR_OBJ   12
# define DEATH_ACT    13
# define FLY_ACT        14
# define MIXED_ACT   15
# define TEXTURE_COORDS (t_xy){.x = (1470), .y = (442)}
# define TEXTURE_DEFAULT 20
# define TEXTURE_MAX 26
# define SHIFT 3
# define GUNS_OBJ    10
# define KITS_OBJ    11
# define ARMOR_OBJ   12
# define DEATH_ACT    13
# define FLY_ACT        14
# define MIXED_ACT   15
# define TEXTURE_COORDS (t_xy){.x = (1470), .y = (442)}
# define TEXTURE_DEFAULT 20
# define TEXTURE_MAX 26
# define NONE 0
# define MAX(x, y) (x >= y) ? (x) : (y)
# define ROUND(x) ((int)(round((double)x/20.0)))*20
# define SPACE ' '
# define I draw->counter
# define DEFAULT_FLOOR 0
# define DEFAULT_CEIL 20
# define RED (255 << 16)
# define GREEN (255 << 8)
# define BLUE (255)
# define VIOLET (BLUE | RED)
# define WHITE (VIOLET | CYAN)
# define CYAN (BLUE | GREEN)

typedef struct			s_xyf
{
	float				x;
	float				y;
}						t_xyf;

typedef struct			s_mode
{
	bool				ceil_mode;
	bool				floor_mode;
	bool				d_mode;
}						t_mode;

typedef struct			s_xy
{
	int					x;
	int					y;

}						t_xy;

typedef struct			s_xy_l
{
	int					x;
	int					y;
	int					index;
	struct s_xy_l		*next;
	struct s_xy_l		*tail;
}						t_xy_l;

typedef struct			s_stack
{
	struct s_xy			xy;
	struct s_stack		*next;
}						t_stack;

typedef struct			s_vertex
{
	t_xy				xy1;
	t_xy				xy2;
	int					texture;
	struct s_vertex		*next;
}						t_vertex;

typedef struct			s_portals
{
	struct s_xy			xy1;
	struct s_xy			xy2;
	struct s_sector		*sec_a;
	struct s_sector		*sec_b;
	struct s_portals	*next;
}						t_portals;

typedef struct			s_index
{
	int					index;
	struct s_index		*next;
}						t_index;

typedef struct			s_portal
{
	int					wall_portal;
	struct s_portal		*next;
}						t_portal;

typedef struct			s_rec_sec
{
	float				ceil;
	float				floor;
	int					index_s;
	t_index				*head_ind;
	t_portal			*head_por;
	struct s_rec_sec	*next;
}						t_rec_sec;

typedef struct			s_record
{
	int					least_y;
	int					least_x;
	t_xy_l				*head_ver;
	t_rec_sec			*head_sec;
	int					player_x;
	int					player_y;
	int					player_sec;
}						t_record;

typedef struct			s_line
{
	u_int				p_color;
	int					start;
	int					end;
	int					tmp_x;
	int					tmp_y;
	int					dx;
	int					dy;
	int					px;
	int					py;
}						t_line;

typedef struct			s_sector
{
	t_vertex			*vertexes;
	int					floor;
	int					ceil;
	int					walls;
	bool				object[3];
	bool				action[3];
	struct s_sector		*next;
}						t_sector;

typedef struct			s_font
{
	TTF_Font			*font;
	SDL_Color			color;
	SDL_Surface			*font_surface;
	uint32_t			it_x;
	uint32_t			it_y;
	uint32_t			size_w;
	uint32_t			size_h;
}						t_font;

typedef struct			s_place_p
{
	int					x;
	int					y;
	t_sector			*sect_p;
}						t_place_p;

typedef struct			s_draw
{
	t_sector			*head;
	t_portals			*portals;
	t_xy				temp;
	t_sector			*player;
	t_place_p			place_p;
	t_sector			*save;
	t_vertex			*save_v;
	SDL_Event			ev;
	const Uint8			*kstate;
	int					loop;
	int					counter;
	int					s_count;
	int					p_count;
	int					cur_s;
	int					cur_v;
	bool				s_mode;
	bool				d_mode;
	bool				w_mode;
	bool				floor_mode;
	bool				ceil_mode;
	char				key;
}						t_draw;

typedef struct			s_textures
{
	SDL_Surface			**arr_tex;
	t_xy				*cords;
	t_xy				*cords_end;
	int					selected;
}						t_textures;

typedef struct			s_env
{

	SDL_Window			*window;
	SDL_Surface			*win_surface;
	t_textures			*textures;
	uint32_t			*buffer;
	int					mouse_x;
	int					mouse_y;
	int					sdl_error;
}						t_env;

void					line(t_xy pt1, t_xy pt2, t_env *env, u_int color);

void					set_pixel(t_env *env, int x, int y, Uint32 pixel);

void					draw_frame(t_env *env);

void					draw_desk(t_env *env);

void					draw_tools(t_env *env);

void					draw_texture(t_xy cords, uint32_t num_tex,
						uint32_t color, t_env *env);

void					clear_screen(t_env *env);

void					texture_load(t_env *env);

void					texture_cords(t_env *env);

void					texture_cords_end(t_env *env);

void					draw_text(uint32_t cord_x, uint32_t cord_y,
						char *text, t_env *env);

uint32_t				get_pixel(SDL_Surface *sur, uint32_t x,
						uint32_t y, uint32_t color);

void					delete_sector_from_list(t_env *env, t_draw *draw);

void					free_sect(t_draw *draw, t_sector *del_me,
						t_sector *cur_s);

t_sector				*check_if_deleted_sector(t_draw *draw, t_vertex *tmp,
						t_vertex *cur_v, t_sector *cur_s);

void					draw_select_text(t_draw *draw, t_env *env);

void					draw_wall(t_xy cords, uint32_t num_tex, t_env *env);

t_xy					stack_pop(struct s_stack **head);

void					stack_push(struct s_stack **head, t_xy data);

void					draw_dot(t_env *env, t_draw *draw, t_stack **head);

void					stack_draw(t_env *env, t_draw *draw, t_stack **head);

int						stack_more_than_two(struct s_stack **head);

void					save_stack_to_list(t_env *env, t_draw *draw,
						t_stack **head);

void					malloc_list(t_sector *sect);

void					malloc_list_first(t_sector *sect);

t_sector				*last_in_list(t_draw *draw);

void					find_portal(t_env *env, t_draw *draw,
						t_vertex *temp, t_sector *temp_s);

int						find_portal_for_draw(t_env *env, t_draw *draw,
						t_vertex *temp, t_sector *temp_s);

void					pop_from_stack_to_list(t_env *env, t_draw *draw,
						t_stack **head, int i);

void					draw_all_portals(t_env *env, t_draw *draw);

t_record				*transform_data(t_draw *draw);

void					delete_portal(t_draw *draw, t_vertex *cur_v);

int						get_index_sec(t_sector *sec, t_sector *head_sec);

t_xy					get_point_cords(int index, t_xy_l *head_vi);

int						get_index(t_xy ab, t_xy_l *list);

t_xy_l					*create_vertex(t_sector *sector, int y);

t_record				*create_vertex_list(t_sector *sectors);

t_portal				*portal_list(t_xy_l *h, t_rec_sec *c,
						t_portals *p, t_sector *s);

t_index					*create_sector_edge_list(t_sector curr,
						t_record *rec);

t_rec_sec				*create_sector_list(t_sector *sectors,
						t_record *record, t_draw *d);

int						a_or_b(t_sector *sectors, t_rec_sec *curr,
						t_sector *a, t_sector *b);

int						find_smallest_y(t_sector *sector, t_record *rec);

int						find_smallest_x(t_sector *sector, int y, int x);

void					num_cat(char **tmp, int num);

int						click_to_text(t_env *env);

void					draw_obj_and_action(t_env *env, t_sector *save);

void					draw_player(t_draw *draw, t_env *env, t_sector *save);

int						place_player(t_xyf cords, t_sector *sector);

void					record_data(t_record *record);

void					open_font(TTF_Font **f, SDL_Color *color,
						SDL_Surface **fs, char *text);

void					draw_text_black(uint32_t cord_x, uint32_t cord_y,
						char *t, t_env *env);

uint32_t				get_pixel_wall(SDL_Surface *sur, uint32_t x,
						uint32_t y);

void					refresh_screen(t_draw *draw, t_env *env,
						t_stack **head);

t_vertex				*save_vertex(t_env *env, int key, t_sector *save);

t_sector				*select_sector_mode(t_env *env, t_draw *draw,
						int key, int i);

void					sector_selection_right(t_env *env, t_draw *draw);

void					wall_selection_right(t_env *env, t_draw *draw);

void					delete_sector_del(t_env *env, t_draw *draw,
						t_stack **head);

void					player_placement_return(t_env *env, t_draw *draw);

void					finish_sector_space(t_draw *draw, t_env *env,
						t_stack **head);

void					delete_line_backspace(t_env *env, t_draw *draw,
						t_stack **head);

void					select_texture_up(t_env *env, t_draw *draw);

void					select_floor_up(t_env *env, t_draw *draw);

void					select_floor_down(t_env *env, t_draw *draw);

void					select_ceil_up(t_env *env, t_draw *draw);

void					select_ceil_down(t_env *env, t_draw *draw);

void					last_iteration(t_env *env, t_draw *draw);

void					choose_event(t_env *env, t_draw *draw, t_stack **head);

void					mouse_event(t_env *env, t_draw *draw, t_stack **head);

void					choose_event_second(t_env *env, t_draw *draw,
						t_stack **head);

t_draw					*init_draw(t_draw *draw);

void					init_vars(t_env *env);

t_portals				*last_portal(t_draw *draw);

void					new_portal(t_draw *draw, t_vertex *temp,
						t_sector *temp_s, t_sector *cur_s);

t_sector				*pop_helper(t_draw *draw, t_sector *cur_s);

t_vertex				*pop_helper_b(t_vertex *head_v,
						t_xy cpf[2], t_sector *cur_s);

void					sector_record(t_rec_sec *head_s, int fd);

t_index					*walk_sv_while(t_index *walk_sv, char *tmp);

char					*gena_pidor(t_rec_sec *walk_s, char *tmp);

t_portal				*walk_sp_while(t_portal *walk_sp, char *tmp);

float					len_vector(t_xyf free_vector);

float					scalar_product(t_xyf xy0, t_xyf xy1);

float					angle_vv(float scalar_product, float len0, float len1);

float					radian_to_grades(float rad);

float					vector_product(t_xyf xy0, t_xyf xy1);

void					record_free(t_record *record);

void					free_stack(t_stack **head);

#endif
