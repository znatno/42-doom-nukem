/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   record_data_b.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vopolonc <vopolonc@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 16:52:04 by vopolonc          #+#    #+#             */
/*   Updated: 2019/08/31 16:52:16 by vopolonc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke_nukem_editor.h"

char			*gena_pidor(t_rec_sec *walk_s, char *tmp)
{
	tmp = ft_strcpy(tmp, "sector ");
	num_cat(&tmp, (int)walk_s->floor);
	tmp = ft_strcat(tmp, " ");
	num_cat(&tmp, (int)walk_s->ceil);
	tmp = ft_strcat(tmp, "\t");
	return (tmp);
}

t_index			*walk_sv_while(t_index *walk_sv, char *tmp)
{
	while (walk_sv && walk_sv->next)
	{
		tmp = ft_strcat(tmp, " ");
		num_cat(&tmp, walk_sv->index);
		walk_sv = walk_sv->next;
	}
	return (walk_sv);
}

t_portal		*walk_sp_while(t_portal *walk_sp, char *tmp)
{
	while (walk_sp)
	{
		tmp = ft_strcat(tmp, " ");
		((walk_sp->wall_portal == -1) ? (tmp = ft_strcat(tmp, "-1"))
	: (num_cat(&tmp, walk_sp->wall_portal)));
		walk_sp = walk_sp->next;
	}
	return (walk_sp);
}

void			sector_record(t_rec_sec *head_s, int fd)
{
	t_rec_sec	*walk_s;
	t_index		*walk_sv;
	t_portal	*walk_sp;
	char		*tmp;

	walk_s = head_s;
	tmp = (char *)malloc(sizeof(char) * 256);
	ft_bzero(tmp, 256);
	while (walk_s)
	{
		gena_pidor(walk_s, tmp);
		walk_sv = walk_s->head_ind;
		walk_sp = walk_s->head_por;
		walk_sv = walk_sv_while(walk_sv, tmp);
		tmp = ft_strcat(tmp, "\t");
		walk_sp = walk_sp_while(walk_sp, tmp);
		tmp = ft_strcat(tmp, "\n");
		write(fd, tmp, ft_strlen(tmp));
		ft_bzero(tmp, 256);
		walk_s = walk_s->next;
	}
	free(tmp);
}
