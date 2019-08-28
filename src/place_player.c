/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 14:31:38 by ggavryly          #+#    #+#             */
/*   Updated: 2019/08/28 14:31:40 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke_nukem_editor.h"

t_xyf	vv_to_v(float x0, float y0, float x1, float y1)		//x0,y0 x1,y1 = x,y пространственный вектор до свободного
{
	t_xyf	xy;

	xy.x = x1 - x0;
	xy.y = y1 - y0;
	return (xy);
}

float	len_vector(t_xyf		free_vector)
{
	float res = sqrtf(powf(free_vector.x, 2) + powf(free_vector.y, 2));
	return (res);
}

float	scalar_product(t_xyf xy0, t_xyf xy1)
{
	float res = xy0.x * xy1.x + xy0.y * xy1.y;
	return (res);
}

float	angle_vv(float scalar_product, float len0, float len1)
{
	float res = scalar_product / (len0 * len1);
	return (res);
}

float	radian_to_grades(float rad)
{
	float res = roundf((180.0 / M_PI) * rad);
	return (res);
}

float	vector_product(t_xyf xy0, t_xyf xy1)
{
	float res = ((xy0.x)*(xy1.y) - (xy1.x)*(xy0.y));
	return (res);
}

int		place_player(t_xyf cords, t_sector *sector)
{
	t_vertex	*walk_v;
	t_xyf		xy[2];
	float 		sum_angles;
	float 		curr_angle;

	sum_angles = 0.0;
	walk_v = sector->vertexes;
	while (walk_v)
	{
		if (!walk_v->next)
		{
			xy[0] = vv_to_v(cords.x, cords.y, walk_v->xy1.x, walk_v->xy1.y);
			xy[1] = vv_to_v(cords.x, cords.y, walk_v->xy2.x, walk_v->xy2.y);
		}
		else
		{
			xy[0] = vv_to_v(cords.x, cords.y, walk_v->xy1.x, walk_v->xy1.y);
			xy[1] = vv_to_v(cords.x, cords.y, walk_v->next->xy1.x, walk_v->next->xy1.y);
		}
		curr_angle = radian_to_grades(acosf(angle_vv(scalar_product(xy[0], xy[1]), len_vector(xy[0]), len_vector(xy[1]))));
		if (vector_product(xy[0], xy[1]) > 0)
			sum_angles += curr_angle;
		else
			sum_angles -= curr_angle;
		walk_v = walk_v->next;
	}
	if ((sum_angles >= 359.0 && sum_angles <= 361.0))
		return (1);
	return (0);
}
