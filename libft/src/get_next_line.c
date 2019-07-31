/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 22:09:43 by ggavryly          #+#    #+#             */
/*   Updated: 2018/11/21 17:04:24 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_findline(char **fds, const int fd, char **line)
{
	size_t	i;
	char	*res;

	i = 0;
	res = NULL;
	if (!fds && !fds[fd])
		return (0);
	if (!(fds[fd][0]))
	{
		ft_strdel(fds + fd);
		return (0);
	}
	while (fds[fd][i] && fds[fd][i] != '\n')
		i++;
	*line = ft_strsub(fds[fd], 0, i);
	if (ft_strlen(fds[fd]) > (i + 1))
		res = ft_strdup(fds[fd] + (++i));
	ft_strdel(fds + fd);
	fds[fd] = res;
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static char	*fds[1024];
	char		*res;
	char		buf[BUFF_SIZE + 1];
	int			t;

	if (fd < 0 || !line || fd > 500000)
		return (-1);
	if (fds[fd] == NULL)
		fds[fd] = ft_strnew(1);
	while ((t = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[t] = '\0';
		res = ft_strjoin(fds[fd], buf);
		ft_strdel(fds + fd);
		fds[fd] = res;
		if (ft_strchr(buf, '\n'))
			return ((ft_findline(fds, fd, line)));
	}
	if (t < 0)
	{
		ft_strdel(fds + fd);
		return (-1);
	}
	return (ft_findline(fds, fd, line));
}
