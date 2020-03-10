/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_manipulation_a.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 21:40:34 by ggavryly          #+#    #+#             */
/*   Updated: 2019/08/30 21:40:36 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke_nukem_editor.h"

void	draw_text(uint32_t cord_x, uint32_t cord_y, char *text, t_env *env)
{
	t_font	font;

	open_font(&font.font, &font.color, &font.font_surface, text);
	font.it_y = 0;
	draw_text_black(cord_x, cord_y, "0000", env);
	font.size_h = font.font_surface->h;
	font.size_w = font.font_surface->w;
	while (font.it_y < font.size_h)
	{
		font.it_x = 0;
		while (font.it_x < font.size_w)
		{
			env->buffer[(cord_y + font.it_y) * W_WIDTH +
			(cord_x + font.it_x)] = get_pixel(font.font_surface,
					font.it_x, font.it_y, 0xffffff);
			font.it_x++;
		}
		font.it_y++;
	}
	SDL_FreeSurface(font.font_surface);
	TTF_CloseFont(font.font);
}

void	draw_tools(t_env *env)
{
	draw_texture(env->textures->cords[DRAW_MODE], DRAW_MODE, 0xffffff, env);
	draw_texture(env->textures->cords[SELECT_MODE], SELECT_MODE, 0xffffff, env);
	draw_texture(env->textures->cords[WALL_MODE], WALL_MODE, 0xffffff, env);
	draw_texture(env->textures->cords[REFRESH], REFRESH, 0xffffff, env);
	draw_texture(env->textures->cords[CEIL], CEIL, 0xffffff, env);
	draw_texture(env->textures->cords[FLOOR], FLOOR, 0xffffff, env);
	draw_texture(env->textures->cords[OBJECTS], OBJECTS, 0xffffff, env);
	draw_text(1480, 15, "- draw", env);
	draw_text(1480, 75, "- select", env);
	draw_text(1480, 135, "- wall", env);
	draw_text(1475, 195, "- refresh", env);
	if (env->textures->selected >= 0)
		draw_texture(env->textures->cords[env->textures->selected],
				env->textures->selected, 0xf98d8d, env);
}

void	draw_texture(t_xy cords, uint32_t num_tex, uint32_t color, t_env *env)
{
	uint32_t it_x;
	uint32_t it_y;
	uint32_t size_w;
	uint32_t size_h;

	it_y = 0;
	size_w = env->textures->arr_tex[num_tex]->w;
	size_h = env->textures->arr_tex[num_tex]->h;
	while (it_y < size_h)
	{
		it_x = 0;
		while (it_x < size_w)
		{
			env->buffer[(cords.y + it_y) * W_WIDTH + (cords.x + it_x)] =
					get_pixel(env->textures->arr_tex[num_tex],
							it_x, it_y, color);
			it_x++;
		}
		it_y++;
	}
}

void	draw_wall(t_xy cords, uint32_t num_tex, t_env *env)
{
	uint32_t it_x;
	uint32_t it_y;
	uint32_t size_w;
	uint32_t size_h;

	it_y = 0;
	size_w = env->textures->arr_tex[num_tex]->w;
	size_h = env->textures->arr_tex[num_tex]->h;
	while (it_y < size_h)
	{
		it_x = 0;
		while (it_x < size_w)
		{
			env->buffer[(cords.y + it_y) * W_WIDTH + (cords.x + it_x)] =
					get_pixel_wall(env->textures->arr_tex[num_tex], it_x, it_y);
			it_x++;
		}
		it_y++;
	}
}
