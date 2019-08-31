/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopolonc <vopolonc@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 14:16:48 by vopolonc          #+#    #+#             */
/*   Updated: 2019/08/31 14:16:56 by vopolonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke_nukem_editor.h"

void	select_texture_up(t_env *env, t_draw *draw)
{
	(draw->save_v->texture < TEXTURE_MAX) ? draw->save_v->texture += 1 :
			(draw->save_v->texture = TEXTURE_DEFAULT);
	draw_wall(TEXTURE_COORDS, draw->save_v->texture, env);
}

void	select_floor_up(t_env *env, t_draw *draw)
{
	char *floor;

	floor = ft_itoa(draw->save->floor);
	draw->save = select_sector_mode(env, draw, draw->cur_s, 0);
	draw_text(1500, 365, floor, env);
	(draw->save->floor + 10 >= draw->save->ceil) ?
	(draw->save->floor = draw->save->ceil - 10) : 0 == 0;
	draw->save->floor++;
	draw_select_text(draw, env);
	free(floor);
}

void	select_floor_down(t_env *env, t_draw *draw)
{
	char *floor;

	floor = ft_itoa(draw->save->floor);
	draw->save = select_sector_mode(env, draw, draw->cur_s, 0);
	draw_text(1500, 365, floor, env);
	(draw->save->floor < 1) ? draw->save->floor = 0 : draw->save->floor--;
	draw_select_text(draw, env);
	free(floor);
}

void	select_ceil_up(t_env *env, t_draw *draw)
{
	char *ceil;

	ceil = ft_itoa(draw->save->ceil);
	draw->save = select_sector_mode(env, draw, draw->cur_s, 0);
	draw_text(1500, 305, ceil, env);
	(draw->save->ceil - 10 <= draw->save->floor) ?
	(draw->save->ceil = draw->save->floor + 10) : 0 == 0;
	draw_select_text(draw, env);
	draw->save->ceil++;
	free(ceil);
}

void	select_ceil_down(t_env *env, t_draw *draw)
{
	char *ceil;

	ceil = ft_itoa(draw->save->ceil);
	draw->save = select_sector_mode(env, draw, draw->cur_s, 0);
	draw_text(1500, 305, ceil, env);
	(draw->save->ceil < 10) ? draw->save->ceil = 20 : draw->save->ceil--;
	(draw->save->ceil - 10 <= draw->save->floor) ?
	(draw->save->ceil = draw->save->floor + 10) : 0 == 0;
	draw_select_text(draw, env);
	free(ceil);
}
