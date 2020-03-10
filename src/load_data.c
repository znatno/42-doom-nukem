/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibohun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 19:06:01 by ggavryly          #+#    #+#             */
/*   Updated: 2019/08/22 23:30:37 by ibohun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		check_file(int fd)
{
	if (fd == -1 || read(fd, 0, 0) < 0)
	{
		ft_putstr("empty file or it's directory\n");
		return (0);
	}
	return (1);
}

void	*ft_realloc(void *ptr, size_t size)
{
	char *newptr;

	if (!size && ptr)
	{
		if (!(newptr = (char *) malloc(1)))
			return (NULL);
		ft_memdel(&ptr);
		return (newptr);
	}
	if (!(newptr = (char *) malloc(size)))
		return (NULL);
	if (ptr)
	{
		ft_memcpy(newptr, ptr, size);
		ft_memdel(&ptr);
	}
	return (newptr);
}

t_posf	atof_posf(const char *s, t_posf posf)
{
	int exp = 0;
	int c;
	int sign = 1;
	int i = posf.pos;

	posf.value = 0.0;
	if (s[0 + posf.pos] == '-')
	{
		sign = -1;
		posf.pos++;
	}
	while ((c = s[0 + posf.pos++]) != '\0' && ISDIGIT(c))
	{
		posf.value = posf.value * 10.0 + (c - '0');
	}
	if (c == '.')
	{
		while ((c = s[0 + posf.pos++]) != '\0' && ISDIGIT(c))
		{
			posf.value = posf.value * 10.0 + (c - '0');
			exp = exp - 1;
		}
	}
	while (ISDIGIT(c))
	{
		i = i * 10 + (c - '0');
		c = s[0 + posf.pos++];
	}
	while (exp < 0)
	{
		posf.value *= 0.1;
		exp++;
	}

	posf.value *= sign;
	return (posf);
}

void	reader(char *line, int fd, t_player *p, t_sector **sectors)
{
	t_posf	posf;

	t_xy	*vert = NULL, v;
	int		n, NumVertices = 0;

	posf.pos = 0;
	posf.value = 0;
	posf.is_y = 0;
	while (get_next_line(fd, &line) > 0)
	{
		posf.pos = 0;
		posf.value = 0;
		if ((posf.is_y = 1) && *line == 'v')
		{
			while (line[posf.pos])
			{
				while (!ft_isdigit(line[posf.pos]))
				{
					posf.pos++;
				}
				vert = ft_realloc(vert, ++NumVertices * sizeof(*vert));
				if (posf.is_y)
				{
					posf = atof_posf(line, posf);
					vert[NumVertices - 1].y = posf.value;
					posf.y = posf.value;
					while (!ft_isdigit(line[posf.pos]))
					{
						posf.pos++;
					}
					posf = atof_posf(line, posf);
					vert[NumVertices - 1].x = posf.value;
					posf.is_y = 0;
				}
				else
				{
					posf = atof_posf(line, posf);
					vert[NumVertices - 1].x = posf.value;
					vert[NumVertices - 1].y = posf.y;
				}
				posf.pos--;
			}
		}
		if (*line == 's')
		{
			*sectors = ft_realloc(*sectors, ++p->num_scts * sizeof(**sectors));
			t_sector *sect = &(*sectors)[p->num_scts - 1];

			int *num = NULL;

			while (!ft_isdigit(line[posf.pos]))
			{
				posf.pos++;
			}
			posf = atof_posf(line, posf);
			sect->floor = posf.value;
			while (!ft_isdigit(line[posf.pos]))
			{
				posf.pos++;
			}
			posf = atof_posf(line, posf);
			sect->ceil = (int) posf.value;
			int all = 0;
			int len = ft_strlen(line);
			while (line[posf.pos] && len >= posf.pos)
			{
				while (!ft_isdigit(line[posf.pos]))
				{
					posf.pos++;
				}
				if (line[posf.pos - 1] == '-')
					posf.pos--;
				if (len >= posf.pos)
				{
					num = ft_realloc(num, ++all * sizeof(*num));
					posf = atof_posf(line, posf);
					num[all - 1] = (int)posf.value;
				}
			}
			sect->npoints = all /= 2;
			sect->neighbors = malloc((all) * sizeof(*sect->neighbors));
			sect->vertex = malloc((all + 1) * sizeof(*sect->vertex));
			n = 0;
			while (n < all)
			{
				sect->neighbors[n] = num[all + n];
				n++;
			}
			n = 0;
			while (n < all)
			{
				sect->vertex[n + 1] = vert[num[n]];
				n++;
			}
			sect->vertex[0] = sect->vertex[all];
			free(num);
		}
		if (*line == 'p')
		{
			while (!ft_isdigit(line[posf.pos]))
				posf.pos++;
			posf = atof_posf(line, posf);
			p->where.x = posf.value;
			posf = atof_posf(line, posf);
			p->where.y = posf.value;
			posf = atof_posf(line, posf);
			p->angle = posf.value;
			posf = atof_posf(line, posf);
			n = (int)posf.value;
			p->sector = n;
			p->where.z = (*sectors)[p->sector].floor + EYE_H;
		}
	}
	free(vert);
}

void	load_data(t_player *player, t_sector **sectors)
{
	int fd;
	char *line;

	line = ft_strnew(1);
	fd = open(FILE_NAME, O_RDONLY);
	if (!(check_file(fd)))
	{
		exit(-1);
	}
	reader(line, fd, player, sectors);
}
