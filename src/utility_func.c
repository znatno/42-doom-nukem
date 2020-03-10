/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibohun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 22:16:27 by ggavryly          #+#    #+#             */
/*   Updated: 2019/08/24 21:27:54 by ibohun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_xy	vect_to_dist(float x0, float y0, float x1, float y1)		//x0,y0 x1,y1 = x,y пространственный вектор до свободного
{
	return ((t_xy){x1 - x0, y1 - y0});
}

float	dist_to_len(t_xy free_vector)
{
	return (sqrtf(powf(free_vector.x, 2) + powf(free_vector.y, 2)));
}

float	scalar_product(t_xy xy0, t_xy xy1)
{
	return (xy0.x * xy1.x + xy0.y * xy1.y);
}

float	angle_vv(float scalar_product, float len0, float len1)
{
	return (scalar_product / (len0 * len1));
}

float	radian_to_grades(float rad)
{
	return (roundf(180.0 / M_PI * rad));
}

float	vector_product(t_xy xy0, t_xy xy1)
{
	return (xy0.x * xy1.y - xy1.x * xy0.y);
}

float	getangle_2vectors(t_xy v1, t_xy v2)
{
	return (radian_to_grades(acosf(angle_vv
			(scalar_product(v1, v2), dist_to_len(v1), dist_to_len(v2)))));
}

float 	getdistance(float x0, float y0, float x1, float y1)
{
	return (dist_to_len(vect_to_dist(x0, y0, x1, y1)));
}