/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_transform_b.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 19:45:38 by ggavryly          #+#    #+#             */
/*   Updated: 2019/08/30 19:45:40 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke_nukem_editor.h"

int			a_or_b(t_sector *sectors, t_rec_sec *curr, t_sector *a, t_sector *b)
{
	t_sector	*wals_s;
	int			index;

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

int			portal_exist(t_portals *e, t_portals *p, t_sector *s, t_rec_sec *c)
{
	int			tmp;
	int			index;
	t_sector	*walk_s;

	index = 0;
	walk_s = s;
	while (e && walk_s)
	{
		if (walk_s == p->sec_b || walk_s == p->sec_a)
		{
			tmp = a_or_b(s, c, p->sec_a, p->sec_b);
			if (tmp == 1)
				tmp = get_index_sec(p->sec_b, s);
			else if (tmp == 2)
				tmp = get_index_sec(p->sec_a, s);
			return (tmp);
		}
		walk_s = walk_s->next;
		index++;
	}
	return (-1);
}

int			portal_index(t_portals *p, t_xy *ab, t_sector *s, t_rec_sec *c)
{
	t_portals	*walk_p;
	t_portals	*exist;

	walk_p = p;
	exist = NULL;
	while (walk_p)
	{
		if (ab[0].x == walk_p->xy1.x && ab[0].y == walk_p->xy1.y &&
		ab[1].x == walk_p->xy2.x && ab[1].y == walk_p->xy2.y)
			exist = walk_p;
		else if (ab[0].x == walk_p->xy2.x && ab[0].y == walk_p->xy2.y &&
		ab[1].x == walk_p->xy1.x && ab[1].y == walk_p->xy1.y)
			exist = walk_p;
		if (exist)
			break ;
		walk_p = walk_p->next;
	}
	return (portal_exist(exist, walk_p, s, c));
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

t_portal	*portal_list(t_xy_l *h, t_rec_sec *c, t_portals *p, t_sector *s)
{
	t_xy		ab[2];
	t_portal	*head;
	t_portal	*curr;
	t_portal	*prev;
	t_index		*walk_is;

	head = NULL;
	walk_is = c->head_ind;
	prev = NULL;
	while (walk_is && walk_is->next)
	{
		ab[0] = get_point_cords(walk_is->index, h);
		ab[1] = get_point_cords(walk_is->next->index, h);
		curr = (t_portal *)malloc(sizeof(t_portal));
		curr->next = NULL;
		curr->wall_portal = portal_index(p, ab, s, c);
		if (head == NULL)
			head = curr;
		else
			prev->next = curr;
		prev = curr;
		walk_is = walk_is->next;
	}
	return (end_to_head(head));
}
