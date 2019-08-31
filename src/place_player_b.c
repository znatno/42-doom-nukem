/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_player_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 15:28:58 by ggavryly          #+#    #+#             */
/*   Updated: 2019/08/31 15:28:59 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke_nukem_editor.h"

t_xyf	vv_to_v(float x0, float y0, float x1, float y1)
{
	t_xyf	xy;

	xy.x = x1 - x0;
	xy.y = y1 - y0;
	return (xy);
}

void	init_free_vector(t_xyf *xy, t_xyf cords, t_vertex *walk_v)
{
	if (!walk_v->next)
	{
		xy[0] = vv_to_v(cords.x, cords.y, walk_v->xy1.x, walk_v->xy1.y);
		xy[1] = vv_to_v(cords.x, cords.y, walk_v->xy2.x, walk_v->xy2.y);
	}
	else
	{
		xy[0] = vv_to_v(cords.x, cords.y, walk_v->xy1.x, walk_v->xy1.y);
		xy[1] = vv_to_v(cords.x, cords.y, walk_v->next->xy1.x,
				walk_v->next->xy1.y);
	}
}

int		place_player(t_xyf cords, t_sector *sector)
{
	t_vertex	*walk_v;
	t_xyf		xy[2];
	float		sum_angles;
	float		curr_angle;

	sum_angles = 0.0;
	walk_v = sector->vertexes;
	while (walk_v)
	{
		init_free_vector(xy, cords, walk_v);
		curr_angle = radian_to_grades(
				acosf(angle_vv(
						scalar_product(xy[0], xy[1]),
						len_vector(xy[0]), len_vector(xy[1]))));
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
