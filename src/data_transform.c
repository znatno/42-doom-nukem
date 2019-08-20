/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_transform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 16:22:51 by ggavryly          #+#    #+#             */
/*   Updated: 2019/08/19 16:22:53 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke_nukem_editor.h"

int		find_smallest_x(t_sector *sector, int y, t_record rec)
{
	t_sector	*walk_sec;
	t_vertex	*walk_ver;
	int 		least_x;

	walk_sec = sector;
	least_x = 100000000;
	while (walk_sec)
	{
		walk_ver = walk_sec->vertexes;
		while (walk_ver)
		{
			if (least_x > walk_ver->xy1.x && walk_ver->xy1.y == y && rec.least_x > least_x)
				least_x = walk_ver->xy1.x;
			if (least_x > walk_ver->xy2.x && walk_ver->xy2.y == y && rec.least_x > least_x)
				least_x = walk_ver->xy2.x;
			walk_ver = walk_ver->next;
		}
		walk_sec = walk_sec->next;
	}
	return (-1);
}

int		find_smallest_y(t_sector *sector, t_record rec)
{
	t_sector	*walk_sec;
	t_vertex	*walk_ver;
	int 		least_y;

	walk_sec = sector;
	least_y = 1000000000;
	while (walk_sec)
	{
		walk_ver = walk_sec->vertexes;
		while (walk_ver)
		{
			if (least_y > walk_ver->xy1.y && rec.least_y > least_y)
				least_y = walk_ver->xy1.y;
			if (least_y > walk_ver->xy2.y && rec.least_y > least_y)
				least_y = walk_ver->xy2.y;
			walk_ver = walk_ver->next;
		}
		walk_sec = walk_sec->next;
	}
	return (-1);
}

t_record	*create_vertex_list(t_sector *sectors)
{
	t_xy_l		*curr;
	t_xy_l		*last;
	t_sector	*walk;
	t_record	*record;

	walk = sectors;
	record = (t_record *)malloc(sizeof(t_record));
	record->head_ver = NULL;
	record->least_x = -1;
	record->least_y = -1;
	while(walk)
	{
		record->least_y = find_smallest_y(sectors, *record);
		record->least_x = find_smallest_x(sectors, record->least_y, *record);
		if (record->least_y >= 0 && record->least_x >= 0)
		{
			curr = (t_xy_l *)malloc(sizeof(t_xy_l));
			curr->y = record->least_y;
			curr->x = record->least_x;
			curr->next = NULL;
			if (record->head_ver == NULL)
			{
				curr->index = 0;
				record->head_ver = curr;
			}
			else
			{
				curr->index = last->index + 1;
				last->next = curr;
			}
			last = curr;
		}
		walk = walk->next;
	}
	return (record);
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

t_portal	*create_sector_portal_list(t_sector curr, t_record *rec)
{

}

t_index		*create_sector_edge_list(t_sector curr, t_record *rec)
{
	t_vertex	*walk;
	t_index		*in_l;
	t_index		*pre;
	int			index[2];


	walk = curr.vertexes;
	pre = NULL;
	while (walk)
	{
		index[0] = get_index(walk->xy1, rec->head_ver);
		index[1] = get_index(walk->xy2, rec->head_ver);
		if (index[0] > -1 && index[1] > -1 && pre == NULL)
		{
			in_l = (t_index *)malloc(sizeof(t_index));
			in_l->index = index[0];
			in_l->next = (t_index *)malloc(sizeof(t_index));
			in_l->next->index = index[1];
			pre = in_l->next;
		}
		else if (index[0] > -1 && index[1] > -1)
		{
			pre->next = (t_index *)malloc(sizeof(t_index));
			pre->index = index[1];
		}
		walk = walk->next;
	}

}

t_rec_sec	*create_sector_list(t_sector *sectors, t_record *record)
{
	t_sector	*walk_sec;
	t_vertex	*walk_ver;
	t_rec_sec	*rec_sec;

	walk_sec = sectors;
	rec_sec = (t_rec_sec *)malloc(sizeof(t_rec_sec));
	while (walk_sec)
	{
		walk_ver = walk_sec->vertexes;
		while (walk_ver)
		{
			rec_sec->head_ver = create_sector_edge_list(*walk_sec, record);
			rec_sec->head_por = create_sector_portal_list(*walk_sec, record);
			rec_sec->ceil = 20;
			rec_sec->floor = 0;
			walk_ver = walk_ver->next;
		}
		walk_sec = walk_sec->next;
	}

}

void	transform_data(t_sector *sectors)
{
	t_record	*record;

	record = create_vertex_list(sectors);
	record->head_sec = create_sector_list(sectors, record);


}
