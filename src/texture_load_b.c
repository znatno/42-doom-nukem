/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_load_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 16:59:03 by ggavryly          #+#    #+#             */
/*   Updated: 2019/08/31 16:59:05 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke_nukem_editor.h"

void	fill_cords_a(t_xy **cords)
{
	(*cords)[DRAW_MODE].x = 1425;
	(*cords)[DRAW_MODE].y = 10;
	(*cords)[SELECT_MODE].x = 1425;
	(*cords)[SELECT_MODE].y = 70;
	(*cords)[WALL_MODE].x = 1425;
	(*cords)[WALL_MODE].y = 130;
	(*cords)[REFRESH].x = 1425;
	(*cords)[REFRESH].y = 190;
	(*cords)[CEIL].x = 1425;
	(*cords)[CEIL].y = 300;
	(*cords)[FLOOR].x = 1425;
	(*cords)[FLOOR].y = 360;
	(*cords)[LEFT].x = 1415;
	(*cords)[LEFT].y = 450;
	(*cords)[RIGHT].x = 1540;
	(*cords)[RIGHT].y = 450;
	(*cords)[PLAYER].x = 1440;
	(*cords)[PLAYER].y = 540;
	(*cords)[OBJECTS].x = 1530;
	(*cords)[OBJECTS].y = 540;
}

void	fill_cords_b(t_xy **cords)
{
	(*cords)[GUNS_OBJ].x = 1430;
	(*cords)[GUNS_OBJ].y = 640;
	(*cords)[KITS_OBJ].x = 1430;
	(*cords)[KITS_OBJ].y = 740;
	(*cords)[ARMOR_OBJ].x = 1430;
	(*cords)[ARMOR_OBJ].y = 850;
	(*cords)[DEATH_ACT].x = 1520;
	(*cords)[DEATH_ACT].y = 640;
	(*cords)[FLY_ACT].x = 1520;
	(*cords)[FLY_ACT].y = 750;
	(*cords)[MIXED_ACT].x = 1520;
	(*cords)[MIXED_ACT].y = 860;
}

void	texture_cords(t_env *env)
{
	t_xy	*cords;

	cords = (t_xy *)malloc(sizeof(t_xy) * 16);
	fill_cords_a(&cords);
	fill_cords_b(&cords);
	env->textures->cords = cords;
}
