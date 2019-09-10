/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopolonc <vopolonc@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 14:25:19 by vopolonc          #+#    #+#             */
/*   Updated: 2019/08/31 14:25:23 by vopolonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke_nukem_editor.h"

void	free_stack(t_stack **head)
{
	while (*head)
		stack_pop(head);
}

t_draw	*init_draw(t_draw *draw)
{
	if (!(draw = (t_draw *)malloc(sizeof(t_draw))))
		exit(13);
	I = 0;
	draw->temp.x = 0;
	draw->temp.y = 0;
	draw->head = NULL;
	draw->portals = NULL;
	draw->loop = 1;
	draw->place_p.sect_p = NULL;
	draw->place_p.x = 0;
	draw->place_p.y = 0;
	draw->s_mode = false;
	draw->d_mode = false;
	draw->ceil_mode = false;
	draw->floor_mode = false;
	draw->w_mode = false;
	draw->save_v = NULL;
	draw->s_count = 0;
	draw->p_count = 0;
	draw->save = NULL;
	draw->cur_s = 0;
	draw->cur_v = 0;
	return (draw);
}

void	init_vars(t_env *env)
{
	env->sdl_error = NONE;
}

void	finish_sector_space(t_draw *draw, t_env *env, t_stack **head)
{
	draw->key = SPACE;
	if (stack_more_than_two(head))
	{
		draw_dot(env, draw, head);
		refresh_screen(draw, env, head);
	}
	draw->key = 0;
}
