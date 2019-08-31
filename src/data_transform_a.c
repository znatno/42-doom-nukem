/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_transform_a.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 19:45:27 by ggavryly          #+#    #+#             */
/*   Updated: 2019/08/30 19:45:28 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke_nukem_editor.h"

void			init_new(t_index **head, t_index **pre,
		t_index **curr_i, int index[2])
{
	if (index[0] > -1 && index[1] > -1 && *pre == NULL)
	{
		*head = (t_index *)malloc(sizeof(t_index));
		(*head)->index = index[0];
		(*head)->next = (t_index *)malloc(sizeof(t_index));
		(*head)->next->next = NULL;
		(*head)->next->index = index[1];
		(*pre) = (*head)->next;
	}
	else if (index[0] > -1 && index[1] > -1)
	{
		(*curr_i) = (t_index *)malloc(sizeof(t_index));
		(*curr_i)->next = NULL;
		(*curr_i)->index = index[1];
		(*pre)->next = *curr_i;
		(*pre) = *curr_i;
	}
}

t_index			*create_sector_edge_list(t_sector curr, t_record *rec)
{
	t_vertex	*walk;
	t_index		*head;
	t_index		*curr_i;
	t_index		*pre;
	int			index[2];

	walk = curr.vertexes;
	pre = NULL;
	head = NULL;
	curr_i = NULL;
	while (walk)
	{
		index[0] = get_index(walk->xy1, rec->head_ver);
		index[1] = get_index(walk->xy2, rec->head_ver);
		init_new(&head, &pre, &curr_i, index);
		walk = walk->next;
	}
	return (head);
}

t_rec_sec		*init_sector(t_rec_sec *c, t_sector *walk,
		t_record *r, t_draw *d)
{
	c = (t_rec_sec *)malloc(sizeof(t_rec_sec));
	c->next = NULL;
	c->head_por = NULL;
	c->head_ind = create_sector_edge_list(*walk, r);
	c->head_por = portal_list(r->head_ver, c, d->portals, d->head);
	c->ceil = walk->ceil;
	c->floor = walk->floor;
	return (c);
}

t_rec_sec		*create_sector_list(t_sector *sectors, t_record *r, t_draw *d)
{
	t_sector	*walk_sec;
	t_rec_sec	*curr;
	t_rec_sec	*pre;
	t_rec_sec	*head;
	static int	index;

	walk_sec = sectors;
	head = NULL;
	pre = NULL;
	curr = NULL;
	while (walk_sec)
	{
		curr = init_sector(curr, walk_sec, r, d);
		curr->index_s = index;
		if (head == NULL)
			head = curr;
		else
			pre->next = curr;
		pre = curr;
		walk_sec = walk_sec->next;
		index++;
	}
	return (head);
}

t_record		*transform_data(t_draw *draw)
{
	t_record	*record;
	t_sector	*head_s;

	head_s = draw->head;
	record = create_vertex_list(head_s);
	record->head_sec = create_sector_list(head_s, record, draw);
	record->player_sec = get_index_sec(draw->place_p.sect_p, draw->head);
	record->player_x = draw->place_p.x;
	record->player_y = draw->place_p.y;
	return (record);
}
