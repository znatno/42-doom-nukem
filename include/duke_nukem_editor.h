//
// Created by Vladislav OPOLONCHIK on 2019-08-09.
//

#ifndef DUKE_NUKEM_EDITOR_H
#define DUKE_NUKEM_EDITOR_H

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

#define W_WIDTH 1600
#define W_HEIGHT 950
#define W_DRAW 1400
#define H_DRAW 800
#define X		0
#define Y		1
#define CEIL		0
#define DRAW_MODE	1
#define FLOOR		2
#define	LEFT		3
#define	OBJECTS		4
#define	PLAYER		5
#define	REFRESH		6
#define RIGHT		7
#define SELECT_MODE 8
#define WALL_MODE	9

#define NONE 0
#define LOOP_START 1
# define MAX(x, y) (x >= y) ? (x) : (y)
# define ROUND(x) ((int)(round((double)x/20.0)))*20
# define SPACE ' '
# define I draw->counter

# define BLUE (255555555 << 8)

typedef struct s_xy {
    int x;
    int y;
} t_xy;

typedef struct s_stack {
	struct s_xy xy;
	struct t_stack *next;
}				t_stack;

typedef struct s_portals
{
	struct s_vertex *line;
	struct t_sector *sec_a;
	struct t_sector *sec_b;
	struct t_portals *next;
} t_portals;

typedef struct s_line {
    int start;
    int end;
    u_int p_color;
    int tmp_x;
    int tmp_y;
    int dx;
    int dy;
    int px;
    int py;
} t_line;


typedef struct s_vertex
{
    t_xy xy1;
    t_xy xy2;
    struct s_vertex *next;
} t_vertex;

typedef struct s_sector
{
    t_vertex *vertexes;
    struct s_sector *next;
} t_sector;

typedef struct s_posf_t
{
    int pos;
    bool is_y;
    float value;
    float y;
} t_posf;

//typedef struct		s_sector
//{
//	float			floor;
//	float			ceil;
//	t_xy			*vertex;
//	signed char		*neighbors;       // Each edge may have a corresponding neighboring sector
//	unsigned		npoints;          // How many vertexes there are
//	t_xy			*vert;
//}					t_sector;

typedef struct s_draw
{
    t_sector    *head;
    t_portals   *portals;
    t_xy f_p[256];
    t_xy temp;
    int counter;
  	int s_count;
    bool s_mode;
    char key;
} t_draw;

typedef struct		s_textures
{
	SDL_Surface		**arr_tex;
	t_xy			*cords;
	t_xy			*cords_end;
	int				selected;
	int				pre;
}					t_textures;

typedef struct s_env
{

    SDL_Window *window;
    SDL_Event window_e;
    SDL_Surface	*win_surface;
    t_textures	*textures;
//    SDL_Event       event;
    uint32_t *buffer;
    int		mouse_x;
    int		mouse_y;
    int zoom;
    int sdl_error;
} t_env;

void line(t_xy pt1, t_xy pt2, t_env *env, u_int color);

/*
 * env_display.c
 */

void set_pixel(t_env *env, int x, int y, Uint32 pixel);

void draw_frame(t_env *env);

void draw_desk(t_env *env);

void	draw_tools(t_env *env);

void	draw_texture(t_xy cords ,uint32_t num_tex, uint32_t color,t_env *env);

void    clear_screen(t_env *env);

void	texture_load(t_env *env);

void	texture_cords(t_env *env);

void	texture_cords_end(t_env *env);

void	draw_text(uint32_t cord_x, uint32_t cord_y, char *text, t_env *env);

uint32_t	get_pixel(SDL_Surface *sur, uint32_t x, uint32_t y, uint32_t color);


/*
 * list_managing.c
 */

void            print_sector(t_sector *temp);

void            print_all_sectors(t_draw *draw, t_sector *temp);

void            add_sector_to_list(t_sector *temp, t_draw *draw);

void            delete_sector_from_list(t_draw *draw);

void            create_sectors_list(t_env *env, t_draw *draw, t_sector *temp);

void			free_sect(t_draw *draw, t_sector *del_me, t_sector *cur_s);

t_sector 		*check_if_deleted_sector(t_draw *draw,  t_vertex *tmp,


										 t_vertex *cur_v, t_sector *cur_s);
void 			print_all_portals(t_draw *draw);

void	draw_select_text(t_env *env);


/*
 * stack boi
 */
t_xy    stack_pop(struct s_stack **head);

void    stack_push(struct s_stack **head, t_xy data);

void    stack_print(struct s_stack **head);

void    draw_dot(t_env *env, t_draw *draw, t_stack **head);

void	stack_draw(t_env *env, t_draw *draw, t_stack **head);

#endif


