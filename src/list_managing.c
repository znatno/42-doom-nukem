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

void print_all_portals(t_draw *draw)
{
	t_portals *cur_s;
	t_vertex *cur_line;

	cur_s = draw->portals;
	while (cur_s)
	{
		cur_line = cur_s->line;
			printf("x1 = %d y1 = %d \n x2 = %d y2 = %d\n\n",
				   cur_line->xy1.x, cur_line->xy1.y, cur_line->xy2.x,
				   cur_line->xy2.y);
		cur_s = cur_s->next;
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

void add_portal(t_draw *draw, t_sector *temp, t_vertex *cur_v, t_sector *cur_s)
{
	int i;
	t_portals *head;

	head = draw->portals;
	while (head->next != NULL)
		head = head->next;
	if (!(head->next = (t_portals *) malloc(sizeof(t_portals))))
		exit(111);
	head = head->next;
	head->sec_a = temp;
	head->sec_b = cur_s;
	head->line = cur_v;
//	printf("%d %d %d %d\n",draw->portals->line->xy1.x,draw->portals->line->xy1.y,
//		   draw->portals->line->xy2.x, draw->portals->line->xy2.y);
//	draw->portals = draw->portals->next;
//	printf("%d %d %d %d\n====================\n",draw->portals->line->xy1.x,draw->portals->line->xy1.y,
//		   draw->portals->line->xy2.x, draw->portals->line->xy2.y);
	head->next = NULL;
}

void create_portals_head(t_draw *draw, t_sector *temp, t_vertex *cur_v,
						 t_sector *cur_s)
{
	int i;
	t_portals *head;

	if (!(draw->portals = (t_portals *) malloc(sizeof(t_portals))))
		exit(167);
	head = draw->portals;
	head->sec_a = temp;
	head->sec_b = cur_s;
	head->line = cur_v;
	head->next = NULL;
	draw->portals = head;
//	printf("%d %d %d %d\n",draw->portals->line->xy1.x,draw->portals->line->xy1.y,
//		   draw->portals->line->xy2.x, draw->portals->line->xy2.y);
}

void find_portal(t_draw *draw, t_sector *temp)
{
	t_sector *cur_s;
	t_vertex *cur_v;
	int i;

	i = 0;
	cur_s = draw->head;
	while (cur_s)
	{
		cur_v = cur_s->vertexes;
		while (cur_v)
		{

//			printf("temp = %d, %d, %d, %d, | cur = %d, %d, %d, %d,\n\n",
//					temp->vertexes->xy1.x,temp->vertexes->xy1.y,temp->vertexes->xy2.x,
//					temp->vertexes->xy2.y,cur_v->xy1.x,cur_v->xy1.y,cur_v->xy2.x,cur_v->xy2.y);
			if ((temp->vertexes->xy1.x == cur_v->xy1.x &&
				 temp->vertexes->xy1.y == cur_v->xy1.y &&
				 temp->vertexes->xy2.x == cur_v->xy2.x &&
				 temp->vertexes->xy2.y == cur_v->xy2.y)
				|| (temp->vertexes->xy1.x == cur_v->xy2.x &&
					temp->vertexes->xy2.y == cur_v->xy1.y &&
					temp->vertexes->xy2.x == cur_v->xy1.x &&
					temp->vertexes->xy2.y == cur_v->xy1.y))
			{
				i++;
				if (draw->portals == NULL && i > 1)
				{
					printf("im here\n");
					create_portals_head(draw, temp, cur_v, cur_s);
				}
				else if (i > 1)
				{
					add_portal(draw, temp, cur_v, cur_s);
				}
			}

			cur_v = cur_v->next;
		}
		cur_s = cur_s->next;
	}
}

void add_sector_to_list(t_sector *temp, t_draw *draw)
{
	int i;
	t_vertex *head;

	while (temp->next != NULL)
		temp = temp->next;
	if (!(temp->next = (t_sector *) malloc(sizeof(t_sector))))
		exit(111);
	temp = temp->next;
	if (!(temp->vertexes = (t_vertex *) malloc(sizeof(t_vertex))))
		exit(167);
	head = temp->vertexes;
	i = 0;
	while (++i < I)
	{
		temp->vertexes->xy1.x = draw->f_p[i - 1].x;
		temp->vertexes->xy1.y = draw->f_p[i - 1].y;
		temp->vertexes->xy2.x = draw->f_p[i].x;
		temp->vertexes->xy2.y = draw->f_p[i].y;
		temp->vertexes->next = NULL;
		temp->next = NULL;
		find_portal(draw, temp);
		if (!(temp->vertexes->next = (t_vertex *) malloc(sizeof(t_vertex))))
			exit(168);
		temp->vertexes = temp->vertexes->next;
	}
	temp->vertexes->xy1.x = draw->f_p[i - 1].x;
	temp->vertexes->xy1.y = draw->f_p[i - 1].y;
	temp->vertexes->xy2.x = draw->f_p[0].x;
	temp->vertexes->xy2.y = draw->f_p[0].y;
	temp->vertexes->next = NULL;
	temp->vertexes = head;
	temp->next = NULL;
	draw->s_count++;
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


void create_sectors_list(t_env *env, t_draw *draw, t_sector *temp)
{
	int i;
	t_vertex *head;

	if (!(temp->vertexes = (t_vertex *) malloc(sizeof(t_vertex))))
		exit(167);
	head = temp->vertexes;
	i = 0;
	while (++i < I)
	{
		temp->vertexes->xy1.x = draw->f_p[i - 1].x;
		temp->vertexes->xy1.y = draw->f_p[i - 1].y;
		temp->vertexes->xy2.x = draw->f_p[i].x;
		temp->vertexes->xy2.y = draw->f_p[i].y;
//        printf("x1 = %d y1 = %d \n x2 = %d y2 = %d\n\n",
//               temp->vertexes->xy1.x, temp->vertexes->xy1.y, temp->vertexes->xy2.x, temp->vertexes->xy2.y);
		if (!(temp->vertexes->next = (t_vertex *) malloc(sizeof(t_vertex))))
			exit(168);
		temp->vertexes = temp->vertexes->next;
	}
	temp->vertexes->xy1.x = draw->f_p[i - 1].x;
	temp->vertexes->xy1.y = draw->f_p[i - 1].y;
	temp->vertexes->xy2.x = draw->f_p[0].x;
	temp->vertexes->xy2.y = draw->f_p[0].y;
	temp->vertexes->next = NULL;
	temp->vertexes = head;
	temp->next = NULL;
	draw->head = temp;
	draw->s_count++;
}