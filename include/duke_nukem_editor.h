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
# define ROUND(x) ((int)(round((double)x/20.0)))*20

typedef struct s_xy
{
	int x;
	int y;
}				t_xy;

typedef struct s_line
{
	int			start;
	int			end;
	u_int		p_color;
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
	SDL_Event       window_e;
	SDL_Renderer    *renderer;
	SDL_Texture     *texture;
//    SDL_Event       event;
	int             *buffer;
	int             zoom;
	int             sdl_error;


}				t_env;
//
void	line(t_xy pt1, t_xy pt2, t_env *env, u_int color);
//
#endif
//
//
//
//void		events(t_sector **sectors, t_player *plr, bool *quit)
//{
//    const Uint8		*kstate; // array of keyboard keys states
//    SDL_Event		ev;
//
//    kstate = SDL_GetKeyboardState(NULL);
//    while (SDL_PollEvent(&ev))
//    {
//        if (kstate[SDL_SCANCODE_ESCAPE] || ev.type == SDL_QUIT)
//            exit_doom(sectors, plr);
//        plr->key.w = kstate[SDL_SCANCODE_W];
//        plr->key.a = kstate[SDL_SCANCODE_A];
//        plr->key.s = kstate[SDL_SCANCODE_S];
//        plr->key.d = kstate[SDL_SCANCODE_D];
//        if (ev.type == SDL_KEYDOWN)
//        {
//            if (ev.key.keysym.sym == SDLK_SPACE && plr->ground)
//            {
//                plr->vlct.z += 0.5;
//                plr->falling = 1;
//            }
//        }
////		if (kstate[SDL_SCANCODE_SPACE] && plr->ground)
////		{
////			printf("%d SPACE CODE: %d\n", ++g_x, kstate[SDL_SCANCODE_SPACE]);
////			plr->vlct.z += 0.25;
////			plr->falling = 1;
////		}
//        plr->ducking = kstate[SDL_SCANCODE_LCTRL];
//        if (plr->ducking)
//            plr->falling = 1;
//        SDL_PumpEvents(); // обработчик событий
//    }
//}
//
//void		game_loop(t_sdl_main *sdl, t_player *plr, t_sector *sectors)
//{
//    bool 			quit;
//
//    quit = false;
//    SDL_ShowCursor(SDL_DISABLE);
//    SDL_SetRelativeMouseMode(SDL_TRUE);
//    while(!quit)
//    {
//        events(&sectors, plr, &quit);
//        plr->eyeheight = plr->ducking ? DuckHeight : EyeHeight; /* Vertical collision detection */
//        plr->ground = !plr->falling;
//        if (plr->falling) //TODO: make ducking unreversable if стеля згори
//            do_fall(plr, &sectors);
//        if (plr->moving) /* Horizontal collision detection */
//            do_move(plr, &sectors);
//        /* mouse aiming */
//        plr->ms.x = 0;
//        plr->ms.y = 0;
//        SDL_GetRelativeMouseState(&plr->ms.x, &plr->ms.y);
//        plr->angle += plr->ms.x * 0.03f;
//        plr->ms.yaw = clamp(plr->ms.yaw - plr->ms.y * 0.05f, -5, 5);
//        plr->yaw = plr->ms.yaw - plr->vlct.z * 0.5f;
//        plr->mv = (t_move_vec){.x = 0.f, .y = 0.f};
//        MovePlayer(plr, &sectors, 0, 0);
//        plr->speed = 0.2f;
//        if (plr->ducking)
//            plr->speed /= 2;
//        if (plr->key.w)
//            plr->mv = (t_move_vec){.x = plr->mv.x + plr->anglecos * plr->speed,
//                    .y = plr->mv.y + plr->anglesin * plr->speed};
//        if (plr->key.s)
//            plr->mv = (t_move_vec){.x = plr->mv.x - plr->anglecos * plr->speed,
//                    .y = plr->mv.y - plr->anglesin * plr->speed};
//        if (plr->key.a)
//            plr->mv = (t_move_vec){.x = plr->mv.x + plr->anglesin * plr->speed,
//                    .y = plr->mv.y - plr->anglecos * plr->speed};
//        if (plr->key.d)
//            plr->mv = (t_move_vec){.x = plr->mv.x - plr->anglesin * plr->speed,
//                    .y = plr->mv.y + plr->anglecos * plr->speed};
//        plr->pushing = plr->key.w || plr->key.s || plr->key.a || plr->key.d;
//        plr->aclrt = plr->pushing ? 0.4 : 0.2;
//        plr->vlct.x = plr->vlct.x * (1 - plr->aclrt) + plr->mv.x * plr->aclrt;
//        plr->vlct.y = plr->vlct.y * (1 - plr->aclrt) + plr->mv.y * plr->aclrt;
//        if (plr->pushing)
//            plr->moving = 1;
//        draw_screen(sectors, *plr);
//        SDL_UpdateTexture(sdl->texture, NULL, sdl->buffer,W *(sizeof(int)));
//        SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
//        SDL_RenderPresent(sdl->renderer);
//        SDL_Delay(15);
//    }
//}