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

void	delete_sector_del(t_env *env, t_draw *draw, t_stack **head)
{
	delete_sector_from_list(env, draw);
	refresh_screen(draw, env, head);
}

void	player_placement_return(t_env *env, t_draw *draw)
{
	SDL_GetMouseState(&env->mouse_x, &env->mouse_y);
	draw->player = draw->save;
	draw->place_p.sect_p = draw->save;
	if(place_player((t_xyf) {.x = (float)env->mouse_x , .y = (float)env->mouse_y}, draw->save))
	{
		draw_texture((t_xy) {.x = env->mouse_x, .y = env->mouse_y}, PLAYER, 0xfffffff, env);
		draw->place_p.x = env->mouse_x / 10;
		draw->place_p.y = env->mouse_y / 10;
		select_sector_mode(env, draw, draw->cur_s, 0);
	}
}

void	sector_selection_right(t_env *env, t_draw *draw)
{
	if (draw->s_count > 1)
		draw->cur_s += (draw->s_count > draw->cur_s) ? 1 : (-draw->cur_s + 1);
	else
		draw->cur_s = 1;
	draw->save = select_sector_mode(env, draw, draw->cur_s, 0);
	(draw->save) ? draw_text(1500, 305, ft_itoa(draw->save->ceil), env) : 0 == 0;
	(draw->save) ? draw_text(1500, 365, ft_itoa(draw->save->floor), env) : 0 == 0;
}

void	wall_selection_right(t_env *env, t_draw *draw)
{
	draw->save = select_sector_mode(env, draw, draw->cur_s, 0);
	(draw->cur_v > draw->save->walls) ? draw->cur_v = 1 : draw->cur_v;
	draw->save_v = save_vertex(env, draw->cur_v++, draw->save);
	draw_text(1500, 305, ft_itoa(draw->save->ceil), env);
	draw_text(1500, 365, ft_itoa(draw->save->floor), env);
	(draw->cur_v > 1) ? draw_wall(TEXTURE_COORDS, draw->save_v->texture, env) : 0 == 0;
}

void	delete_line_backspace(t_env *env, t_draw *draw, t_stack **head)
{
	stack_pop(head);
	refresh_screen(draw, env, head);
}

void	select_texture_up(t_env *env, t_draw *draw)
{
	(draw->save_v->texture < TEXTURE_MAX) ? draw->save_v->texture += 1 : (draw->save_v->texture = TEXTURE_DEFAULT);
	draw_wall(TEXTURE_COORDS, draw->save_v->texture, env);
}

void	select_floor_up(t_env *env, t_draw *draw)
{
	draw->save = select_sector_mode(env, draw, draw->cur_s, 0);
	draw_text(1500, 365, ft_itoa(draw->save->floor), env);
	(draw->save->floor + 10 >= draw->save->ceil) ? (draw->save->floor = draw->save->ceil - 10) : 0 == 0;
	draw->save->floor++;
	draw_select_text(draw, env);
}

void	select_floor_down(t_env *env, t_draw *draw)
{
	draw->save = select_sector_mode(env, draw, draw->cur_s, 0);
	draw_text(1500, 365, ft_itoa(draw->save->floor), env);
	(draw->save->floor < 1) ? draw->save->floor = 0 : draw->save->floor--;
	draw_select_text(draw, env);
}

void	select_ceil_up(t_env *env, t_draw *draw)
{
	draw->save = select_sector_mode(env, draw, draw->cur_s, 0);
	draw_text(1500, 305, ft_itoa(draw->save->ceil),env);
	(draw->save->ceil - 10 <= draw->save->floor) ? (draw->save->ceil = draw->save->floor + 10) : 0 == 0;
	draw_select_text(draw, env);
	draw->save->ceil++;
}

void	select_ceil_down(t_env *env, t_draw *draw)
{
	draw->save = select_sector_mode(env, draw, draw->cur_s, 0);
	draw_text(1500, 305, ft_itoa(draw->save->ceil),env);
	(draw->save->ceil < 10) ? draw->save->ceil = 20 : draw->save->ceil--;
	(draw->save->ceil - 10 <= draw->save->floor) ? (draw->save->ceil = draw->save->floor + 10) : 0 == 0;
	draw_select_text(draw, env);
}

void	mouse_event(t_env *env, t_draw *draw, t_stack **head)
{
	SDL_GetMouseState(&env->mouse_x, &env->mouse_y);

	if (draw->ev.button.clicks && env->mouse_x < W_DRAW - 20
		&& env->mouse_y < H_DRAW - 20 && env->mouse_y > 15 &&
		env->mouse_x > 15 && !draw->s_mode)
	{
		draw_dot(env, draw, head);
	}
	if (draw->s_mode && !draw->w_mode && draw->save && click_to_text(env) >= 10 && click_to_text(env) <= 12)
		draw->save->object[click_to_text(env) % 10] = draw->save->object[click_to_text(env) % 10] == 0;
	else if ((draw->s_mode && !draw->w_mode && draw->save && click_to_text(env) >= 12 && click_to_text(env) <= 15))
		draw->save->action[click_to_text(env) % 10 - SHIFT] = draw->save->action[click_to_text(env) % 10 - SHIFT] == 0;
	draw_select_text(draw, env);
	(draw->s_mode) ? select_sector_mode(env, draw, draw->cur_s, 0)
				   : refresh_screen(draw, env, head);
}

void	last_iteration(t_env *env, t_draw *draw)
{
	(draw->save && draw->head && draw->cur_s > 0 && !draw->d_mode) ? draw_obj_and_action(draw, env, draw->save) : 0 == 0;
	(draw->save && draw->head) ? draw_player(draw, env, draw->save) : 0 == 0;
	draw_frame(env);
	draw_tools(env);
}

void	choose_event_second(t_env *env, t_draw *draw, t_stack **head)
{
	if (draw->kstate[SDL_SCANCODE_RIGHT] && draw->s_mode && !draw->w_mode && (draw->head != NULL))
		sector_selection_right(env, draw);
	else if (draw->kstate[SDL_SCANCODE_RIGHT] && draw->w_mode && !draw->d_mode && draw->s_mode &&  (draw->head != NULL))
		wall_selection_right(env, draw);
	else if (draw->kstate[SDL_SCANCODE_UP] && WALL_MOD_CONDITION && draw->cur_v > 1)
		select_texture_up(env, draw);
	else if (draw->kstate[SDL_SCANCODE_UP] && draw->floor_mode && draw->s_mode && (draw->head != NULL))
		select_floor_up(env, draw);
	else if (draw->kstate[SDL_SCANCODE_DOWN] && draw->floor_mode && draw->s_mode && draw->head != NULL)
		select_floor_down(env, draw);
	else if (draw->kstate[SDL_SCANCODE_UP] && draw->ceil_mode && draw->s_mode && draw->head)
		select_ceil_up(env, draw);
	else if (draw->kstate[SDL_SCANCODE_DOWN] && draw->ceil_mode && draw->s_mode && draw->head)
		select_ceil_down(env, draw);
}

void	choose_event(t_env *env, t_draw *draw, t_stack **head)
{
	if (draw->kstate[SDL_SCANCODE_ESCAPE] || draw->ev.type == SDL_QUIT)
	{
//					print_all_sectors(draw, draw->head);
//					record_data(transform_data(draw));
		draw->loop = 0;
	}
	else if (draw->kstate[SDL_SCANCODE_SPACE] && !draw->s_mode)
		finish_sector_space(draw, env, head);
	else if (draw->kstate[SDL_SCANCODE_DELETE])
		delete_sector_del(env, draw, head);
	else if (draw->kstate[SDL_SCANCODE_BACKSPACE] && !draw->s_mode)
		delete_line_backspace(env, draw, head);
	else if (draw->kstate[SDL_SCANCODE_RETURN] && draw->save && draw->head && draw->s_mode)
		player_placement_return(env, draw);
	choose_event_second(env, draw, head);
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
