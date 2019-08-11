#include "duke_nukem_editor.h"




void            save_sector(t_env *env, t_draw *draw)
{
    //
}

t_draw          *init_draw(t_draw *draw)
{
    if (!(draw = (t_draw*)malloc(sizeof(t_draw))))
    {
        exit(13);
    }
    draw->counter = 0;
    draw->temp.x = 0;
    draw->temp.y = 0;
    return (draw);
}

void             draw_vertex(t_env *env, t_draw *draw)
{


    SDL_GetMouseState(&draw->temp.x, &draw->temp.y);
    if (draw->key == SPACE && draw->f_p[0].y != 0 && draw->f_p[0].x != 0 && draw->counter > 2)
    {
        line(draw->f_p[draw->counter - 1], draw->f_p[0], env, 0xFF00FF);
        draw->counter = -1;
        //        save_sector(env, draw);
    }
    else if (draw->counter && draw->key != SPACE)
    {
        draw->temp.x = ROUND(draw->temp.x);
        draw->temp.y = ROUND(draw->temp.y);
        line(draw->f_p[draw->counter - 1], draw->temp, env, 0xFF00FF);
        draw->f_p[draw->counter].x = draw->temp.x;
        draw->f_p[draw->counter].y = draw->temp.y;
    }
    else if (!draw->counter && draw->key != SPACE)
    {
        draw->f_p[draw->counter].x = ROUND(draw->temp.x);
        draw->f_p[draw->counter].y = ROUND(draw->temp.y);
    }
    draw->counter++;
    SDL_WarpMouseInWindow(env->window, ROUND(draw->temp.x), ROUND(draw->temp.y));
}

t_env           *sdl_main_loop(t_env *env)
{
    const Uint8 *kstate;
    t_draw      *draw;
    SDL_Event   ev;



    draw = init_draw(draw);
    draw_desk(env);
    while (LOOP_START && env->sdl_error == NONE) {
        kstate = SDL_GetKeyboardState(NULL);
        while (SDL_PollEvent(&ev))
        {
            if (kstate[SDL_SCANCODE_ESCAPE] || ev.type == SDL_QUIT)
                exit(1);
            else if (kstate[SDL_SCANCODE_SPACE])
            {
                SDL_Delay(100);
                draw->key = SPACE; // space pressed
                draw_vertex(env, draw);
                draw->key = 0;
            }
            else if (ev.type == SDL_MOUSEBUTTONDOWN)
            {
                if (ev.button.clicks)
                {
                    draw_vertex(env, draw);
                }
            }
        }
        draw_frame(env);
        SDL_UpdateTexture(env->texture, NULL, env->buffer, W_WIDTH * (sizeof(int)));
        SDL_RenderCopy(env->renderer, env->texture, NULL, NULL);
        SDL_RenderPresent(env->renderer);
        SDL_Delay(10);
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
