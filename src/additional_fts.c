/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_fts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibohun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:05:45 by ibohun            #+#    #+#             */
/*   Updated: 2019/08/18 23:27:54 by ibohun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
**	Needs to prevent leaks on exit
*/

void	UnloadData(t_sector **sectors, t_player *plr)
{
	for (unsigned a = 0; a < plr->num_scts; ++a)
		free((*sectors)[a].vertex);
	for (unsigned a = 0; a < plr->num_scts; ++a)
		free((*sectors)[a].neighbors);
	free(*sectors);
	*sectors = NULL;
	plr->num_scts = 0;
	//todo All Font Closing
}

/*
** vline:
** Draw a vertical line on screen, with a different color pixel in top & bottom
*/

void	vline(int x, int y1, int y2, int color, t_player *plr)
{
	int *pix;

	pix = (int *)plr->sdl->buffer;
	y1 = clamp(y1, 0, H - 1);
	y2 = clamp(y2, 0, H - 1);
	if (y2 == y1)
		pix[y1 * W + x] = BLACK_COLOR; //нижня межа вікна
	else if (y2 > y1)
	{
		pix[y1 * W + x] = SEC_COLOR; //проміжок секторів
		if (y1 == 0 || y1 == 1)
			pix[y1 * W + x] = BLACK_COLOR; //верхня межа вікна
		for (int y = y1 + 1; y <= y2; ++y)
			pix[y * W + x] = color;
		pix[y2 * W + x] = color;
	}
}

/*
**	Quit
*/

int		exit_doom(t_game *g)
{
	if (g->error)
		ft_putendl_fd("text", 2);
	else
		ft_putendl("text");
	UnloadData(&g->sectors, &g->plr);
	SDL_Quit();
	TTF_Quit();
	exit(0);
}