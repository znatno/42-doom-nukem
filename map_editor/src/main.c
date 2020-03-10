/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopolonc <vopolonc@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 14:26:39 by vopolonc          #+#    #+#             */
/*   Updated: 2019/08/31 14:26:40 by vopolonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke_nukem_editor.h"

t_env			*sdl_main_loop(t_env *env, t_draw *draw, t_stack **head)
{
	draw_desk(env);
	while (draw->loop && env->sdl_error == NONE)
	{
		draw->kstate = SDL_GetKeyboardState(NULL);
		while (SDL_PollEvent(&draw->ev))
		{
			if (draw->ev.type == SDL_KEYDOWN)
				choose_event(env, draw, head);
			if (draw->ev.type == SDL_MOUSEBUTTONDOWN)
				mouse_event(env, draw, head);
		}
		last_iteration(env, draw);
		SDL_UpdateWindowSurface(env->window);
	}
	free(*head);
	free(head);
	return (env);
}

t_env			*sdl_init(t_env *env)
{
	init_vars(env);
	env->window = SDL_CreateWindow("doom-nukem-editor", 910, 510, W_WIDTH,
								W_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
	env->win_surface = SDL_GetWindowSurface(env->window);
	env->buffer = (uint32_t *)env->win_surface->pixels;
	if (!env->window)
		SDL_GetError();
	texture_load(env);
	return (env);
}

int				main(void)
{
	t_env		*env;
	t_draw		*draw;
	t_textures	textures;
	t_stack		**head;

	head = ft_memalloc(sizeof(stack_t**));
	env = malloc(sizeof(t_env));
	draw = init_draw(draw);
	env->textures = &textures;
	if (!(SDL_Init(SDL_INIT_EVERYTHING) < 0) && !(TTF_Init() < 0))
	{
		env = sdl_main_loop(sdl_init(env), draw, head);
	}
	else
	{
		SDL_GetError();
	}
	SDL_Quit();
	TTF_Quit();
	return (0);
}
