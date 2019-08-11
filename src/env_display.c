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