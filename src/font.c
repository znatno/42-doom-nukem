/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibohun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 18:32:05 by ibohun            #+#    #+#             */
/*   Updated: 2019/08/18 23:01:05 by ibohun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

SDL_Color black = {0, 0, 0};
SDL_Color white = {255, 255, 255};

TTF_Font *get_font(char *filename, int size)
{
	TTF_Font *font;

	if (!(font = TTF_OpenFont(filename, size))) //todo remake
	{
		fprintf(stderr, "Unable to load ttf file: %s\n", SDL_GetError());
		exit(1);
	}
	return (font);
}
