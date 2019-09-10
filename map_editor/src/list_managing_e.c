/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_managing_e.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopolonc <vopolonc@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 15:46:47 by vopolonc          #+#    #+#             */
/*   Updated: 2019/08/31 15:46:50 by vopolonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke_nukem_editor.h"

void			malloc_list(t_sector *sect)
{
	sect = sect->next;
	sect->vertexes = ft_memalloc(sizeof(t_vertex));
	sect->vertexes->next = NULL;
	sect->next = NULL;
}

void			malloc_list_first(t_sector *sect)
{
	sect->vertexes = ft_memalloc(sizeof(t_vertex));
	sect->vertexes->next = NULL;
	sect->next = NULL;
}

t_sector		*pop_helper(t_draw *draw, t_sector *cur_s)
{
	cur_s = last_in_list(draw);
	cur_s->floor = DEFAULT_FLOOR;
	cur_s->ceil = DEFAULT_CEIL;
	return (cur_s);
}

t_vertex		*pop_helper_b(t_vertex *head_v, t_xy cpf[2], t_sector *cur_s)
{
	head_v = cur_s->vertexes;
	head_v->xy1 = cpf[1];
	head_v->xy2 = cpf[0];
	return (head_v);
}
