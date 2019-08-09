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

#define NONE 0
#define LOOP_START 1
# define MAX(x, y) (x >= y) ? (x) : (y)

typedef struct s_xy
{
	int x;
	int y;
}				t_xy;

typedef struct s_line
{
	int			start;
	int			end;
	int			p0_color;
	int			p1_color;
	int			tmp_x;
	int			tmp_y;
	int			dx;
	int			dy;
	int			px;
	int			py;
}				t_line;

typedef struct s_posf_t {
	int     pos;
	bool    is_y;
	float   value;
	float   y;
}				t_posf;

typedef struct		s_sector
{
	float			floor;
	float			ceil;
	t_xy			*vertex;
	signed char		*neighbors;       // Each edge may have a corresponding neighboring sector
	unsigned		npoints;          // How many vertexes there are
	t_xy			*vert;
}					t_sector;

typedef struct s_env
{
	SDL_Window      *window;
	SDL_Event window_e;
	SDL_Renderer    *renderer;
	SDL_Texture     *texture;
//    SDL_Event       event;
	int             *buffer;
	int             zoom;
	int             sdl_error;


}				t_env;

void	line(t_xy pt1, t_xy pt2, t_env *env);

#endif
