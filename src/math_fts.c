/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_fts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibohun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:00:11 by ibohun            #+#    #+#             */
/*   Updated: 2019/08/12 16:04:47 by ibohun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool overlap(float a0, float a1, float b0, float b1)
{
	if (min(a0,a1) <= max(b0,b1) && min(b0,b1) <= max(a0,a1))
		return (true);
	return (false);
}

bool intersect_box(float x0, float y0, float x1, float y1, float x2, float y2,
				   float x3, float y3)
{
	//printf("intersect\n");
	bool result;
	result = (overlap(x0, x1, x2, x3) && overlap(y0, y1, y2, y3));
	return (result);
}

float point_side(float px, float py, float x0, float y0, float x1, float y1)
{
	float result;
	result = vxs((x1)-(x0), (y1)-(y0), (px)-(x0), (py)-(y0));
	return (result);
}

t_xy intersect(float x1, float y1, float x2, float y2, float x3, float y3,
			   float x4, float y4)
{
	t_xy result;

	result = (t_xy){.x = vxs(vxs(x1,y1, x2,y2), (x1)-(x2),
							 vxs(x3,y3, x4,y4), (x3)-(x4))
						 / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)),
			.y = vxs(vxs(x1,y1, x2,y2), (y1)-(y2),
					 vxs(x3,y3, x4,y4), (y3)-(y4))
				 / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4))};
	return (result);
}

