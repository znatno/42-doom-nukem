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
	while (i < 10)
	{
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

void	draw_select_text(t_env *env)
{
	int	text_select;

	text_select = click_to_text(env);

	if (text_select > -1)
	{
		if (env->textures->pre >= 0)
			draw_texture(env->textures->cords[env->textures->pre], env->textures->pre, 0xffffff, env);
		env->textures->selected = text_select;
		draw_texture(env->textures->cords[text_select], text_select, 0xf98d8d, env);
		env->textures->pre = text_select;
		SDL_UpdateWindowSurface(env->window);
	}
	env->mouse_x = -1;
	env->mouse_y = -1;
	printf("mouse_x - %d| mouse_y - %d\n", env->mouse_x, env->mouse_y);
}
