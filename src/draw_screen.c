/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibohun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 21:38:26 by ggavryly          #+#    #+#             */
/*   Updated: 2019/08/23 19:53:37 by ibohun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	init_draw(t_draw_screen_calc *ds, t_player plr)
{
	unsigned	i;

	i = 0;
	ds->it->s = 0;
	ds->it->x = 0;
	ds->it->start_do = 1;
	while (i < W)
	{
		ds->i->y_bottom[i] = H - 1;
		ds->i->y_top[i] = 0;
		i++;
	}
	i = 0;
	ds->i->renderedsectors = (int *)malloc(sizeof(int) * plr.num_scts);
	while (i < plr.num_scts)
	{
		ds->i->renderedsectors[i] = 0;
		i++;
	}
	*ds->s->head = (t_item){plr.sector, 0, W - 1};
}

void	pick_sector_slice(t_draw_screen_calc *ds)
{
	ds->s->now = *ds->s->tail;
	if (++ds->s->tail == ds->queue + MAX_QUE)
		ds->s->tail = ds->queue;
}

void	rotate_view(t_draw_screen_calc *ds, t_game *g)
{
	ds->f->vx1 = ds->s->sect->vertex[ds->it->s + 0].x - g->plr.where.x;
	ds->f->vy1 = ds->s->sect->vertex[ds->it->s + 0].y - g->plr.where.y;
	ds->f->vx2 = ds->s->sect->vertex[ds->it->s + 1].x - g->plr.where.x;
	ds->f->vy2 = ds->s->sect->vertex[ds->it->s + 1].y - g->plr.where.y;
	ds->f->pcos = g->plr.anglecos;
	ds->f->psin = g->plr.anglesin;
	ds->f->tx1 = ds->f->vx1 * ds->f->psin - ds->f->vy1 * ds->f->pcos;
	ds->f->tz1 = ds->f->vx1 * ds->f->pcos + ds->f->vy1 * ds->f->psin;
	ds->f->tx2 = ds->f->vx2 * ds->f->psin - ds->f->vy2 * ds->f->pcos;
	ds->f->tz2 = ds->f->vx2 * ds->f->pcos + ds->f->vy2 * ds->f->psin;
}
