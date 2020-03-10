/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_managing_c.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopolonc <vopolonc@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 14:59:08 by vopolonc          #+#    #+#             */
/*   Updated: 2019/08/31 14:59:11 by vopolonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke_nukem_editor.h"

t_portals		*malloc_portal_first(t_portals *portal, t_vertex *data,
		t_sector *temp_s, t_sector *cur_s)
{
	portal->sec_a = cur_s;
	portal->sec_b = temp_s;
	portal->xy1 = data->xy1;
	portal->xy2 = data->xy2;
	return (portal);
}

void			new_portal(t_draw *draw, t_vertex *temp,
		t_sector *temp_s, t_sector *cur_s)
{
	t_portals	*portal;

	draw->p_count++;
	if (!draw->portals)
	{
		draw->portals = ft_memalloc(sizeof(t_portals));
		draw->portals = malloc_portal_first(draw->portals, temp, temp_s, cur_s);
		draw->portals->next = NULL;
	}
	else
	{
		portal = last_portal(draw);
		portal->next = ft_memalloc(sizeof(t_portals));
		portal = portal->next;
		portal->sec_a = cur_s;
		portal->sec_b = temp_s;
		portal->xy1 = temp->xy1;
		portal->xy2 = temp->xy2;
		portal->next = NULL;
	}
}

int				find_portal_for_draw(t_env *env, t_draw *draw,
		t_vertex *temp, t_sector *temp_s)
{
	t_sector	*cur_s;
	t_vertex	*cur_v;
	int			i;

	i = 0;
	cur_s = draw->head;
	while (cur_s && ++i)
	{
		cur_v = cur_s->vertexes;
		while (cur_v)
		{
			if (((temp->xy1.x == cur_v->xy1.x &&
				temp->xy1.y == cur_v->xy1.y &&
				temp->xy2.x == cur_v->xy2.x &&
				temp->xy2.y == cur_v->xy2.y)
				|| (temp->xy1.x == cur_v->xy2.x &&
					temp->xy1.y == cur_v->xy2.y &&
					temp->xy2.x == cur_v->xy1.x &&
					temp->xy2.y == cur_v->xy1.y)) && (cur_s != temp_s))
				return (1);
			cur_v = cur_v->next;
		}
		cur_s = cur_s->next;
	}
	return (0);
}
