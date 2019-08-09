#include "duke_nukem_editor.h"
void set_pixel(t_env *env, int x, int y, Uint32 pixel)
{
    env->buffer[ ( y * W_WIDTH ) + x ] = pixel;
}

void    draw_desk(t_env *env) {
    t_xy pos;
    int sum;
    int coef;

    sum = 0;
    coef = 1;
    pos.y = 0;
    while ((pos.y += 20) < H_DRAW)
    {
        pos.x = 0;
        while ((pos.x += 20) < W_DRAW){
            set_pixel(env, pos.x, pos.y, 0xFFFFFF);
            sum += pos.x;
        }
        coef += 1;
    }
}

void			draw_frame(t_env *env)
{
	t_xy	edge[2];

	edge[0].x = W_DRAW;
	edge[0].y = H_DRAW;
	edge[1].x = W_DRAW;
	edge[1].y = 0;
	line(edge[0], edge[1], env, 0xffffff00);
	edge[1].x = 0;
	edge[1].y = H_DRAW;
	line(edge[0], edge[1], env, 0xffffff00);
}


t_env           *sdl_main_loop(t_env *env)
{
    int x, y = 0;

    draw_desk(env);
    while (LOOP_START && env->sdl_error == NONE)
    {
        if (SDL_PollEvent(&env->window_e))
        {
            if (SDL_QUIT == env->window_e.type)
            {
                break;
            }
        }
        SDL_PumpEvents();
        if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            set_pixel(env, x, y, 0xFF00FF);
        }
        draw_frame(env);
        SDL_UpdateTexture(env->texture, NULL, env->buffer, W_WIDTH *(sizeof(int)));
        SDL_RenderCopy(env->renderer, env->texture, NULL, NULL);
        SDL_RenderPresent(env->renderer);
    }
    return (env);
}


void            init_vars(t_env *env)
{
    env->sdl_error = NONE;
    env->zoom = 20;
}

t_env           *sdl_init(t_env   *env)
{
    init_vars(env);
    env->window  = SDL_CreateWindow("doom-nukem-editor", 910, 510, W_WIDTH, W_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    env->buffer = (int*)malloc(sizeof(int) * W_HEIGHT * W_WIDTH);
    if (!env->window) {
        //env->sdl_error = ERROR_WINDOW;
        SDL_GetError();
    }
    env->renderer = SDL_CreateRenderer(env->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    env->texture = SDL_CreateTexture(env->renderer,
									 SDL_PIXELFORMAT_ARGB32,
									 SDL_TEXTUREACCESS_STREAMING,
									 W_WIDTH, W_HEIGHT);
    return (env);
}

int             main()
{
    t_env       *env;

    env = malloc(sizeof(t_env));
    if (!(SDL_Init(SDL_INIT_EVERYTHING) < 0))
    {
        env = sdl_main_loop(sdl_init(env));
    }
    else
    {
        SDL_GetError();
    }
    printf("IM HERE");
    SDL_Quit();
    return (0);
}
