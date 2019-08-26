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

void	print_list_vec(t_xy_l *head)
{
	t_xy_l	*walk;

	walk = head;
	while (walk)
	{
		printf("*************\n");
		printf("*x=%3d|y=%3d* # index == %d\n", walk->x, walk->y, walk->index);
		printf("*************\n");
		printf(" \\   |     /\n");
		printf("  \\  |   /\n");
		printf("   \\ | /\n");
		printf("    \\|/\n");
		printf("     |\n");
		printf("     v\n");
		walk = walk->next;
	}
}

void	print_list_sec(t_record *rec)
{
	t_rec_sec	*walk_sec;
	t_index		*walk_ver;

	walk_sec = rec->head_sec;
	while (walk_sec)
	{
		walk_ver = walk_sec->head_ind;
		while (walk_ver)
		{
			printf("*************\n");
			printf("*index = %3d*\n", walk_ver->index);
			printf("*************\n");
			printf(" \\   |     /\n");
			printf("  \\  |   /\n");
			printf("   \\ | /\n");
			printf("    \\|/\n");
			printf("     |\n");
			printf("     v\n");
			walk_ver = walk_ver->next;
		}
		printf("---------------------\n");
		printf("---------------------\n");
		walk_sec = walk_sec->next;
	}
}

int		find_smallest_x(t_sector *sector, int y, int x)
{
	t_sector	*walk_sec;
	t_vertex	*walk_ver;
	int 		least_x;

	walk_sec = sector;
	least_x = 100000;
	while (walk_sec)
	{
		walk_ver = walk_sec->vertexes;
		while (walk_ver)
		{
			if (least_x > walk_ver->xy1.x && walk_ver->xy1.x > x && walk_ver->xy1.y == y)
				least_x = walk_ver->xy1.x;
			if (least_x > walk_ver->xy2.x && walk_ver->xy2.x > x && walk_ver->xy2.y == y)
				least_x = walk_ver->xy2.x;
			walk_ver = walk_ver->next;
		}
		walk_sec = walk_sec->next;
	}
	return (least_x);
}

t_xy_l	*create_vertex(t_sector *sector, int y)
{
	t_xy_l		*head;
	t_xy_l		*curr;
	t_xy_l		*pre;
	static int 	index;
	int 		least_x_curr;

	least_x_curr = -1;
	head = NULL;
	while ((least_x_curr = find_smallest_x(sector, y,least_x_curr)) && (least_x_curr != 100000))
	{
			curr = (t_xy_l *)malloc(sizeof(t_xy_l));
			curr->y = y;
			curr->x = least_x_curr;
			curr->index = index;
			curr->next = NULL;
			curr->tail = NULL;
			if (head == NULL)
			{
				head = curr;
				head->next = NULL;
				pre = head;
			}
			else
			{
				pre->next = curr;
				pre = curr;
			}
			index++;
	}
	if (head)
		head->tail = curr;
	return (head);
}

int		find_smallest_y(t_sector *sector, t_record rec)
{
	t_sector	*walk_sec;
	t_vertex	*walk_ver;
	int 		least_y;

	walk_sec = sector;
	least_y = -1;
	while (walk_sec)
	{
		walk_ver = walk_sec->vertexes;
		while (walk_ver)
		{
			if (walk_ver->xy1.y < rec.least_y && walk_ver->xy1.y > least_y)
				least_y = walk_ver->xy1.y;
			if (walk_ver->xy1.y < rec.least_y && walk_ver->xy1.y > least_y)
				least_y = walk_ver->xy2.y;
			walk_ver = walk_ver->next;
		}
		walk_sec = walk_sec->next;
	}
	return (least_y);
}

t_record	*create_vertex_list(t_sector *sectors)
{
	t_xy_l		*curr;
	t_xy_l		*tail;
	t_xy_l		*head;
	t_record	*record;

	record = (t_record *)malloc(sizeof(t_record));
	head = NULL;
	curr = NULL;
	record->head_ver = NULL;
	record->least_x = -1;
	record->least_y = 100000;
	while((record->least_y = find_smallest_y(sectors, *record)) != -1)
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

int 	get_index_sec(t_sector *sec, t_sector *head_sec)
{
	t_sector	*walk_sec;
	int 	index;

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
}

int		choose_your_destiny(t_sector *sectors, t_rec_sec *curr, t_sector *a, t_sector *b)
{
	t_sector	*wals_s;
	int 		index;

	wals_s = sectors;
	index = 0;
	while (wals_s)
	{
		if (index == curr->index_s && a == wals_s)
			return (1);
		else if (index == curr->index_s && b == wals_s)
			return (2);
		wals_s = wals_s->next;
		index++;
	}
	return (-1);
}



int 	get_portal_index_sectors(t_portals *portals, t_xy a, t_xy b, t_sector *sectors, t_rec_sec *curr)
{
	t_portals	*walk_p;
	t_sector	*walk_s;
	t_portals 	*exist;
	int 		index;
	int 		tmp;

	walk_p = portals;
	exist = NULL;
	walk_s = sectors;
	while (walk_p)
	{
		if (a.x == walk_p->xy1.x && a.y == walk_p->xy1.y &&
		b.x == walk_p->xy2.x && b.y == walk_p->xy2.y)
			exist = walk_p;
		else if (a.x == walk_p->xy2.x && a.y == walk_p->xy2.y &&
				 b.x == walk_p->xy1.x && b.y == walk_p->xy1.y)
			exist = walk_p;
		if (exist)
			break;
		walk_p = walk_p->next;
	}
	while (exist && walk_s)
	{
		if (walk_s == walk_p->sec_b || walk_s == walk_p->sec_a)
		{
			tmp = choose_your_destiny(sectors, curr, walk_p->sec_a, walk_p->sec_b);
			if (tmp == 1)
				tmp = get_index_sec(walk_p->sec_b, sectors);
			else if (tmp == 2)
				tmp = get_index_sec(walk_p->sec_a, sectors);
			return (tmp);
		}
		walk_s = walk_s->next;
		index++;
	}
	return (-1);
}

t_portal	*end_to_head(t_portal *head_p)
{
	t_portal	*walk_p;
	t_portal	*prev;

	walk_p = head_p;
	prev = NULL;
	while (walk_p && walk_p->next)
	{
		prev = walk_p;
		walk_p = walk_p->next;
	}
	if (prev && walk_p)
	{
		prev->next = NULL;
		walk_p->next = head_p;
	}
	return (walk_p);
}

t_portal	*create_sector_portal_list(t_xy_l *head_vi, t_rec_sec *curr_s, t_portals *portals, t_sector *sectors)
{
	t_xy		a;
	t_xy		b;
	t_portal	*head;
	t_portal	*curr;
	t_portal	*prev;
	t_index		*walk_is;

	head = NULL;
	walk_is = curr_s->head_ind;
	while (walk_is && walk_is->next)
	{
		a = get_point_cords(walk_is->index, head_vi);
		b = get_point_cords(walk_is->next->index, head_vi);
		curr = (t_portal *)malloc(sizeof(t_portal));
		curr->next = NULL;
		curr->wall_portal = get_portal_index_sectors(portals, a, b, sectors, curr_s);
		if (head == NULL)
			head = curr;
		else
			prev->next = curr;
		prev = curr;
		walk_is = walk_is->next;
	}
	return (end_to_head(head));
}

t_index		*create_sector_edge_list(t_sector curr, t_record *rec)
{
	t_vertex	*walk;
	t_index		*head;
	t_index		*curr_i;
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
			head = (t_index *)malloc(sizeof(t_index));
			head->index = index[0];
			head->next = (t_index *)malloc(sizeof(t_index));
			head->next->next = NULL;
			head->next->index = index[1];
			pre = head->next;
		}
		else if (index[0] > -1 && index[1] > -1)
		{
			curr_i = (t_index *)malloc(sizeof(t_index));
			curr_i->next = NULL;
			curr_i->index = index[1];
			pre->next = curr_i;
			pre = curr_i;
		}
		walk = walk->next;
	}
	return (head);
}

t_vertex	*reverse_list(t_vertex *vertex)
{
	t_vertex	*curr;
	t_vertex	*next;
	t_vertex	*prev;

	curr = vertex;
	prev = NULL;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	return (prev);
}

t_rec_sec	*create_sector_list(t_sector *sectors, t_record *record, t_draw *d)
{
	t_sector	*walk_sec;
	t_rec_sec	*curr;
	t_rec_sec	*pre;
	t_rec_sec	*head;
	static int 	index;

	walk_sec = sectors;
	head = NULL;
	while (walk_sec)
	{
		curr = (t_rec_sec *)malloc(sizeof(t_rec_sec));
		curr->next = NULL;
		curr->head_por = NULL;
		curr->index_s = index;
		curr->head_ind = create_sector_edge_list(*walk_sec, record);
		curr->head_por = create_sector_portal_list(record->head_ver, curr, d->portals, d->head);
		curr->ceil = 20.0;
		curr->floor = 0.0;
		if (head == NULL)
			head = curr;
		else
			pre->next = curr;
		pre = curr;
		walk_sec= walk_sec->next;
		index++;
	}
	return (head);
}

int		sector_orientation(t_sector *curr_s)
{
	t_vertex	*needle;
	t_vertex	*walk_v;

	walk_v = curr_s->vertexes;
	needle = NULL;
	while (walk_v)
	{
		if (walk_v->xy1.x != walk_v->xy2.x)
			needle = walk_v;
		walk_v = walk_v->next;
	}
	if (needle)
	{
		if (needle->xy1.x > needle->xy2.x)
			return (0);
		else if (needle->xy1.x < needle->xy2.x)
			return (1);
	}
	return (-1);
}

void		transform_sectors_list(t_sector *head_s)
{
	t_sector	*walk_s;

	walk_s = head_s;
	while (walk_s)
	{
		 if (sector_orientation(walk_s) == 1)
		 	walk_s->vertexes = reverse_list(walk_s->vertexes);
		walk_s = walk_s->next;
	}
}

t_record	*transform_data(t_draw *draw)
{
	t_record	*record;
	t_sector    *head_s;

	head_s = draw->head;
	record = create_vertex_list(head_s);
	print_list_vec(record->head_ver);
	transform_sectors_list(head_s);
	record->head_sec = create_sector_list(head_s, record, draw);
	return (record);
//	print_list_sec(record);
}
