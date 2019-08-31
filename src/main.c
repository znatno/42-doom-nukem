#include "duke_nukem_editor.h"

t_draw *init_draw(t_draw *draw)
{
	if (!(draw = (t_draw *) malloc(sizeof(t_draw))))
		exit(13);
	I = 0;
	draw->temp.x = 0;
	draw->temp.y = 0;
	draw->head = NULL;
	draw->portals = NULL;
	draw->loop = 1;
	draw->place_p.sect_p = NULL;
	draw->place_p.x = 0;
	draw->place_p.y = 0;
	draw->s_mode = false;
	draw->d_mode = false;
	draw->ceil_mode = false;
	draw->floor_mode = false;
	draw->w_mode = false;
	draw->save_v = NULL;
	draw->s_count = 0;
	draw->p_count = 0;
	draw->save = NULL;
	draw->cur_s = 0;
	draw->cur_v = 0;
	return (draw);
}



void	finish_sector_space(t_draw *draw, t_env *env, t_stack **head)
{
	draw->key = SPACE;
	if (stack_more_than_two(head))
	{
		draw_dot(env, draw, head);
		refresh_screen(draw, env, head);
	}
	draw->key = 0;
}



t_env *sdl_main_loop(t_env *env)
{
	t_draw *draw;
	t_stack **head = ft_memalloc(sizeof(stack_t**));

	draw = init_draw(draw);
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
//		SDL_Delay(10);
	}
	return (env);
}


void init_vars(t_env *env)
{
	env->sdl_error = NONE;
	env->zoom = 20;
}

t_env *sdl_init(t_env *env)
{
	init_vars(env);
	env->window = SDL_CreateWindow("doom-nukem-editor", 910, 510, W_WIDTH,
								   W_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
	env->win_surface = SDL_GetWindowSurface(env->window);
	env->buffer = (uint32_t *)env->win_surface->pixels;
	if (!env->window)
	{
		//env->sdl_error = ERROR_WINDOW;
		SDL_GetError();
	}
	texture_load(env);
	return (env);
}

int main(void)
{
	t_env *env;
	t_textures textures;

	env = malloc(sizeof(t_env));
	env->textures = &textures;
	if (!(SDL_Init(SDL_INIT_EVERYTHING) < 0) && !(TTF_Init() < 0))
	{
		env = sdl_main_loop(sdl_init(env));
	}
	else
	{
		SDL_GetError();
	}
	SDL_Quit();
	TTF_Quit();
	return (0);
}
