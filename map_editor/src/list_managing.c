/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_managing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopolonc <vopolonc@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 15:22:58 by vopolonc          #+#    #+#             */
/*   Updated: 2019/08/31 15:23:00 by vopolonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke_nukem_editor.h"

void			zero_objects(t_sector *cur_s, int i)
{
	cur_s->walls = i;
	ft_bzero(&cur_s->object, 3);
	ft_bzero(&cur_s->action, 3);
}

void			pop_from_stack_to_list(t_env *env,
		t_draw *draw, t_stack **head, int i)
{
	t_sector	*cur_s;
	t_vertex	*head_v;
	t_xy		cpf[2];

	cur_s = pop_helper(draw, cur_s);
	cpf[1] = stack_pop(head);
	cpf[0] = cpf[1];
	head_v = pop_helper_b(head_v, cpf, cur_s);
	while (cpf[0].x != -42 && ++i)
	{
		head_v->texture = TEXTURE_DEFAULT;
		head_v->xy1 = cpf[0];
		cpf[0] = stack_pop(head);
		if (cpf[0].x != -42)
			(head_v->xy2 = cpf[0]);
		else
			(head_v->xy2 = cpf[1]);
		(N_H_N) ? find_portal(env, draw, head_v, cur_s) : 0 == 0;
		if (cpf[0].x != -42)
		{
			head_v->next = ft_memalloc(sizeof(t_vertex));
			head_v = head_v->next;
		}
	}
	zero_objects(cur_s, i);
}

void			save_stack_to_list(t_env *env, t_draw *draw, t_stack **head)
{
	t_sector	*sect;

	if (!draw->head)
	{
		sect = ft_memalloc(sizeof(t_sector));
		draw->head = sect;
		malloc_list_first(sect);
	}
	else
	{
		sect = last_in_list(draw);
		sect->next = ft_memalloc(sizeof(t_sector));
		malloc_list(sect);
	}
	pop_from_stack_to_list(env, draw, head, 0);
	draw->s_count++;
}
