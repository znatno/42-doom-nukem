#include "duke_nukem_editor.h"
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
		draw_all_portals(env, draw);
}
// TODO: DEL ME AFTER
int	click_to_text2(t_env *env)
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

t_vertex 		*save_vertex(t_env *env, t_draw *draw, int key, t_sector *save)
{
	t_sector 	*cur_s;
	t_vertex 	*cur_v;
	int 		i;

	cur_s = save;
	i = 0;
	while (cur_s)
	{
		cur_v = cur_s->vertexes;
		while (cur_v)
		{
			i++;
			if (i == key)
			{
				line(cur_v->xy1, cur_v->xy2, env, CYAN);
				return (cur_v);
			}
			cur_v = cur_v->next;
		}
		cur_s = cur_s->next;
	}
}

t_sector		*select_sector_mode(t_env *env, t_draw *draw, int key)
{
	t_sector 	*cur_s;
	t_vertex 	*cur_v;
	t_sector 	*save;
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
			{
				line(cur_v->xy1, cur_v->xy2, env, VIOLET);
				save = cur_s;
			}
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
	return (save);
}

t_env *sdl_main_loop(t_env *env)
{
	const Uint8 *kstate;
	t_sector 	*save;
	t_vertex 	*save_v;
	t_draw *draw;
	SDL_Event ev;
	int loop;
	int cur_s;
	int cur_v;

	//STACK VARS
	t_stack **head = ft_memalloc(sizeof(stack_t**));

	draw = init_draw(draw);
	draw_desk(env);
	loop = 1;
	draw->s_mode = false;
	draw->d_mode = false;
	draw->ceil_mode = false;
	draw->floor_mode = false;
	draw->w_mode = false;
	draw->s_count = 0;
	draw->p_count = 0;
	save = NULL;

	cur_s = 0;
	cur_v = 0;
	int i = 0;
	while (loop && env->sdl_error == NONE)
	{
		kstate = SDL_GetKeyboardState(NULL);
		while (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_KEYDOWN)
			{
				if (kstate[SDL_SCANCODE_ESCAPE] || ev.type == SDL_QUIT)
				{
					loop = 0;
				}
				else if (kstate[SDL_SCANCODE_SPACE] && !draw->s_mode)
				{
					draw->key = SPACE;
					if (stack_more_than_two(head))
					{
						draw_dot(env, draw, head);
						refresh_screen(draw, env, head);
					}
					draw->key = 0;
				}
				else if (kstate[SDL_SCANCODE_DELETE])
				{
					delete_sector_from_list(env, draw);
					refresh_screen(draw, env, head);
				}
				else if (kstate[SDL_SCANCODE_BACKSPACE] && !draw->s_mode)
				{
					stack_pop(head);
					refresh_screen(draw, env, head);
				}
				else if (kstate[SDL_SCANCODE_RIGHT] && draw->s_mode && !draw->w_mode && (draw->head != NULL))
				{
						if (draw->s_count > 1)
							cur_s += (draw->s_count > cur_s) ? 1 : (-cur_s + 1);
						else
							cur_s = 1;
						save = select_sector_mode(env, draw, cur_s);
					(save) ? draw_text(1500, 305, ft_itoa(save->ceil), env) : 0 == 0;
					(save) ? draw_text(1500, 365, ft_itoa(save->floor), env) : 0 == 0;

				}
				// FIXME: WALL MOD BLEAT
				else if (kstate[SDL_SCANCODE_RIGHT] && draw->w_mode && !draw->d_mode && draw->s_mode &&  (draw->head != NULL))
				{
						save = select_sector_mode(env, draw, cur_s);
						(cur_v > save->walls) ? cur_v = 1 : cur_v;
						save_v = save_vertex(env, draw, cur_v++, save);
						draw_text(1500, 305, ft_itoa(save->ceil), env);
						draw_text(1500, 365, ft_itoa(save->floor), env);

					(cur_v > 1) ? draw_wall(TEXTURE_COORDS, save_v->texture, env) : 0 == 0;
				}
				else if (kstate[SDL_SCANCODE_UP] && WALL_MOD_CONDITION && cur_v > 1)
				{
					(save_v->texture < TEXTURE_MAX) ? save_v->texture += 1 : (save_v->texture = TEXTURE_DEFAULT);
					draw_wall(TEXTURE_COORDS, save_v->texture, env);
				}
				else if (kstate[SDL_SCANCODE_UP] && draw->floor_mode && draw->s_mode && (draw->head != NULL))
				{
						save = select_sector_mode(env, draw, cur_s);
						draw_text(1500, 365, ft_itoa(save->floor), env);
						(save->floor + 10 >= save->ceil) ? (save->floor = save->ceil - 10) : 0 == 0;
						save->floor++;
						draw_select_text(draw, env);
				}
				else if (kstate[SDL_SCANCODE_DOWN] && draw->floor_mode && draw->s_mode && draw->head != NULL)
				{
						save = select_sector_mode(env, draw, cur_s);
						draw_text(1500, 365, ft_itoa(save->floor), env);
						(save->floor < 1) ? save->floor = 0 : save->floor--;
						draw_select_text(draw, env);
				}
				else if (kstate[SDL_SCANCODE_UP] && draw->ceil_mode && draw->s_mode && draw->head){
					save = select_sector_mode(env, draw, cur_s);
					draw_text(1500, 305, ft_itoa(save->ceil),env);
					(save->ceil - 10 <= save->floor) ? (save->ceil = save->floor + 10) : 0 == 0;
					draw_select_text(draw, env);
					save->ceil++;
				}
				else if (kstate[SDL_SCANCODE_DOWN] && draw->ceil_mode && draw->s_mode && draw->head){
					save = select_sector_mode(env, draw, cur_s);
					draw_text(1500, 305, ft_itoa(save->ceil),env);
					(save->ceil < 10) ? save->ceil = 20 : save->ceil--;
					(save->ceil - 10 <= save->floor) ? (save->ceil = save->floor + 10) : 0 == 0;
					draw_select_text(draw, env);
				}
			}
			if (ev.type == SDL_MOUSEBUTTONDOWN)
			{
				SDL_GetMouseState(&env->mouse_x, &env->mouse_y);
				if (ev.button.clicks && env->mouse_x < W_DRAW - 15
				&& env->mouse_y < H_DRAW - 15 && env->mouse_y > 15 &&
						env->mouse_x > 15 && !draw->s_mode && !draw->w_mode && draw->d_mode)
				{
					draw_dot(env, draw, head);
				}
				if (draw->s_mode && save && click_to_text(env) >= 10 && click_to_text(env) <= 12)
					save->object[click_to_text(env) % 10] = save->object[click_to_text(env) % 10] == 0;
				else if ((draw->s_mode && save && click_to_text(env) >= 12 && click_to_text(env) <= 15))
					save->action[click_to_text(env) % 10 - SHIFT] = save->action[click_to_text(env) % 10 - SHIFT] == 0;

					draw_select_text(draw, env);
				(draw->s_mode) ? select_sector_mode(env, draw, cur_s)
				: refresh_screen(draw, env, head);
				// TODO: SELECT IF OBJECT PICKED
			}
		}
		(save && draw->head && cur_s > 0) ? draw_obj_and_action(draw, env, save) : 0 == 0;
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
