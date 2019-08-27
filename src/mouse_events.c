/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 22:05:45 by ggavryly          #+#    #+#             */
/*   Updated: 2019/08/18 22:05:47 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke_nukem_editor.h"

int	click_to_text(t_env *env)
{
	int start[2];
	int end[2];
	int i;

	i = 0;
	while (i < 16)
	{
		if (i == LEFT || i == RIGHT)
			i += 1;
		start[X] = env->textures->cords[i].x;
		start[Y] = env->textures->cords[i].y;
		end[X] = env->textures->cords_end[i].x;
		end[Y] = env->textures->cords_end[i].y;
		if (env->mouse_x > start[X] && env->mouse_x < end[X] &&
			env->mouse_y > start[Y] && env->mouse_y < end[Y])
			return (i);
		i++;
	}
	return (-1);
}

void	draw_obj_and_action(t_draw *draw, t_env *env, t_sector *save)
{
		(save->object[GUNS_OBJ % 10] == 1) ? (draw_texture(env->textures->cords[GUNS_OBJ], GUNS_OBJ, 0xf98d8d,
														   env)) : (draw_texture(env->textures->cords[GUNS_OBJ],
																				 GUNS_OBJ, 0xffffff,
																				 env));
		(save->object[KITS_OBJ % 10] == 1) ? draw_texture(env->textures->cords[KITS_OBJ], KITS_OBJ, 0xf98d8d,
														  env) : draw_texture(env->textures->cords[KITS_OBJ], KITS_OBJ,
																			  0xffffff,
																			  env);
		(save->object[ARMOR_OBJ % 10] == 1) ? draw_texture(env->textures->cords[ARMOR_OBJ], ARMOR_OBJ, 0xf98d8d,
														   env) : draw_texture(env->textures->cords[ARMOR_OBJ],
																			   ARMOR_OBJ, 0xffffff,
																			   env);
		(save->action[(DEATH_ACT - SHIFT) % 10] == 1) ? draw_texture(env->textures->cords[DEATH_ACT], DEATH_ACT,
																	 0xf98d8d,
																	 env) : draw_texture(
				env->textures->cords[DEATH_ACT], DEATH_ACT, 0xffffff,
				env);
		(save->action[(FLY_ACT - SHIFT) % 10] == 1) ? draw_texture(env->textures->cords[FLY_ACT], FLY_ACT, 0xf98d8d,
																   env) : draw_texture(env->textures->cords[FLY_ACT],
																					   FLY_ACT, 0xffffff,
																					   env);
		(save->action[(MIXED_ACT - SHIFT) % 10] == 1) ? draw_texture(env->textures->cords[MIXED_ACT], MIXED_ACT,
																	 0xf98d8d,
																	 env) : draw_texture(
				env->textures->cords[MIXED_ACT], MIXED_ACT, 0xffffff,
				env);
}


void	draw_select_text(t_draw *draw, t_env *env)
{
	int	text_select;

	text_select = click_to_text(env);

	if (text_select == CEIL && draw->s_mode && !draw->d_mode && !draw->w_mode)
	{
		draw->ceil_mode = true;
		draw->floor_mode = false;
		draw->d_mode = false;
		draw_texture(env->textures->cords[text_select], text_select, 0xf98d8d,
					 env);
	}
	if (text_select == FLOOR && draw->s_mode && !draw->d_mode && !draw->w_mode)
	{
		draw->ceil_mode = false;
		draw->floor_mode = true;
		draw->d_mode = false;
		draw_texture(env->textures->cords[text_select], text_select, 0xf98d8d, env);
	}
	if (text_select == 8)
	{
		env->textures->selected = text_select;
		draw->s_mode = 1;
		draw->w_mode = 0;
		draw->d_mode = 0;
		if (draw->s_mode)
			draw_texture(env->textures->cords[text_select], text_select, 0xf98d8d, env);
	}
	// CEIL

	// SELECT MODE ENDS
//	if (text_select == 9 && draw->s_mode)
//	{
//		env->textures->selected = text_select;
//		draw->d_mode = 1;
//		draw->s_mode = 0;
//		draw->w_mode = 0;
////		draw->ceil_mode = true;
////		draw->floor_mode = true
//		if (draw->d_mode)
//			draw_texture(env->textures->cords[text_select], text_select, 0xf98d8d, env);
//	}
	 if (text_select == 1)
	{
		env->textures->selected = text_select;
		draw->s_mode = 0;
		draw->w_mode = 0;
		draw->d_mode = 1;
		draw->ceil_mode = false;
		draw->floor_mode = false;
		if (draw->s_mode)
			draw_texture(env->textures->cords[text_select], text_select, 0xf98d8d, env);
	}
	if (text_select == WALL_MODE && draw->s_mode && !draw->d_mode)
	{
		printf("TEXT_SELECT_W_M: wall = %d select = %d draw %d\n", draw->s_mode, draw->w_mode, draw->d_mode);
		draw->w_mode = true;
		draw->d_mode = false;
		draw->s_mode = true;
		draw->ceil_mode = false;
		draw->floor_mode = false;
		draw_texture(env->textures->cords[text_select], text_select, 0xf98d8d,
					 env);
	}
	if (text_select > -1 && text_select <= 9)
	{

		env->textures->selected = text_select;
			draw_texture(env->textures->cords[text_select], text_select, 0xf98d8d, env);
	}
	env->mouse_x = -1;
	env->mouse_y = -1;
}
