#include "duke_nukem_editor.h"

void print_sector(t_sector *temp)
{
	t_vertex *cur;

	cur = temp->vertexes;
	while (cur)
	{
		printf("x1 = %d y1 = %d \n x2 = %d y2 = %d\n\n",
			   cur->xy1.x, cur->xy1.y, cur->xy2.x, cur->xy2.y);
		cur = cur->next;
	}
	// free(cur);
}

//void print_all_portals(t_draw *draw)
//{
//	t_portals *cur_s;
//	t_vertex *cur_line;
//
//	cur_s = draw->portals;
//	while (cur_s)
//	{
//		cur_line = cur_s->line;
//			printf("x1 = %d y1 = %d \n x2 = %d y2 = %d\n\n",
//				   cur_line->xy1.x, cur_line->xy1.y, cur_line->xy2.x,
//				   cur_line->xy2.y);
//		cur_s = cur_s->next;
//	}
//}

void print_all_sectors(t_draw *draw, t_sector *temp)
{
	t_sector *cur_s;
	t_vertex *cur_v;

	cur_s = draw->head;
	while (cur_s)
	{
		cur_v = cur_s->vertexes;
		while (cur_v)
		{
			printf("x1 = %d y1 = %d \n x2 = %d y2 = %d\n--------------\n",
				   cur_v->xy1.x, cur_v->xy1.y, cur_v->xy2.x, cur_v->xy2.y);
			cur_v = cur_v->next;
		}
		cur_s = cur_s->next;
	}
}

void find_portal(t_draw *draw, t_vertex *temp, t_sector *temp_s)
{
	t_sector *cur_s;
	t_vertex *cur_v;
	int i;

	i = 0;
	cur_s = draw->head;
	while (cur_s)
	{
		i++;
		printf("sectors %d | %p  |  %p\n", i, cur_s, temp_s);
		cur_v = cur_s->vertexes;
		while (cur_v)
		{
			printf("|---------------------\nx1 = %d y1 = %d\n x2 = %d y2 = %d\n", cur_v->xy1.x, cur_v->xy1.y,cur_v->xy2.x,cur_v->xy2.y);
			printf("---------------------|\nx1 = %d y1 = %d\n x2 = %d y2 = %d\n\n\n", temp->xy1.x,temp->xy1.y,temp->xy2.x,temp->xy2.y);
			if (((temp->xy1.x == cur_v->xy1.x &&
				 temp->xy1.y == cur_v->xy1.y &&
				 temp->xy2.x == cur_v->xy2.x &&
				 temp->xy2.y == cur_v->xy2.y)
				&& (temp->xy1.x == cur_v->xy2.x &&
					temp->xy2.y == cur_v->xy1.y &&
					temp->xy2.x == cur_v->xy1.x &&
					temp->xy2.y == cur_v->xy1.y)) 	&& cur_s != temp_s)
			{
				printf("\n>>>>OCCURANCE<<<<\n", temp->xy1.x,temp->xy1.y,temp->xy2.x,temp->xy2.y);
			}
			cur_v = cur_v->next;
		}
		cur_s = cur_s->next;
	}
}

//void add_sector_to_list(t_sector *temp, t_draw *draw)
//{
//	int i;
//	t_vertex *head;
//
//	while (temp->next != NULL)
//		temp = temp->next;
//	if (!(temp->next = (t_sector *) malloc(sizeof(t_sector))))
//		exit(111);
//	temp = temp->next;
//	if (!(temp->vertexes = (t_vertex *) malloc(sizeof(t_vertex))))
//		exit(167);
//	head = temp->vertexes;
//	i = 0;
//	while (++i < I)
//	{
//		temp->vertexes->xy1.x = draw->f_p[i - 1].x;
//		temp->vertexes->xy1.y = draw->f_p[i - 1].y;
//		temp->vertexes->xy2.x = draw->f_p[i].x;
//		temp->vertexes->xy2.y = draw->f_p[i].y;
//		temp->vertexes->next = NULL;
//		temp->next = NULL;
//		find_portal(draw, temp);
//		if (!(temp->vertexes->next = (t_vertex *) malloc(sizeof(t_vertex))))
//			exit(168);
//		temp->vertexes = temp->vertexes->next;
//	}
//	temp->vertexes->xy1.x = draw->f_p[i - 1].x;
//	temp->vertexes->xy1.y = draw->f_p[i - 1].y;
//	temp->vertexes->xy2.x = draw->f_p[0].x;
//	temp->vertexes->xy2.y = draw->f_p[0].y;
//	temp->vertexes->next = NULL;
//	temp->vertexes = head;
//	temp->next = NULL;
//	draw->s_count++;
//}

t_sector *check_if_deleted_sector(t_draw *draw, t_vertex *tmp,
								  t_vertex *cur_v, t_sector *cur_s)
{
	if (!(cur_s = draw->head))
		return (NULL);
	if (cur_s->next == NULL)
	{
		cur_v = cur_s->vertexes;
		while (cur_v != NULL)
		{
			tmp = cur_v->next;
			free(cur_v);
			cur_v = tmp;
		}
		cur_s = NULL;
		draw->head = NULL;
		free(cur_s);
		draw->s_count--;
		return (NULL);
	}
	return (cur_s);
}

void free_sect(t_draw *draw, t_sector *del_me, t_sector *cur_s)
{
	del_me = cur_s->next;
	cur_s->next = NULL;
	draw->s_count--;
	free(del_me);
}

void delete_sector_from_list(t_draw *draw)
{
	t_sector *cur_s;
	t_vertex *cur_v;
	t_sector *del_me;
	t_vertex *tmp;

	if (!(cur_s = check_if_deleted_sector(draw, tmp, cur_v, cur_s)))
		return;
	while (cur_s->next->next != NULL)
	{
		cur_s = cur_s->next;
	}
	cur_v = cur_s->next->vertexes;
	while (cur_v != NULL)
	{
		tmp = cur_v->next;
		free(cur_v);
		cur_v = tmp;
	}
	free_sect(draw, del_me, cur_s);
}

/*
 * NEW FUNCTIONS TODO: implement new functions
 */

t_sector *last_in_list(t_draw *draw)
{
	t_sector *cur;

	cur = draw->head;
	while (cur && cur->next && (cur = cur->next))
		;
	return (cur);
}

void	find_wall_in_list(t_draw *draw, int cur_s)
{
	int count;

	count = 0;

}

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

void	pop_from_stack_to_list(t_draw *draw, t_stack **head)
{
	t_sector *cur_s;
	t_vertex *cur_v;
	t_vertex *head_v;
	t_xy cur_data;
	t_xy prev_data;
	t_xy first_data;

	cur_s = last_in_list(draw);
	first_data = stack_pop(head);
	cur_data = first_data; //

	head_v = cur_s->vertexes;
	head_v->xy1 = first_data;
	head_v->xy2 = cur_data;

	while (cur_data.x != -42)
	{
		head_v->xy1 = cur_data;
		cur_data = stack_pop(head);
		(cur_data.x != -42) ? (head_v->xy2 = cur_data) : (head_v->xy2 = first_data);
		(draw->head->next != NULL) ? find_portal(draw, head_v, cur_s) : 0 == 0;
		if (cur_data.x != -42)
		{
			head_v->next = ft_memalloc(sizeof(t_vertex));
			head_v = head_v->next;
		}
	}
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
	pop_from_stack_to_list(draw, head);
	draw->s_count++;
}