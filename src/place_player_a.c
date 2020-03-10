/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_player_a.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 15:28:54 by ggavryly          #+#    #+#             */
/*   Updated: 2019/08/31 15:28:56 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke_nukem_editor.h"

float		len_vector(t_xyf free_vector)
{
	float res;

	res = sqrtf(powf(free_vector.x, 2) + powf(free_vector.y, 2));
	return (res);
}

float		scalar_product(t_xyf xy0, t_xyf xy1)
{
	float res;

	res = xy0.x * xy1.x + xy0.y * xy1.y;
	return (res);
}

float		angle_vv(float scalar_product, float len0, float len1)
{
	float res;

	res = scalar_product / (len0 * len1);
	return (res);
}

float		radian_to_grades(float rad)
{
	float res;

	res = roundf((180.0 / M_PI) * rad);
	return (res);
}

float		vector_product(t_xyf xy0, t_xyf xy1)
{
	float res;

	res = ((xy0.x) * (xy1.y) - (xy1.x) * (xy0.y));
	return (res);
}
