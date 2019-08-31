/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_transform_d.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 20:43:11 by ggavryly          #+#    #+#             */
/*   Updated: 2019/08/30 20:43:15 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke_nukem_editor.h"

t_record	*init_value(t_record *record, t_xy_l **head, t_xy_l **curr)
{
	record = (t_record *)malloc(sizeof(t_record));
	*head = NULL;
	*curr = NULL;
	record->head_ver = NULL;
	record->least_x = -1;
	record->least_y = 100000;
	return (record);
}

t_record	*create_vertex_list(t_sector *sectors)
{
	t_xy_l		*curr;
	t_xy_l		*tail;
	t_xy_l		*head;
	t_record	*record;

	record = init_value(record, &head, &curr);
	while ((record->least_y = find_smallest_y(sectors, record)) != -1)
	{
		if (curr == NULL)
		{
			curr = create_vertex(sectors, record->least_y);
			tail = curr->tail;
			head = curr;
		}
		else
		{
			curr = create_vertex(sectors, record->least_y);
			tail->next = curr;
			tail = curr->tail;
		}
	}
	record->head_ver = head;
	return (record);
}

int			get_index_sec(t_sector *sec, t_sector *head_sec)
{
	t_sector	*walk_sec;
	int			index;

	index = 0;
	walk_sec = head_sec;
	while (walk_sec)
	{
		if (sec == walk_sec)
			return (index);
		walk_sec = walk_sec->next;
		index++;
	}
	return (-1);
}

t_xy		get_point_cords(int index, t_xy_l *head_vi)
{
	t_xy	result;
	t_xy_l	*walk_vi;

	walk_vi = head_vi;
	result.x = -1;
	result.y = -1;
	while (walk_vi)
	{
		if (index == walk_vi->index)
		{
			result.x = walk_vi->x;
			result.y = walk_vi->y;
			return (result);
		}
		walk_vi = walk_vi->next;
	}
	return (result);
}
