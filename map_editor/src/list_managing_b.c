/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_managing_b.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopolonc <vopolonc@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 14:55:49 by vopolonc          #+#    #+#             */
/*   Updated: 2019/08/31 14:55:49 by vopolonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke_nukem_editor.h"

t_portals			*last_portal(t_draw *draw)
{
	t_portals		*cur;

	cur = draw->portals;
	while (cur->next)
		cur = cur->next;
	return (cur);
}

void				draw_all_portals(t_env *env, t_draw *draw)
{
	t_portals		*cur;

	cur = draw->portals;
	while (cur)
	{
		line(cur->xy1, cur->xy2, env, RED);
		cur = cur->next;
	}
}

void				del_if_portal(t_draw *draw, t_portals *head,
		t_portals *prev, t_portals *del_me)
{
	del_me = head->next;
	prev = del_me->next;
	head->next = prev;
	free(del_me);
}

void				del_cur_portal(t_draw *draw, t_portals *cur)
{
	t_portals		*head;
	t_portals		*del_me;
	t_portals		*prev;

	if (draw->p_count > 1 && draw->s_count > 1)
	{
		head = draw->portals;
		while (head->next != cur)
			head = head->next;
		del_if_portal(draw, head, prev, del_me);
	}
	else
	{
		del_me = draw->portals;
		draw->portals->next = NULL;
		free(del_me);
		draw->portals = NULL;
	}
	draw->p_count--;
}

void				delete_portal(t_draw *draw, t_vertex *cur_v)
{
	t_portals		*cur;

	cur = draw->portals;
	while (cur)
	{
		if (((cur->xy1.x == cur_v->xy1.x &&
			cur->xy1.y == cur_v->xy1.y &&
			cur->xy2.x == cur_v->xy2.x &&
			cur->xy2.y == cur_v->xy2.y)
			|| (cur->xy1.x == cur_v->xy2.x &&
				cur->xy1.y == cur_v->xy2.y &&
				cur->xy2.x == cur_v->xy1.x &&
				cur->xy2.y == cur_v->xy1.y)))
			del_cur_portal(draw, cur);
		cur = cur->next;
	}
}
