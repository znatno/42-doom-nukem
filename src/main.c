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
			line(cur_v->xy1, cur_v->xy2, env, WHITE);
			cur_v = cur_v->next;
		}
		cur_s = cur_s->next;
	}

		printf("%p\n %p\n",draw->portals, draw->portals->next);
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
			cur_v = cur_v->next;
		}
		cur_s = cur_s->next;
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
					loop = 0;
				}
				else if (kstate[SDL_SCANCODE_SPACE] && !draw->s_mode)
				{
					draw->key = SPACE; // space pressed
					if (stack_more_than_two(head))
					draw_dot(env,draw,head);
					draw->key = 0;
				} // TODO: WALL SELECTION
//				else if (kstate[SDL_SCANCODE_RETURN] && !draw->d_mode)
//				{
//					cur_v = find_wall_in_list()
//				}
				else if (kstate[SDL_SCANCODE_DELETE] && draw->s_mode)
				{
					delete_sector_from_list(draw);
					select_sector_mode(env, draw, cur_s);
				}
				else if (kstate[SDL_SCANCODE_BACKSPACE] && !draw->s_mode)
				{
					stack_pop(head);
					refresh_screen(draw, env, head);
				}
				else if (kstate[SDL_SCANCODE_S])
				{
					draw->s_mode = (draw->s_mode) ? 0 : 1;
					(draw->s_mode) ? 0 == 0 : refresh_screen(draw, env, head);

				}
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
			if (ev.type == SDL_MOUSEBUTTONDOWN && !draw->s_mode)
			{
				if (ev.button.clicks)
				{
					draw_dot(env, draw, head);
				}
			}
		}
		draw_frame(env);
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
	return (env);
}

int main(void)
{
	t_env *env;

	env = malloc(sizeof(t_env));
	if (!(SDL_Init(SDL_INIT_EVERYTHING) < 0))
	{
		env = sdl_main_loop(sdl_init(env));
	}
	else
	{
		SDL_GetError();
	}
	SDL_Quit();
	return (0);
}
