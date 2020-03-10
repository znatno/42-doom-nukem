/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_func2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprokysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 15:11:14 by tprokysh          #+#    #+#             */
/*   Updated: 2019/09/06 15:11:15 by tprokysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int			check_file(int fd)
{
	if (fd == -1 || read(fd, 0, 0) < 0)
	{
		ft_putstr("empty file or it's directory\n");
		return (0);
	}
	return (1);
}

void		*ft_realloc(void *ptr, size_t size)
{
	char *newptr;

	if (!size && ptr)
	{
		if (!(newptr = (char *)malloc(1)))
			return (NULL);
		ft_memdel(&ptr);
		return (newptr);
	}
	if (!(newptr = (char *)malloc(size)))
		return (NULL);
	if (ptr)
	{
		ft_memcpy(newptr, ptr, size);
		ft_memdel(&ptr);
	}
	return (newptr);
}

t_posf		atof_posf(const char *s, t_posf posf, int exp)
{
	int c;
	int sign;
	int i;

	exp = 0;
	sign = 1;
	i = posf.pos;
	posf.value = 0.0;
	if (s[0 + posf.pos] == '-' && posf.pos++)
		sign = -1;
	while ((c = s[0 + posf.pos++]) != '\0' && ISDIGIT(c))
		posf.value = posf.value * 10.0 + (c - '0');
	if (c == '.')
		while (((c = s[0 + posf.pos++]) != '\0' && ISDIGIT(c)) || exp--)
			posf.value = posf.value * 10.0 + (c - '0');
	while (ISDIGIT(c))
	{
		i = i * 10 + (c - '0');
		c = s[0 + posf.pos++];
	}
	while (exp++ < 0)
		posf.value *= 0.1;
	posf.value *= sign;
	return (posf);
}

int			inter_point(unsigned int s, t_sector **sc, t_player *plr)
{
	if (surface_in((t_math) {.x0 = plr->where.x, .y0 = plr->where.y,
			.x1 = plr->where.x + plr->vlct.x,
			.y1 = plr->where.y + plr->vlct.y,
			.x2 = (*sc)->vert[s + 0].x,
			.y2 = (*sc)->vert[s + 0].y,
			.x3 = (*sc)->vert[s + 1].x,
			.y3 = (*sc)->vert[s + 1].y})
		&& point_basis((t_math) {.px = plr->where.x + plr->vlct.x,
			.py = plr->where.y + plr->vlct.y,
			.xx0 = (*sc)->vert[s + 0].x,
			.yy0 = (*sc)->vert[s + 0].y,
			.xx1 = (*sc)->vert[s + 1].x,
			.yy1 = (*sc)->vert[s + 1].y}) < 0)
		return (1);
	return (0);
}
