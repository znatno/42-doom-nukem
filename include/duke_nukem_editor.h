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

#define W_WIDTH 1600
#define W_HEIGHT 950
#define W_DRAW 1400
#define H_DRAW 800

#ifndef UKR_LANG
# define UKR_LANG

#define СЛАВА_УКРАЇНІ(x) main(x)
#define ГЕРОЯМ_СЛАВА(x) return(x)

#define гривня int
#define буква char
#define гривня_з_копійками double
#define ніхріна void
#define дофіга(x) x*

#define от_стільки =
#define так_само ==
#define більше >
#define менше <
#define нарощувати(x) x++

#define перемога if
#define зрада else
#define ганяти_по_колу_доки while

#define червонець 10
#define вякати printf


#endif

#define NONE 0
#define LOOP_START 1
# define MAX(x, y) (x >= y) ? (x) : (y)
# define ROUND(x) ((int)(round((double)x/20.0)))*20
# define SPACE ' '
# define I draw->counter
typedef struct s_xy {
    int x;
    int y;
} t_xy;

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
    t_xy f_p[256];
    t_xy temp;
    int counter;
    bool s_mode;
    char key;
} t_draw;

typedef struct s_env
{

    SDL_Window *window;
    SDL_Event window_e;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
//    SDL_Event       event;
    int *buffer;
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

void    clear_screen(t_env *env);


/*
 * list_managing.c
 */

void            print_sector(t_sector *temp);

void            print_all_sectors(t_draw *draw, t_sector *temp);

void            add_sector_to_list(t_sector *temp, t_draw *draw);

void            delete_sector_from_list(t_draw *draw);

void            create_sectors_list(t_env *env, t_draw *draw, t_sector *temp);

#endif


