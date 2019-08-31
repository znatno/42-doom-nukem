/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopolonc <vopolonc@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 14:07:18 by vopolonc          #+#    #+#             */
/*   Updated: 2019/08/31 14:07:24 by vopolonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke_nukem_editor.h"

void	mouse_event(t_env *env, t_draw *draw, t_stack **head)
{
	SDL_GetMouseState(&env->mouse_x, &env->mouse_y);
	if (draw->ev.button.clicks && env->mouse_x < W_DRAW - 20
		&& env->mouse_y < H_DRAW - 20 && env->mouse_y > 15 &&
		env->mouse_x > 15 && !draw->s_mode)
	{
		draw_dot(env, draw, head);
	}
	if (draw->s_mode && !draw->w_mode && draw->save && OBJ_COND)
		OBJ = OBJ == 0;
	else if ((draw->s_mode && !draw->w_mode && draw->save && ACT_COND))
		ACT = ACT == 0;
	draw_select_text(draw, env);
	(draw->s_mode) ? select_sector_mode(env, draw, draw->cur_s, 0)
				: refresh_screen(draw, env, head);
}

void	last_iteration(t_env *env, t_draw *draw)
{
	(DRAW_OBJ) ? draw_obj_and_action(env, draw->save) : 0 == 0;
	(draw->save && draw->head) ? draw_player(draw, env, draw->save) : 0 == 0;
	draw_frame(env);
	draw_tools(env);
}

void	choose_event_second(t_env *env, t_draw *draw, t_stack **head)
{
	if (K_R && draw->s_mode && !draw->w_mode && (draw->head != NULL))
		sector_selection_right(env, draw);
	else if (K_R && draw->w_mode && !draw->d_mode && draw->s_mode && N_H)
		wall_selection_right(env, draw);
	else if (K_U && WALL_MOD_CONDITION && draw->cur_v > 1)
		select_texture_up(env, draw);
	else if (K_U && draw->floor_mode && draw->s_mode && (draw->head != NULL))
		select_floor_up(env, draw);
	else if (K_D && draw->floor_mode && draw->s_mode && draw->head != NULL)
		select_floor_down(env, draw);
	else if (K_U && draw->ceil_mode && draw->s_mode && draw->head)
		select_ceil_up(env, draw);
	else if (K_D && draw->ceil_mode && draw->s_mode && draw->head)
		select_ceil_down(env, draw);
}

void	choose_event(t_env *env, t_draw *draw, t_stack **head)
{
	if (draw->kstate[SDL_SCANCODE_ESCAPE] || draw->ev.type == SDL_QUIT)
	{
		(N_H) ? record_data(transform_data(draw)) : 0;
		(*head) ? free_stack(head) : 0;
		draw->loop = 0;
	}
	else if (draw->kstate[SDL_SCANCODE_SPACE] && !draw->s_mode)
		finish_sector_space(draw, env, head);
	else if (draw->kstate[SDL_SCANCODE_DELETE])
		delete_sector_del(env, draw, head);
	else if (draw->kstate[SDL_SCANCODE_BACKSPACE] && !draw->s_mode)
		delete_line_backspace(env, draw, head);
	else if (K_ENTER && draw->save && draw->head && draw->s_mode)
		player_placement_return(env, draw);
	(draw->loop) ? choose_event_second(env, draw, head) : 0 == 0;
}
