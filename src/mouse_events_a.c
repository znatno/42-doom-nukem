/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events_a.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 22:44:37 by ggavryly          #+#    #+#             */
/*   Updated: 2019/08/30 22:44:38 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke_nukem_editor.h"

int		click_to_text(t_env *env)
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

void	draw_player(t_draw *draw, t_env *env, t_sector *save)
{
	(draw->player == save) ?
	draw_texture(env->textures->cords[PLAYER], PLAYER, 0xf98d8d, env)
	: draw_texture(env->textures->cords[PLAYER],
			PLAYER, 0xffffff, env);
}

void	draw_obj(t_sector *save, t_env *env, int texture)
{
	if (save->object[texture % 10] == 1)
		draw_texture(env->textures->cords[texture], texture, 0xf98d8d, env);
	else
		draw_texture(env->textures->cords[texture], texture, 0xffffff, env);
}

void	draw_act(t_sector *save, t_env *env, int texture)
{
	if (save->action[(texture - SHIFT) % 10] == 1)
		draw_texture(env->textures->cords[texture], texture, 0xf98d8d, env);
	else
		draw_texture(env->textures->cords[texture], texture, 0xffffff, env);
}

void	draw_obj_and_action(t_env *env, t_sector *save)
{
	draw_obj(save, env, GUNS_OBJ);
	draw_obj(save, env, KITS_OBJ);
	draw_obj(save, env, ARMOR_OBJ);
	draw_act(save, env, DEATH_ACT);
	draw_act(save, env, FLY_ACT);
	draw_act(save, env, MIXED_ACT);
}
