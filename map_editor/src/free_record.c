/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_record.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopolonc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 20:07:20 by vopolonc          #+#    #+#             */
/*   Updated: 2019/08/31 20:07:21 by vopolonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke_nukem_editor.h"

void	record_free_vert(t_record *record)
{
	t_xy_l		*next_v;
	t_xy_l		*walk_v;

	walk_v = record->head_ver;
	next_v = NULL;
	if (walk_v)
		next_v = walk_v->next;
	while (next_v)
	{
		free(walk_v);
		walk_v = next_v;
		next_v = walk_v->next;
	}
	free(walk_v);
}

void	record_free_sec_index(t_rec_sec *rec_sec)
{
	t_index		*next_i;
	t_index		*walk_i;

	walk_i = rec_sec->head_ind;
	next_i = NULL;
	if (walk_i)
		next_i = walk_i->next;
	while (next_i)
	{
		free(walk_i);
		walk_i = next_i;
		next_i = walk_i->next;
	}
	free(walk_i);
}

void	record_free_sec_portal(t_rec_sec *rec_sec)
{
	t_portal	*next_p;
	t_portal	*walk_p;

	walk_p = rec_sec->head_por;
	next_p = NULL;
	if (walk_p)
		next_p = walk_p->next;
	while (next_p)
	{
		free(walk_p);
		walk_p = next_p;
		next_p = walk_p->next;
	}
	free(walk_p);
}

void	record_free_rec_sec(t_record *record)
{
	t_rec_sec	*next_r;
	t_rec_sec	*walk_r;

	walk_r = record->head_sec;
	next_r = NULL;
	if (walk_r)
		next_r = walk_r->next;
	while (next_r)
	{
		record_free_sec_index(walk_r);
		record_free_sec_portal(walk_r);
		free(walk_r);
		walk_r = next_r;
		next_r = walk_r->next;
	}
	record_free_sec_index(walk_r);
	record_free_sec_portal(walk_r);
	free(walk_r);
}

void	record_free(t_record *record)
{
	record_free_vert(record);
	record_free_rec_sec(record);
	free(record);
}
