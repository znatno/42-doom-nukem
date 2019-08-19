#include "duke_nukem_editor.h"

void    stack_print(struct s_stack **head)
{
	struct s_stack *temp;

	temp = *head;
	while((temp))
	{
		printf("%d %d\n", temp->xy.x, temp->xy.y);
		temp = temp->next;
	}
}

int    stack_more_than_two(struct s_stack **head)
{
	struct s_stack *temp;
	int 	i;

	temp = *head;
	i = 0;
	while((temp))
	{
		i++;
		if (i > 2)
			return (true);
		temp = temp->next;
	}
	return (false);
}

t_xy    stack_pop(struct s_stack **head)
{
	t_stack *temp;
	t_xy data;

	if (head && *head)
	{
		data = (*head)->xy;
		temp = (*head)->next;
		ft_memdel((void **) head);
		*head = temp;
		return (data);
	}
	data.x = -42;
	data.y = -42;
	return (data);
}

void    stack_push(struct s_stack **head, t_xy data)
{
	struct s_stack *new_next;

	new_next = (t_stack*)ft_memalloc(sizeof(t_stack));

	new_next->next = *head;
	new_next->xy.y = data.y;
	new_next->xy.x = data.x;
	*head = new_next;
}

void	stack_draw(t_env *env, t_draw *draw, t_stack **head)
{
	struct s_stack *temp;
	struct s_stack *prev;

	if (head && *head)
	{
		temp = *head;
		if (draw->key == SPACE)
		{
			while (temp->next)
				temp = temp->next;
			line((*head)->xy, temp->xy, env, WHITE);
			save_stack_to_list(env, draw, head);
		}
		else
		{
			while (temp->next)
			{
				prev = temp;
				temp = temp->next;
				line(prev->xy, temp->xy, env, WHITE);
			}
		}

	}
}

void    draw_dot(t_env *env, t_draw *draw, t_stack **head)
{
	t_xy data;

	SDL_GetMouseState(&data.x,&data.y);
	data.x = ROUND(data.x);
	data.y = ROUND(data.y);
	(draw->key != SPACE) ? stack_push(head, data) : 0 == 0;
	if (*head && (*head)->next != NULL)
		stack_draw(env, draw, head);
//	SDL_WarpMouseInWindow(env->window, data.x, data.y);
//	check_drawer(env, draw);
//draw_stack(env, draw, head);
	return ;
}