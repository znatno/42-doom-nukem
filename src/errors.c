/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 14:41:45 by ggavryly          #+#    #+#             */
/*   Updated: 2019/08/01 14:41:47 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	error_box(char *title, char *sub_title, t_sdl_main *sdl)
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, sub_title,
			sdl->window);
}

void	exit_sdl(t_sdl_main *sdl)
{
	SDL_DestroyWindow(sdl->window);
	SDL_Quit();
}
