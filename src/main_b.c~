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
			if (!(find_portal_for_draw(env, draw, cur_v, cur_s)))
				delete_portal(draw, cur_v);
			line(cur_v->xy1, cur_v->xy2, env, WHITE);
			cur_v = cur_v->next;
		}
		cur_s = cur_s->next;
	}
	if (draw->portals != NULL)
		draw_all_portals(env, draw);
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

t_sector 			*check_player_select_mode(t_env *env, t_draw *draw)
{
	clear_screen(env);
	if (draw->place_p.x > 4 && (draw->place_p.y > 4) && draw->head && draw->s_mode)
		draw_texture((t_xy) {.x = draw->place_p.x * 10 - 19, .y =  draw->place_p.y * 10 - 19}, PLAYER, 0xfffffff, env);
	draw_desk(env);
	return (draw->head);
}

t_sector		*select_sector_mode(t_env *env, t_draw *draw, int key, int i)
{
	t_sector 	*cur_s;
	t_vertex 	*cur_v;
	t_sector 	*save;

	cur_s = check_player_select_mode(env, draw);
	while (draw->head != NULL && cur_s && ++i && (cur_v = cur_s->vertexes))
	{
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
	(draw->portals != NULL) ? draw_all_portals(env, draw) : 0 == 0;
	return (save);
}