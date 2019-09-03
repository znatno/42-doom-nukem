/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 22:16:27 by ggavryly          #+#    #+#             */
/*   Updated: 2019/08/12 22:16:28 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_xy	vv_to_v(float x0, float y0, float x1, float y1)		//x0,y0 x1,y1 = x,y пространственный вектор до свободного
{
	t_xy	xy;

	xy.x = x1 - x0;
	xy.y = y1 - y0;
	return (xy);
}

float	len_vector(t_xy		free_vector)
{
	float res = sqrtf(powf(free_vector.x, 2) + powf(free_vector.y, 2));
	return (res);
}

float	scalar_product(t_xy xy0, t_xy xy1)
{
	float res = xy0.x * xy1.x + xy0.y * xy1.y;
	return (res);
}

float	angle_vv(float scalar_product, float len0, float len1)
{
	float res = scalar_product / (len0 * len1);
	if (scalar_product != 0 && len0 != 0 && len1 != 0)
		return (res);
	return (-100);
}

float	radian_to_grades(float rad)
{
	float res = roundf((180.0 / M_PI) * rad);
	return (res);
}

float	vector_product(t_xy xy0, t_xy xy1)
{
	float res = ((xy0.x)*(xy1.y) - (xy1.x)*(xy0.y));
	return (res);
}

float	angles(t_xy xy0, t_xy xy1)
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

