/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_manipulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 13:16:29 by ggavryly          #+#    #+#             */
/*   Updated: 2019/08/18 13:16:31 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL_ttf.h>
#include "duke_nukem_editor.h"

uint32_t	get_pixel(SDL_Surface *sur, uint32_t x, uint32_t y, uint32_t color)
{
	uint32_t		*pixel;

	pixel = 0;
	pixel = sur->pixels + y * sur->pitch + x * sur->format->BytesPerPixel;
	if (*pixel == 0)
		return (0);
	else
		return (color);
}

void	draw_text(uint32_t cord_x, uint32_t cord_y, char *text, t_env *env)
{
	TTF_Font	*font = TTF_OpenFont("../fonts/FiraSans-Regular.ttf", 32);
	SDL_Color	color = {255, 255, 255};
	SDL_Surface	*font_surface = TTF_RenderText_Solid(font, text, color);
	uint32_t it_x;
	uint32_t it_y;
	uint32_t size_w;
	uint32_t size_h;

	it_y = 0;
	size_h = font_surface->h;
	size_w = font_surface->w;
	while (it_y < size_h)
	{
		it_x = 0;
		while (it_x < size_w)
		{
			env->buffer[(cord_y + it_y) * W_WIDTH + (cord_x + it_x)] = get_pixel(font_surface, it_x, it_y, 0xffffff);
			it_x++;
		}
		it_y++;
	}

}

void	draw_tools(t_env *env)
{
	draw_texture(env->textures->cords[DRAW_MODE], DRAW_MODE, 0xffffff, env);
	draw_texture(env->textures->cords[SELECT_MODE], SELECT_MODE, 0xffffff, env);
	draw_texture(env->textures->cords[WALL_MODE], WALL_MODE, 0xffffff, env);
	draw_texture(env->textures->cords[REFRESH], REFRESH, 0xffffff, env);
	draw_texture(env->textures->cords[CEIL], CEIL, 0xffffff, env);
	draw_texture(env->textures->cords[FLOOR], FLOOR, 0xffffff, env);
	draw_texture(env->textures->cords[LEFT], LEFT, 0xffffff, env);
	draw_texture(env->textures->cords[RIGHT], RIGHT, 0xffffff ,env);
	draw_texture(env->textures->cords[PLAYER], PLAYER, 0xffffff, env);
	draw_texture(env->textures->cords[OBJECTS], OBJECTS, 0xffffff, env);
	line((t_xy){.x = 1495,.y = 700}, (t_xy){.x = 1495, .y = 930}, env, 0xffffff);
	line((t_xy){.x = 1410,.y = 730}, (t_xy){.x = 1590, .y = 730}, env, 0xffffff);
}

void	draw_texture(t_xy cords ,uint32_t num_tex, uint32_t color,t_env *env)
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
					get_pixel(env->textures->arr_tex[num_tex], it_x, it_y, color);
			it_x++;
		}
		it_y++;
	}
}
