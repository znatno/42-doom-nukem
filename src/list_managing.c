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

//int	check_if_deleted_portal(t_draw *draw, t_portals *cur)
//{
//	printf("cur->sec_a = %p\n cur->sec_b = %p\n\n", cur->sec_a->vertexes, cur->sec_b->vertexs);
//	//	if (cur->sec_a == NULL || cur->sec_b == NULL)
////	{
////		free(cur);
////		cur = NULL;
////		return (1);
////	}
////	else
//		return (0);
//}

void	del_cur_portal(t_draw *draw, t_portals *cur)
{
	t_portals *head;
	t_portals *del_me;
	t_portals *prev;

	if (draw->portals->next)
	{
		head = draw->portals;
		while (head->next != cur)
		{
			head = head->next;
		}
		del_me = head->next;
		prev = del_me->next;
		head->next = prev;
		free(del_me);
		del_me = NULL;
	}
	else
	{
		del_me = draw->portals;
		free()
	}
}

void	delete_portal(t_draw *draw, t_vertex *cur_v)
{
	t_portals *cur;
	int i;

	i = 0;
	cur = draw->portals;
	while (cur)
	{
		if (((cur->xy1.x == cur_v->xy1.x &&
			  cur->xy1.y == cur_v->xy1.y &&
			  cur->xy2.x == cur_v->xy2.x &&
			  cur->xy2.y == cur_v->xy2.y)
			 || (cur->xy1.x == cur_v->xy2.x &&
				 cur->xy1.y == cur_v->xy2.y &&
				 cur->xy2.x == cur_v->xy1.x &&
				 cur->xy2.y == cur_v->xy1.y)))
				del_cur_portal(draw,cur);
			cur = cur->next;
	}
}


void	draw_all_portals(t_env *env, t_draw *draw)
{
		t_portals *cur;
		int i;

		i = 0;
		cur = draw->portals;
		while (cur)
		{
			printf("%d\n",++i);
			line(cur->xy1, cur->xy2, env, RED);
			cur = cur->next;
		}
}

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



t_sector *last_portal(t_draw *draw)
{
	t_portals *cur;

	cur = draw->portals;
	while (cur->next)
	{
		cur = cur->next;
//		printf("IM HERE\n");
	}
//	printf("%p",cur);
	return (cur);
}
t_portals 	*malloc_portal(t_portals *portal, t_vertex *data, t_sector *temp_s, t_sector *cur_s)
{
	portal->sec_a = cur_s;
	portal->sec_b = temp_s;
	portal->xy1 = data->xy1;
	portal->xy2 = data->xy2;
	return (portal);
}

t_portals 	*malloc_portal_first(t_portals *portal, t_vertex *data, t_sector *temp_s, t_sector *cur_s)
{
	portal->sec_a = cur_s;
	portal->sec_b = temp_s;
	portal->xy1 = data->xy1;
	portal->xy2 = data->xy2;
	return (portal);
}


void		new_portal(t_draw *draw, t_vertex *temp,t_sector *temp_s, t_sector *cur_s)
{
	t_portals *portal;

	if (!draw->portals) // first element in list
	{
		draw->portals = ft_memalloc(sizeof(t_portals));
		draw->portals = malloc_portal_first(draw->portals, temp, temp_s, cur_s);
		draw->portals->next = NULL;
	}
	else
	{
		portal = last_portal(draw);
		portal->next = ft_memalloc(sizeof(t_portals));
		portal = portal->next;
		portal->sec_a = cur_s;
		portal->sec_b = temp_s;
		portal->xy1 = temp->xy1;
		portal->xy2 = temp->xy2;
		portal->next = NULL;
	}
//	draw->s_count++;
}


int find_portal_for_draw(t_env *env, t_draw *draw, t_vertex *temp, t_sector *temp_s)
{
	t_sector *cur_s;
	t_vertex *cur_v;
	int i;
//				*** ***
// 				 -   -
//				\_____/

	i = 0;
	cur_s = draw->head;
	while (cur_s)
	{
		i++;
//		printf("sectors %d | %p  |  %p\n", i, cur_s, temp_s);
		cur_v = cur_s->vertexes;
		while (cur_v)
		{
//			printf("|---------------------\nx1 = %d y1 = %d\n x2 = %d y2 = %d\n", cur_v->xy1.x, cur_v->xy1.y,cur_v->xy2.x,cur_v->xy2.y);
//			printf("---------------------|\nx1 = %d y1 = %d\n x2 = %d y2 = %d\n\n\n", temp->xy1.x,temp->xy1.y,temp->xy2.x,temp->xy2.y);
			if (((temp->xy1.x == cur_v->xy1.x &&
				  temp->xy1.y == cur_v->xy1.y &&
				  temp->xy2.x == cur_v->xy2.x &&
				  temp->xy2.y == cur_v->xy2.y)
				 || (temp->xy1.x == cur_v->xy2.x &&
					 temp->xy1.y == cur_v->xy2.y &&
					 temp->xy2.x == cur_v->xy1.x &&
					 temp->xy2.y == cur_v->xy1.y)) && (cur_s != temp_s))
			{
				return (1);
			}
			cur_v = cur_v->next;
		}
		cur_s = cur_s->next;
	}
	return (0);
}

void find_portal(t_env *env, t_draw *draw, t_vertex *temp, t_sector *temp_s)
{
	t_sector *cur_s;
	t_vertex *cur_v;
	int i;
//				*** ***
// 				 -   -
//				\_____/

	i = 0;
	cur_s = draw->head;
	while (cur_s)
	{
		i++;
//		printf("sectors %d | %p  |  %p\n", i, cur_s, temp_s);
		cur_v = cur_s->vertexes;
		while (cur_v)
		{
//			printf("|---------------------\nx1 = %d y1 = %d\n x2 = %d y2 = %d\n", cur_v->xy1.x, cur_v->xy1.y,cur_v->xy2.x,cur_v->xy2.y);
//			printf("---------------------|\nx1 = %d y1 = %d\n x2 = %d y2 = %d\n\n\n", temp->xy1.x,temp->xy1.y,temp->xy2.x,temp->xy2.y);
			if (((temp->xy1.x == cur_v->xy1.x &&
				 temp->xy1.y == cur_v->xy1.y &&
				 temp->xy2.x == cur_v->xy2.x &&
				 temp->xy2.y == cur_v->xy2.y)
				|| (temp->xy1.x == cur_v->xy2.x &&
					temp->xy1.y == cur_v->xy2.y &&
					temp->xy2.x == cur_v->xy1.x &&
					temp->xy2.y == cur_v->xy1.y)) && (cur_s != temp_s))
			{
				new_portal(draw, temp, temp_s, cur_s);
//				line(temp->xy1, temp->xy2, env, RED);
//				printf("\n>>>>OCCURANCE<<<<\n", temp->xy1.x,temp->xy1.y,temp->xy2.x,temp->xy2.y);
			}
			cur_v = cur_v->next;
		}
		cur_s = cur_s->next;
	}
}

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

void delete_sector_from_list(t_env *env, t_draw *draw)
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
//		if(find_portal_for_draw(env, draw, cur_v, cur_s->next))
		//	printf("YDALI MENYA YA PORTAL\n");
//		delete_portal(draw, env, cur_v, cur_s->next);
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

void	pop_from_stack_to_list(t_env *env, t_draw *draw, t_stack **head)
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
		(draw->head->next != NULL) ? find_portal(env, draw, head_v, cur_s) : 0 == 0;
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
	pop_from_stack_to_list(env, draw, head);
	draw->s_count++;
}