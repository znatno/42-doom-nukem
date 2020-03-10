/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 21:16:07 by ggavryly          #+#    #+#             */
/*   Updated: 2019/08/30 21:16:19 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke_nukem_editor.h"

void	pixel_put(t_line line, t_env *env)
{
	if (line.tmp_x < W_WIDTH && line.tmp_x >= 0 &&
		line.tmp_y < W_HEIGHT && line.tmp_y >= 0)
	{
		env->buffer[line.tmp_y * W_WIDTH + line.tmp_x] = line.p_color;
	}
}

void	fill_line(t_line *line, t_xy xy0, t_xy xy1, u_int color)
{
	line->p_color = color;
	line->tmp_x = xy0.x;
	line->tmp_y = xy0.y;
	line->dx = abs(xy1.x - xy0.x);
	line->dy = abs(xy1.y - xy0.y);
	line->px = xy1.x >= xy0.x ? 1 : -1;
	line->py = xy1.y >= xy0.y ? 1 : -1;
}

void	draw_dx(t_line line, t_env *env, int i)
{
	int d;

	d = -line.dx;
	i++;
	while (i--)
	{
		pixel_put(line, env);
		line.tmp_x += line.px;
		d += 2 * line.dy;
		if (d > 0)
		{
			d -= 2 * line.dx;
			line.tmp_y += line.py;
		}
	}
}

void	draw_dy(t_line line, t_env *env, int i)
{
	int d;

	d = -line.dy;
	i++;
	while (i--)
	{
		pixel_put(line, env);
		line.tmp_y += line.py;
		d += 2 * line.dx;
		if (d > 0)
		{
			d -= 2 * line.dy;
			line.tmp_x += line.px;
		}
	}
}

void	line(t_xy pt1, t_xy pt2, t_env *env, u_int color)
{
	t_line	line;
	int		i;

	fill_line(&line, pt1, pt2, color);
	i = MAX(line.dx, line.dy);
	if (i == 0)
		pixel_put(line, env);
	if (line.dy <= line.dx)
	{
		line.start = pt1.x;
		line.end = pt2.x;
		draw_dx(line, env, i);
	}
	else
	{
		line.start = pt1.y;
		line.end = pt2.y;
		draw_dy(line, env, i);
	}
}
