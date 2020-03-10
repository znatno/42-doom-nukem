/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_fts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibohun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:00:11 by ibohun            #+#    #+#             */
/*   Updated: 2019/08/20 23:16:09 by ibohun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	overflow(float a0, float a1, float b0, float b1)
{
	if (MIN(a0, a1) <= MAX(b0, b1) && MIN(b0, b1) <= MAX(a0, a1))
		return (true);
	return (false);
}

bool	surface_in(t_math m)
{
	bool result;

	result = (overflow(m.x0, m.x1, m.x2, m.x3)
			&& overflow(m.y0, m.y1, m.y2, m.y3));
	return (result);
}

float	point_basis(t_math m)
{
	float result;

	result = VXS((m.xx1) - (m.xx0), (m.yy1) - (m.yy0),
			(m.px) - (m.xx0), (m.py) - (m.yy0));
	return (result);
}

t_xy	crossing(t_math m)
{
	t_xy result;

	result = (t_xy){.x = VXS(VXS(m.xxx1, m.yyy1, m.xxx2, m.yyy2), (m.xxx1) -
				(m.xxx2), VXS(m.xxx3, m.yyy3, m.xxx4, m.yyy4), (m.xxx3) -
				(m.xxx4)) / VXS((m.xxx1) - (m.xxx2), (m.yyy1) - (m.yyy2),
						(m.xxx3) - (m.xxx4), (m.yyy3) - (m.yyy4)),
				.y = VXS(VXS(m.xxx1, m.yyy1, m.xxx2, m.yyy2),
						(m.yyy1) - (m.yyy2),
						VXS(m.xxx3, m.yyy3, m.xxx4, m.yyy4), (m.yyy3) - \
	(m.yyy4)) / VXS((m.xxx1) - (m.xxx2),
			(m.yyy1) - (m.yyy2), (m.xxx3) - (m.xxx4), (m.yyy3) - (m.yyy4))};
	return (result);
}
