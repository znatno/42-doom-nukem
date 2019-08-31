#include "duke_nukem_editor.h"



//void delete_portal(t_env *env, t_draw *draw, t_vertex *temp, t_sector *temp_s)
//{
//	t_portals *cur;
//
//
//	cur = draw->portals;
//	while (cur)
//	{
//		cur = cur->next;
////		if (cur-> == temp_s || cur->sec_b == temp_s)
//			printf("DA DA YDALI\n");
//	}
//	printf("\n---------\n");
//
//}



/*
 * NEW FUNCTIONS TODO: implement new functions
 */


//void	find_wall_in_list(t_draw *draw, int cur_s)
//{
//	int count;
//
//	count = 0;
//
//}

void 	malloc_list(t_sector *sect)
{
	sect = sect->next;
	sect->vertexes = ft_memalloc(sizeof(t_vertex));
	sect->vertexes->next = NULL;
	sect->next = NULL;
}

void 	malloc_list_first(t_sector *sect)
{
	sect->vertexes = ft_memalloc(sizeof(t_vertex));
	sect->vertexes->next = NULL;
	sect->next = NULL;
}

void	pop_from_stack_to_list(t_env *env, t_draw *draw, t_stack **head)
{
	t_sector *cur_s;
	t_vertex *cur_v;
	t_vertex *head_v;
	t_xy cur_data;
	t_xy prev_data;
	t_xy first_data;
	int i;

	i = 0;
	cur_s = last_in_list(draw);
	cur_s->floor = DEFAULT_FLOOR;
	cur_s->ceil = DEFAULT_CEIL;
	first_data = stack_pop(head);
	cur_data = first_data; //

	head_v = cur_s->vertexes;
	head_v->xy1 = first_data;
	head_v->xy2 = cur_data;
	while (cur_data.x != -42)
	{
		i++;
		head_v->texture = TEXTURE_DEFAULT;
		head_v->xy1 = cur_data;
		cur_data = stack_pop(head);
		(cur_data.x != -42) ? (head_v->xy2 = cur_data) : (head_v->xy2 = first_data);
		(draw->head->next != NULL) ? find_portal(env, draw, head_v, cur_s) : 0 == 0;
		if (cur_data.x != -42)
		{
			head_v->next = ft_memalloc(sizeof(t_vertex));
			head_v = head_v->next;
		}
	}
	cur_s->walls = i;
	ft_bzero(&cur_s->object, 3);
	ft_bzero(&cur_s->action, 3);
	cur_s->object[0] = 1;
	cur_s->object[1] = 0;
	cur_s->object[2] = 1;
	head_v = NULL;
}

void save_stack_to_list (t_env *env, t_draw *draw, t_stack **head)
{
	t_sector *sect;

	if (!draw->head) // first element in list
	{
		sect = ft_memalloc(sizeof(t_sector));
		draw->head = sect;
		malloc_list_first(sect);
	}
	else
	{
		sect = last_in_list(draw);
		sect->next = ft_memalloc(sizeof(t_sector));
		malloc_list(sect);
	}
	pop_from_stack_to_list(env, draw, head);
	draw->s_count++;
}