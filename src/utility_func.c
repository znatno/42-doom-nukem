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

float	len_vector(t_xy free_vector)
{
	float res;

	res = sqrtf(powf(free_vector.x, 2) + powf(free_vector.y, 2));
	return (res);
}

float	scalar_product(t_xy xy0, t_xy xy1)
{
	float res;

	res = xy0.x * xy1.x + xy0.y * xy1.y;
	return (res);
}

float	angle_vv(float scalar_product, float len0, float len1)
{
	float res;

	res = scalar_product / (len0 * len1);
	if (scalar_product != 0 && len0 != 0 && len1 != 0)
		return (res);
	return (-100);
}

float	radian_to_grades(float rad)
{
	float res;

	res = roundf((180.0 / M_PI) * rad);
	return (res);
}

float	vector_product(t_xy xy0, t_xy xy1)
{
	float res;

	res = ((xy0.x) * (xy1.y) - (xy1.x) * (xy0.y));
	return (res);
}
