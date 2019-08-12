#include "duke_nukem_editor.h"

void            print_sector(t_sector *temp)
{
    t_vertex *cur;

    cur = temp->vertexes;
    while (cur) {
    printf("x1 = %d y1 = %d \n x2 = %d y2 = %d\n\n",
            cur->xy1.x, cur->xy1.y, cur->xy2.x, cur->xy2.y);
        cur = cur->next;
    }
   // free(cur);
}

void            print_all_sectors(t_draw *draw, t_sector *temp)
{
    t_sector *cur_s;
    t_vertex *cur_v;

    cur_s = draw->head;
    while (cur_s)
    {
        printf("NEXT SECTOR\n");
        cur_v = cur_s->vertexes;
        while (cur_v) {
            printf("x1 = %d y1 = %d \n x2 = %d y2 = %d\n\n",
                   cur_v->xy1.x, cur_v->xy1.y, cur_v->xy2.x, cur_v->xy2.y);
            cur_v = cur_v->next;
        }
        cur_s = cur_s->next;
    }
    exit(1);
}

void            add_sector_to_list(t_sector *temp, t_draw *draw) {
    int i;
    t_vertex *head;

    while (temp->next != NULL)
        temp = temp->next;
    if (!(temp->next = (t_sector*)malloc(sizeof(t_sector))))
        exit(111);
    temp = temp->next;
    if (!(temp->vertexes = (t_vertex*)malloc(sizeof(t_vertex))))
        exit(167);
    head = temp->vertexes;
    i = 0;
    while (++i < I)
    {
        temp->vertexes->xy1.x = draw->f_p[i - 1].x;
        temp->vertexes->xy1.y = draw->f_p[i - 1].y;
        temp->vertexes->xy2.x = draw->f_p[i].x;
        temp->vertexes->xy2.y = draw->f_p[i].y;
//        printf("x1 = %d y1 = %d \n x2 = %d y2 = %d\n\n",
//               temp->vertexes->xy1.x, temp->vertexes->xy1.y, temp->vertexes->xy2.x, temp->vertexes->xy2.y);
        if (!(temp->vertexes->next = (t_vertex*)malloc(sizeof(t_vertex))))
            exit(168);
        temp->vertexes = temp->vertexes->next;
    }
    temp->vertexes->xy1.x = draw->f_p[i - 1].x;
    temp->vertexes->xy1.y = draw->f_p[i - 1].y;
    temp->vertexes->xy2.x = draw->f_p[0].x;
    temp->vertexes->xy2.y = draw->f_p[0].y;
//    printf("x1 = %d y1 = %d \n x2 = %d y2 = %d\n\n",
//           temp->vertexes->xy1.x, temp->vertexes->xy1.y, temp->vertexes->xy2.x, temp->vertexes->xy2.y);
    temp->vertexes->next = NULL;
    temp->vertexes = head;
    temp->next = NULL;
}

void            create_sectors_list(t_env *env, t_draw *draw, t_sector *temp)
{
    int i;
    t_vertex *head;

    if (!(temp->vertexes = (t_vertex*)malloc(sizeof(t_vertex))))
        exit(167);
    head = temp->vertexes;
    i = 0;
    while (++i < I)
    {
        temp->vertexes->xy1.x = draw->f_p[i - 1].x;
        temp->vertexes->xy1.y = draw->f_p[i - 1].y;
        temp->vertexes->xy2.x = draw->f_p[i].x;
        temp->vertexes->xy2.y = draw->f_p[i].y;
//        printf("x1 = %d y1 = %d \n x2 = %d y2 = %d\n\n",
//               temp->vertexes->xy1.x, temp->vertexes->xy1.y, temp->vertexes->xy2.x, temp->vertexes->xy2.y);
        if (!(temp->vertexes->next = (t_vertex*)malloc(sizeof(t_vertex))))
            exit(168);
        temp->vertexes = temp->vertexes->next;
    }
    temp->vertexes->xy1.x = draw->f_p[i - 1].x;
    temp->vertexes->xy1.y = draw->f_p[i - 1].y;
    temp->vertexes->xy2.x = draw->f_p[0].x;
    temp->vertexes->xy2.y = draw->f_p[0].y;
    temp->vertexes->next = NULL;
    temp->vertexes = head;
    temp->next = NULL;
    draw->head = temp;
}

void            save_sector(t_env *env, t_draw *draw)
{
    t_sector *temp;

    if (!(temp = draw->head))
    {
        if (!(temp = (t_sector *)malloc(sizeof(t_sector))))
            exit(166);
        create_sectors_list(env, draw, temp);
//        print_sector(temp);
    }
    else
    {
        add_sector_to_list(temp, draw);
        print_all_sectors(draw, temp);
    }

    //free(temp);
}

t_draw          *init_draw(t_draw *draw)
{
    if (!(draw = (t_draw*)malloc(sizeof(t_draw))))
    {
        exit(13);
    }
    I = 0;
    draw->temp.x = 0;
    draw->temp.y = 0;
    draw->head = NULL;
    return (draw);
}

void             draw_vertex(t_env *env, t_draw *draw)
{
    SDL_GetMouseState(&draw->temp.x, &draw->temp.y);
    if (draw->key == SPACE && draw->f_p[0].y != 0 && draw->f_p[0].x != 0 && I > 2)
    {
        line(draw->f_p[I - 1], draw->f_p[0], env, 0xFF00FF);
        save_sector(env, draw);
        I = -1;
    }
    else if (I && draw->key != SPACE)
    {
        draw->temp.x = ROUND(draw->temp.x);
        draw->temp.y = ROUND(draw->temp.y);
        line(draw->f_p[I - 1], draw->temp, env, 0xFF00FF);
        draw->f_p[I].x = draw->temp.x;
        draw->f_p[I].y = draw->temp.y;
    }
    else if (!I && draw->key != SPACE)
    {
        draw->f_p[I].x = ROUND(draw->temp.x);
        draw->f_p[I].y = ROUND(draw->temp.y);
    }
    I++;
    SDL_WarpMouseInWindow(env->window, ROUND(draw->temp.x), ROUND(draw->temp.y));
}

t_env           *sdl_main_loop(t_env *env)
{
    const Uint8 *kstate;
    t_draw      *draw;
    SDL_Event   ev;
    int         loop;


    draw = init_draw(draw);
    draw_desk(env);
    loop = 1;
    while (loop && env->sdl_error == NONE) {
        kstate = SDL_GetKeyboardState(NULL);
        while (SDL_PollEvent(&ev))
        {
            if (kstate[SDL_SCANCODE_ESCAPE] || ev.type == SDL_QUIT)
                loop = 0;
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
//    free(draw);
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
    SDL_Quit();
    return (0);
}
