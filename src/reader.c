/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tprokysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 15:11:33 by tprokysh          #+#    #+#             */
/*   Updated: 2019/09/06 15:11:34 by tprokysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	reader_init(t_reader *read)
{
	read->posf.pos = 0;
	read->posf.value = 0;
	read->posf.is_y = 0;
	read->num_vertices = 0;
	read->vert = NULL;
}

void	reader(char *line, int fd, t_player *p, t_sector **sectors)
{
	t_reader *read;

	read = (t_reader *)malloc(sizeof(t_reader));
	reader_init(read);
	while (get_next_line(fd, &line) > 0)
	{
		read->posf.pos = 0;
		read->posf.value = 0;
		if ((read->posf.is_y = 1) && *line == 'v')
			read = reader_coroutine1(read, line);
		if (*line == 's')
		{
			*sectors = ft_realloc(*sectors, ++p->num_scts * sizeof(**sectors));
			read->sect = &((*sectors)[p->num_scts - 1]);
			read->num = NULL;
			read = reader_coroutine2(read, sectors, p, line);
			read = reader_coroutine3(read);
		}
		if (*line == 'p')
			read = reader_coroutine4(read, line, p, sectors);
		free(line);
	}
	free(read->vert);
	free(read);
}
