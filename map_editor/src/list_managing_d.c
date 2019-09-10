/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_managing_d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopolonc <vopolonc@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 15:07:35 by vopolonc          #+#    #+#             */
/*   Updated: 2019/08/31 15:07:38 by vopolonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke_nukem_editor.h"

t_sector		*last_in_list(t_draw *draw)
{
	t_sector *cur;

	cur = draw->head;
	while (cur && cur->next && (cur = cur->next))
		;
	return (cur);
}

void			delete_sector_from_list(t_env *env, t_draw *draw)
{
	t_sector	*cur_s;
	t_vertex	*cur_v;
	t_sector	*del_me;
	t_vertex	*tmp;

	if (!(cur_s = check_if_deleted_sector(draw, tmp, cur_v, cur_s)))
		return ;
	while (cur_s->next->next != NULL)
	{
		cur_s = cur_s->next;
	}
	cur_v = cur_s->next->vertexes;
	while (cur_v != NULL)
	{
		tmp = cur_v->next;
		free(cur_v);
		cur_v = tmp;
	}
	free_sect(draw, del_me, cur_s);
}

void			find_portal(t_env *env, t_draw *draw,
		t_vertex *temp, t_sector *temp_s)
{
	t_sector	*cur_s;
	t_vertex	*cur_v;

	cur_s = draw->head;
	while (cur_s)
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
				new_portal(draw, temp, temp_s, cur_s);
			cur_v = cur_v->next;
		}
		cur_s = cur_s->next;
	}
}

t_sector		*check_if_deleted_sector(t_draw *draw, t_vertex *tmp,
								t_vertex *cur_v, t_sector *cur_s)
{
	if (!(cur_s = draw->head))
		return (NULL);
	if (cur_s->next == NULL)
	{
		cur_v = cur_s->vertexes;
		while (cur_v != NULL)
		{
			tmp = cur_v->next;
			free(cur_v);
			cur_v = tmp;
		}
		free(cur_s);
		cur_s = NULL;
		draw->head = NULL;
		draw->s_count--;
		return (NULL);
	}
	return (cur_s);
}

void			free_sect(t_draw *draw, t_sector *del_me, t_sector *cur_s)
{
	del_me = cur_s->next;
	cur_s->next = NULL;
	draw->s_count--;
	free(del_me);
}
