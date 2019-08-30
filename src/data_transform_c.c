/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_transform_c.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 19:45:42 by ggavryly          #+#    #+#             */
/*   Updated: 2019/08/30 19:45:43 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke_nukem_editor.h"

int		find_smallest_x(t_sector *sector, int y, int x)
{
	t_sector	*walk_sec;
	t_vertex	*w_v;
	int			least_x;

	walk_sec = sector;
	least_x = 100000;
	while (walk_sec)
	{
		w_v = walk_sec->vertexes;
		while (w_v)
		{
			if (least_x > w_v->xy1.x && w_v->xy1.x > x && w_v->xy1.y == y)
				least_x = w_v->xy1.x;
			if (least_x > w_v->xy2.x && w_v->xy2.x > x && w_v->xy2.y == y)
				least_x = w_v->xy2.x;
			w_v = w_v->next;
		}
		walk_sec = walk_sec->next;
	}
	return (least_x);
}

t_xy_l	*init_vertex(t_xy_l *curr, int y, int lea_x, int index)
{
	curr = (t_xy_l *)malloc(sizeof(t_xy_l));
	curr->y = y;
	curr->x = lea_x;
	curr->index = index;
	curr->next = NULL;
	curr->tail = NULL;
	return (curr);
}

t_xy_l	*create_vertex(t_sector *sector, int y)
{
	t_xy_l		*head;
	t_xy_l		*curr;
	t_xy_l		*pre;
	static int	index;
	int			lea_x;

	lea_x = -1;
	head = NULL;
	curr = NULL;
	while ((lea_x = find_smallest_x(sector, y, lea_x)) && (lea_x != 100000))
	{
		curr = init_vertex(curr, y, lea_x, index);
		if (head == NULL)
			head = curr;
		else
			pre->next = curr;
		pre = curr;
		index++;
	}
	if (head)
		head->tail = curr;
	return (head);
}

int		find_smallest_y(t_sector *sector, t_record *rec)
{
	t_sector	*walk_sec;
	t_vertex	*walk_ver;
	int			least_y;

	walk_sec = sector;
	least_y = -1;
	while (walk_sec)
	{
		walk_ver = walk_sec->vertexes;
		while (walk_ver)
		{
			if (walk_ver->xy1.y < rec->least_y && walk_ver->xy1.y > least_y)
				least_y = walk_ver->xy1.y;
			if (walk_ver->xy1.y < rec->least_y && walk_ver->xy1.y > least_y)
				least_y = walk_ver->xy2.y;
			walk_ver = walk_ver->next;
		}
		walk_sec = walk_sec->next;
	}
	return (least_y);
}

int		get_index(t_xy ab, t_xy_l *list)
{
	t_xy_l	*walk;

	walk = list;
	while (walk)
	{
		if (ab.x == walk->x && ab.y == walk->y)
			return (walk->index);
		walk = walk->next;
	}
	return (-1);
}
