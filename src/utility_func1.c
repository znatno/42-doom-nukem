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

t_xy	vv_to_v(float x0, float y0, float x1, float y1)
{
	t_xy	xy;

	xy.x = x1 - x0;
	xy.y = y1 - y0;
	return (xy);
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
