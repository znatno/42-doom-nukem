/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 21:17:15 by ggavryly          #+#    #+#             */
/*   Updated: 2019/08/30 21:17:17 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke_nukem_editor.h"

void	set_pixel(t_env *env, int x, int y, Uint32 pixel)
{
	env->buffer[(y * W_WIDTH) + x] = pixel;
}

void	draw_desk(t_env *env)
{
	t_xy	pos;
	int		sum;
	int		coef;

	sum = 0;
	coef = 1;
	pos.y = 0;
	while ((pos.y += 20) < H_DRAW)
	{
		pos.x = 0;
		while ((pos.x += 20) < W_DRAW)
		{
			set_pixel(env, pos.x, pos.y, 0xFFFFFF);
			sum += pos.x;
		}
		coef += 1;
	}
}

void	clear_screen(t_env *env)
{
	t_xy	pos;
	int		sum;

	sum = 0;
	pos.y = -1;
	while (++pos.y < H_DRAW)
	{
		pos.x = -1;
		while (++pos.x < W_DRAW)
		{
			set_pixel(env, pos.x, pos.y, 0x000);
			sum += pos.x;
		}
	}
}

void	draw_frame(t_env *env)
{
	t_xy	edge[2];

	edge[0].x = W_DRAW;
	edge[0].y = W_HEIGHT;
	edge[1].x = W_DRAW;
	edge[1].y = 0;
	line(edge[0], edge[1], env, 0x009900);
	edge[0].x += 1;
	edge[1].x += 1;
	line(edge[0], edge[1], env, 0x00AA00);
	edge[0].x += 1;
	edge[1].x += 1;
	line(edge[0], edge[1], env, 0x00FF00);
}
