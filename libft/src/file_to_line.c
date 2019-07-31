/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 16:04:42 by ggavryly          #+#    #+#             */
/*   Updated: 2018/12/15 16:04:45 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*file_to_line(const char *name)
{
	int		fd;
	char	*file;
	char	*tmp;
	int		i;
	char	buf[BUFF_SIZE + 1];

	i = 0;
	if ((fd = open(name, O_RDONLY)) == -1)
		return (NULL);
	file = ft_strnew(1);
	while ((i = read(fd, buf, BUFF_SIZE)))
	{
		if (i < 0)
		{
			ft_memdel((void **)&file);
			return (NULL);
		}
		buf[i] = '\0';
		tmp = ft_strjoin(file, buf);
		ft_memdel((void **)&file);
		file = tmp;
	}
	close(fd);
	return (file);
}
