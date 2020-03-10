/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_func1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprokysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 12:39:28 by tprokysh          #+#    #+#             */
/*   Updated: 2019/09/03 12:39:29 by tprokysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_xy		vv_to_v(float x0, float y0, float x1, float y1)
{
	t_xy	xy;

	xy.x = x1 - x0;
	xy.y = y1 - y0;
	return (xy);
}

float		angles(t_xy xy0, t_xy xy1)
{
	float	len0;
	float	len1;
	float	scalar_p;
	float	angle;

	len0 = len_vector(xy0);
	len1 = len_vector(xy1);
	if (len0 == 0 || len1 == 0)
		return (-1);
	scalar_p = scalar_product(xy0, xy1);
	if (scalar_p == 0)
		return (-1);
	angle = radian_to_grades(acosf(angle_vv(scalar_p, len0, len1)));
	return (angle);
}

void		move_init(t_player **plr, t_sector **sectors, float dx, float dy)
{
	(*plr)->mc.px = (*plr)->where.x;
	(*plr)->mc.py = (*plr)->where.y;
	(*plr)->mc.sect = &(*sectors)[(*plr)->sector];
	(*plr)->mc.vert = (*plr)->mc.sect->vertex;
	(*plr)->mc.flag[1] = -1;
	(*plr)->mc.flag[0] = -2;
	(*plr)->where.x += dx;
	(*plr)->where.y += dy;
}

void		check_sector(t_player **plr, t_sector **sectors, float dx, float dy)
{
	(*plr)->mc.flag[0] = move_or_not((*plr)->where, (*sectors)[
			(*plr)->mc.sect->neighbors[(*plr)->mc.flag[1]]],
					(*plr)->mc.sect->neighbors[(*plr)->mc.flag[1]], 0);
	if ((*plr)->mc.flag[0] >= 0 && (*plr)->mc.flag[0] < (*plr)->num_scts)
		(*plr)->sector = (*plr)->mc.sect->neighbors[(*plr)->mc.flag[1]];
	else if ((*plr)->mc.flag[0] == -1)
	{
		(*plr)->where.x -= dx;
		(*plr)->where.y -= dy;
	}
}

void		check_dia(t_player **plr, t_sector **sectors, float dx, float dy)
{
	if ((*plr)->mc.flag[0] == -2)
	{
		(*plr)->mc.flag[0] = move_or_not((*plr)->where,
				(*sectors)[(*plr)->sector], (*plr)->sector, 0);
		if ((*plr)->mc.flag[0] == -1)
		{
			(*plr)->where.x -= dx;
			(*plr)->where.y -= dy;
		}
	}
	(*plr)->anglesin = sinf((*plr)->angle);
	(*plr)->anglecos = cosf((*plr)->angle);
}
