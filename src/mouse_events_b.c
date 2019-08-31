/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 22:44:40 by ggavryly          #+#    #+#             */
/*   Updated: 2019/08/30 22:44:47 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke_nukem_editor.h"

void	init_mode(t_mode mode, t_draw **draw, t_env *env, int text_select)
{
	(*draw)->ceil_mode = mode.ceil_mode;
	(*draw)->floor_mode = mode.floor_mode;
	(*draw)->d_mode = mode.d_mode;
	draw_texture(env->textures->cords[text_select], text_select, 0xf98d8d, env);
}

void	draw_any_mode(t_draw **draw, t_env *env, int text_select)
{
	if (text_select == 8)
	{
		env->textures->selected = text_select;
		(*draw)->s_mode = 1;
		(*draw)->w_mode = 0;
		(*draw)->d_mode = 0;
		if ((*draw)->s_mode)
			draw_texture(env->textures->cords[text_select], text_select,
					0xf98d8d, env);
	}
	if (text_select == 1)
	{
		env->textures->selected = text_select;
		(*draw)->s_mode = 0;
		(*draw)->w_mode = 0;
		(*draw)->d_mode = 1;
		(*draw)->ceil_mode = false;
		(*draw)->floor_mode = false;
		if ((*draw)->s_mode)
			draw_texture(env->textures->cords[text_select], text_select,
					0xf98d8d, env);
	}
}

void	end_select(t_env **env, int text_select)
{
	if (text_select > -1 && text_select <= 9 && text_select != 5)
	{
		(*env)->textures->selected = text_select;
		draw_texture((*env)->textures->cords[text_select], text_select,
				0xf98d8d, *env);
	}
	(*env)->mouse_x = -1;
	(*env)->mouse_y = -1;
}

void	draw_select_text(t_draw *draw, t_env *env)
{
	int	text_select;

	text_select = click_to_text(env);
	if (text_select == CEIL && draw->s_mode && !draw->d_mode && !draw->w_mode)
		init_mode((t_mode){.ceil_mode = true, .floor_mode = false,
					.d_mode = false}, &draw, env, text_select);
	if (text_select == FLOOR && draw->s_mode && !draw->d_mode && !draw->w_mode)
		init_mode((t_mode){.ceil_mode = false, .floor_mode = true,
					.d_mode = false}, &draw, env, text_select);
	draw_any_mode(&draw, env, text_select);
	if (text_select == WALL_MODE && draw->s_mode && !draw->d_mode)
	{
		draw->w_mode = true;
		draw->d_mode = false;
		draw->s_mode = true;
		draw->ceil_mode = false;
		draw->floor_mode = false;
		draw_texture(env->textures->cords[text_select], text_select,
					0xf98d8d, env);
	}
	end_select(&env, text_select);
}
