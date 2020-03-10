//
// Created by Vladislav OPOLONCHIK on 2019-08-06.
//

#include "../include/doom_nukem_editor.h"
//#include "SDL.h"
void set_pixel(p_env *env, int x, int y, Uint32 pixel)
{
    env->buffer[ ( y * W_WIDTH ) + x ] = pixel;
}

void		    draw_desk(p_env *env) {
    po_xyi pos;
    int sum;
    int coef;

    sum = 0;
    coef = 1;
    pos.y = 20;
    while (pos.y < W_DRAW)
    {
        pos.x = 10;
        while (pos.x < H_DRAW){
            set_pixel(env, pos.x, pos.y, 0xFF00FF);
            printf("%d ",pos.x);
            pos.x += 20;
            sum += pos.x;
        }
        coef += 1;
        printf("[%d[ \n",pos.y);
        pos.y += 20;
    }
}

p_env           *sdl_main_loop(p_env *env)
{
    int x, y = 0;
    int x2, y2 = 0;

    draw_desk(env);
    while (LOOP_START && env->sdl_error == NONE)
    {
        if (SDL_PollEvent(&env->window_e))
        {
            if (SDL_QUIT == env->window_e.type)
            {
                break;
            }
//            if (env->window_e.key.keysym.sym == 'w')
//            {
//                env->zoom += 1;
//            }
        }
        SDL_PumpEvents();
        if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
            set_pixel(env, x, y, 0xFF00FF);

        }
        SDL_UpdateTexture(env->texture, NULL, env->buffer, W_WIDTH *(sizeof(int)));
        SDL_RenderCopy(env->renderer, env->texture, NULL, NULL);
        SDL_RenderPresent(env->renderer);
    }
    return (env);
}


void            init_vars(p_env *env)
{
    env->sdl_error = NONE;
    env->zoom = 20;
}

p_env           *sdl_init(p_env   *env)
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
    p_env       *env;

    env = malloc(sizeof(p_env));
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
