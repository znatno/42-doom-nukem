/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_e.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopolonc <vopolonc@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 14:20:40 by vopolonc          #+#    #+#             */
/*   Updated: 2019/08/31 14:20:43 by vopolonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke_nukem_editor.h"

void	delete_sector_del(t_env *env, t_draw *draw, t_stack **head)
{
	delete_sector_from_list(env, draw);
	refresh_screen(draw, env, head);
}

void	player_placement_return(t_env *env, t_draw *draw)
{
	SDL_GetMouseState(&env->mouse_x, &env->mouse_y);
	draw->player = draw->save;
	draw->place_p.sect_p = draw->save;
	if (place_player((t_xyf) {.x = (float)env->mouse_x,
					.y = (float)env->mouse_y}, draw->save))
	{
		draw_texture((t_xy) {.x = env->mouse_x,
					.y = env->mouse_y}, PLAYER, 0xfffffff, env);
		draw->place_p.x = env->mouse_x / 10;
		draw->place_p.y = env->mouse_y / 10;
		select_sector_mode(env, draw, draw->cur_s, 0);
	}
}

void	sector_selection_right(t_env *env, t_draw *draw)
{
	char *ceil;
	char *floor;

	if (draw->s_count > 1)
		draw->cur_s += (draw->s_count > draw->cur_s) ? 1 : (-draw->cur_s + 1);
	else
		draw->cur_s = 1;
	draw->save = select_sector_mode(env, draw, draw->cur_s, 0);
	ceil = ft_itoa(draw->save->ceil);
	floor = ft_itoa(draw->save->floor);
	(draw->save) ? draw_text(1500, 305, ceil, env)
	: 0 == 0;
	(draw->save) ? draw_text(1500, 365, floor, env)
	: 0 == 0;
	free(ceil);
	free(floor);
}

void	wall_selection_right(t_env *env, t_draw *draw)
{
	char *ceil;
	char *floor;

	draw->save = select_sector_mode(env, draw, draw->cur_s, 0);
	(draw->cur_v > draw->save->walls) ? draw->cur_v = 1 : draw->cur_v;
	draw->save_v = save_vertex(env, draw->cur_v++, draw->save);
	ceil = ft_itoa(draw->save->ceil);
	floor = ft_itoa(draw->save->floor);
	draw_text(1500, 305, ceil, env);
	draw_text(1500, 365, floor, env);
	(draw->cur_v > 1) ? draw_wall(TEXTURE_COORDS,
			draw->save_v->texture, env) : 0 == 0;
	free(ceil);
	free(floor);
}

void	delete_line_backspace(t_env *env, t_draw *draw, t_stack **head)
{
	stack_pop(head);
	refresh_screen(draw, env, head);
}
