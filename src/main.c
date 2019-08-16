#include "duke_nukem_editor.h"

//void		stack_peek(struct s_stack **head)
//{
//
//}

void		stack_print(struct s_stack **head)
{
	struct s_stack *temp;

	temp = *head;
	while((temp))
	{
		printf("%d %d\n", temp->point.x, temp->point.y);
		temp = temp->next;
	}
}

t_xy		stack_pop(struct s_stack **head)
{
	t_stack *temp;
	t_xy 	data;

	if (head && *head)
	{
		data = (*head)->point;
		temp = (*head)->next;
		ft_memdel((void **) head);
		*head = temp;
		return (data);
	}
	data.x = -9e9;
	return (data);
}

void		stack_push(struct s_stack **head, t_xy data)
{
	struct s_stack *new_next;

	new_next = (t_stack*)ft_memalloc(sizeof(t_stack));
	new_next->next = *head;
	new_next->point = data;
	*head = new_next;
}

void		check_stack(void)
{
	t_stack *head;
	t_xy 	to_push;

	head = NULL;
	to_push.x = 5;
	to_push.y = 10;
	stack_push(&head,to_push);
	to_push.x += 2;
	to_push.y -= 2;
	stack_push(&head, to_push);
	to_push.x += 4;
	to_push.y -= 8;
	stack_push(&head, to_push);
	stack_print(&head);
	exit(99);
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



//void draw_vertex(t_env *env, t_draw *draw)
//{
//	SDL_GetMouseState(&draw->temp.x, &draw->temp.y);
//	if (draw->key == SPACE && draw->f_p[0].y != 0 && draw->f_p[0].x != 0 &&
//		I > 2)
//	{
//		line(draw->f_p[I - 1], draw->f_p[0], env, 0xFF00FF);
//		save_sector(env, draw);
//		I = -1;
//	}
//	else if (I && draw->key != SPACE)
//	{
//		draw->temp.x = ROUND(draw->temp.x);
//		draw->temp.y = ROUND(draw->temp.y);
//		line(draw->f_p[I - 1], draw->temp, env, 0xFF00FF);
//		draw->f_p[I].x = draw->temp.x;
//		draw->f_p[I].y = draw->temp.y;
//	}
//	else if (!I && draw->key != SPACE)
//	{
//		draw->f_p[I].x = ROUND(draw->temp.x);
//		draw->f_p[I].y = ROUND(draw->temp.y);
//	}
//	I++;
//	SDL_WarpMouseInWindow(env->window, ROUND(draw->temp.x),
//						  ROUND(draw->temp.y));
//}

t_env *sdl_main_loop(t_env *env)
{
	const Uint8 *kstate;
	t_draw *draw;
	SDL_Event ev;
	int loop;


	check_stack();
	draw = init_draw(draw);
	draw_desk(env);
	loop = 1;
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
				else if (kstate[SDL_SCANCODE_SPACE])
				{
					printf("SPACE\n");
				}
			}
			if (ev.type == SDL_MOUSEBUTTONDOWN)
			{
				if (ev.button.clicks)
				{
					printf("clicked\n");
				}
			}
		}
		draw_frame(env);
		SDL_UpdateTexture(env->texture, NULL, env->buffer,
						  W_WIDTH * (sizeof(int)));
		SDL_RenderCopy(env->renderer, env->texture, NULL, NULL);
		SDL_RenderPresent(env->renderer);
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
	env->buffer = (int *) malloc(sizeof(int) * W_HEIGHT * W_WIDTH);
	if (!env->window)
	{
		SDL_GetError();
	}
	env->renderer = SDL_CreateRenderer(env->window, -1,
									   SDL_RENDERER_ACCELERATED |
									   SDL_RENDERER_PRESENTVSYNC);

	env->texture = SDL_CreateTexture(env->renderer,
									 SDL_PIXELFORMAT_ARGB32,
									 SDL_TEXTUREACCESS_STREAMING,
									 W_WIDTH, W_HEIGHT);
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
