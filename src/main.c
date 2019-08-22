#include "duke_nukem_editor.h"

//void save_sector(t_env *env, t_draw *draw)
//{
//	t_sector *temp;
//
//	if (!(temp = draw->head))
//	{
//		if (!(temp = (t_sector *) malloc(sizeof(t_sector))))
//			exit(166);
////		create_sectors_list(env, draw, temp);
////        print_sector(temp);
//	}
//	else
//	{
//		add_sector_to_list(temp, draw);
////		print_all_sectors(draw, temp);
//	}
//
//	//free(temp);
//}

//void				is_portal(t_draw *draw, t_env *env, t_vertex *cur_v)
//{
//
//}
void 				refresh_screen(t_draw *draw, t_env *env, t_stack **head)
{
	t_sector *cur_s;
	t_vertex *cur_v;

	cur_s = draw->head;
	clear_screen(env);
	draw_desk(env);
	stack_draw(env,draw ,head);
	while (draw->head != NULL && cur_s)
	{
		cur_v = cur_s->vertexes;
		while (cur_v)
		{
			// DRAW PORTALS
			if (!(find_portal_for_draw(env, draw, cur_v, cur_s)))
				delete_portal(draw, cur_v);
//			line(cur_v->xy1, cur_v->xy2, env, RED);
//			else
				line(cur_v->xy1, cur_v->xy2, env, WHITE);
			cur_v = cur_v->next;
		}
		cur_s = cur_s->next;
	}

	if (draw->portals != NULL)
	{
		draw_all_portals(env, draw);
	}
//	draw_all_portals(env, draw);
}

//void 				redraw_screen(t_draw *draw, t_env *env)
//{
//	t_sector *cur_s;
//	t_vertex *cur_v;
//
//	cur_s = draw->head;
//	delete_sector_from_list(draw);
//	clear_screen(env);
//	draw_desk(env);
//	while (draw->head != NULL && cur_s)
//	{
//		cur_v = cur_s->vertexes;
//		while (cur_v)
//		{
//			line(cur_v->xy1, cur_v->xy2, env, 0xFF00FF);
//			cur_v = cur_v->next;
//		}
//		cur_s = cur_s->next;
//	}
//}

t_draw *init_draw(t_draw *draw)
{
	if (!(draw = (t_draw *) malloc(sizeof(t_draw))))
	{
		exit(13);
	}
	I = 0;
	draw->temp.x = 0;
	draw->temp.y = 0;
	draw->head = NULL;
	draw->portals = NULL;
	return (draw);
}

void 		select_sector_mode(t_env *env, t_draw *draw, int key)
{
	t_sector 	*cur_s;
	t_vertex 	*cur_v;
	int 		i;

	cur_s = draw->head;
	clear_screen(env);
	draw_desk(env);
	i = 0;
	while (draw->head != NULL && cur_s)
	{
		i++;
		cur_v = cur_s->vertexes;
		while (cur_v)
		{
			if (i == key)
			line(cur_v->xy1, cur_v->xy2, env, VIOLET);
			else
				line(cur_v->xy1, cur_v->xy2, env, WHITE);
			if (!(find_portal_for_draw(env, draw, cur_v, cur_s)))
				delete_portal(draw, cur_v);
			cur_v = cur_v->next;
		}
		cur_s = cur_s->next;
	}
	if (draw->portals != NULL)
	{
		draw_all_portals(env, draw);
	}
}

t_env *sdl_main_loop(t_env *env)
{
	const Uint8 *kstate;
	t_draw *draw;
	SDL_Event ev;
	int loop;
	int cur_s;

	//STACK VARS
	t_stack **head = ft_memalloc(sizeof(stack_t**));

	draw = init_draw(draw);
	draw_desk(env);
	loop = 1;
	draw->s_mode = false;
	draw->d_mode = false;
	draw->s_count = 0;
	draw->p_count = 0;
	cur_s = 0;
	while (loop && env->sdl_error == NONE)
	{
		kstate = SDL_GetKeyboardState(NULL);
		while (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_KEYDOWN)
			{
				if (kstate[SDL_SCANCODE_ESCAPE] || ev.type == SDL_QUIT)
				{
//					print_all_sectors(draw, draw->head);к
					record_data(transform_data(draw));
					loop = 0;
				}
				else if (kstate[SDL_SCANCODE_SPACE] && !draw->s_mode)
				{
					draw->key = SPACE; // space pressed
					if (stack_more_than_two(head))
					{
						draw_dot(env, draw, head);
						refresh_screen(draw, env, head);
					}
					draw->key = 0;
				} // TODO: WALL SELECTION
//				else if (kstate[SDL_SCANCODE_RETURN] && !draw->d_mode)
//				{
//					cur_v = find_wall_in_list()
//				}
				else if (kstate[SDL_SCANCODE_DELETE])// && draw->s_mode)
				{
					delete_sector_from_list(env, draw);
					select_sector_mode(env, draw, cur_s);
				}
				else if (kstate[SDL_SCANCODE_BACKSPACE] && !draw->s_mode)
				{
					stack_pop(head);
					refresh_screen(draw, env, head);
				}
//				else if (kstate[SDL_SCANCODE_S])
//				{
//					draw->s_mode = (draw->s_mode) ? 0 : 1;
//					(draw->s_mode) ? 0 == 0 : refresh_screen(draw, env, head);
//
//				}
				else if (kstate[SDL_SCANCODE_RIGHT] && draw->s_mode)
				{
					if (draw->s_count > 1)
						cur_s += (draw->s_count > cur_s) ? 1 : (-cur_s + 1);
					else
						cur_s = 1;
//					printf("%d\n",cur_s);
						select_sector_mode(env, draw, cur_s);
				}
			}
			if (ev.type == SDL_MOUSEBUTTONDOWN)
			{
				SDL_GetMouseState(&env->mouse_x, &env->mouse_y);
				if (ev.button.clicks && env->mouse_x < W_DRAW - 20
				&& env->mouse_y < H_DRAW - 20 && env->mouse_y > 15 &&
						env->mouse_x > 15 && !draw->s_mode)
				{
					draw_dot(env, draw, head);
				}
				draw_select_text(draw, env);
				(draw->s_mode) ? select_sector_mode(env, draw, cur_s)
				: refresh_screen(draw, env, head);
			}
		}
		draw_frame(env);
		draw_tools(env);
		SDL_UpdateWindowSurface(env->window);
		SDL_Delay(10);
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
