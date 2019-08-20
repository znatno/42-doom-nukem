/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 13:59:22 by ggavryly          #+#    #+#             */
/*   Updated: 2019/08/04 13:59:24 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke_nukem_editor.h"

//char	*trim_itof(char *flt)
//{
//	int		i;
//
//	i = ft_strlen(flt);
//	if (flt[i - 1] == '0')
//	{
//		flt[i - 2] = '\0';
//		return (flt);
//	}
//	return (flt);
//}
//
//int		open_create_map()
//{
//	int 	fd;
//
//	fd = open("../maps/ya_karta.doom", O_WRONLY);
//	if (fd == -1)
//	{
//		system("touch ../maps/ya_karta.doom");
//		fd = open("../maps/ya_karta.doom", O_WRONLY);
//	}
//	return (fd);
//}
//
//void	vertex_record(t_xy *vertex, int num_vertex, int fd)
//{
//	int i;
//	char *tmp;
//
//	i = 0;
//	tmp = (char *)malloc(sizeof(char) * 256);
//	ft_bzero(tmp, 256);
//	while (i < num_vertex)
//	{
//		tmp = ft_strcpy(tmp, "vertex ");
//		tmp = ft_strcat(tmp , trim_itof(ft_itof(vertex[i].y)));
//		tmp = ft_strcat(tmp, " ");
//		tmp = ft_strcat(tmp, trim_itof(ft_itof(vertex[i].x)));
//		tmp = ft_strcat(tmp, "\n");
//		write(fd, tmp, ft_strlen(tmp));
//		ft_bzero(tmp, 256);
//		i++;
//	}
//}
//
//void	sector_record(t_sector *sectors, int num_sectors, int fd)
//{
//	int		i;
//	char 	*tmp;
//
//	i = 0;
//	tmp = (char *)malloc(sizeof(char) * 256);
//	ft_bzero(tmp, 256);
//	while (i < num_sectors)
//	{
//		tmp = ft_strcpy(tmp, "sector ");
//		tmp = ft_strcat(tmp, trim_itof((ft_itof(sectors->floor))));
//		tmp = ft_strcat(tmp, " ");
//		tmp = ft_strcat(tmp, trim_itof((ft_itof(sectors->ceil))));
//		tmp = ft_strcat(tmp, " ");
//		write(fd, tmp, ft_strlen(tmp));
//		ft_bzero(tmp, 256);
//		i++;
//	}
//}

void	player_record()
{
	//record player to file
}

void	record_to_file(t_record *rec)
{

}

//void	record_data(t_xy *vertex, int num_vertex, t_sector *sectors, int num_sectors)
//{
//	int fd;
//
//	fd = open_create_map();
//	vertex_record(vertex, num_vertex, fd);
//	sector_record(sectors, num_sectors, fd);
//	player_record(player, fd);
//	close(fd);
//}