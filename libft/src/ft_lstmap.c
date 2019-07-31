/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 16:24:26 by ggavryly          #+#    #+#             */
/*   Updated: 2018/10/31 17:10:18 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*map;
	t_list	*rot;

	if (lst && f)
	{
		rot = f(lst);
		map = rot;
		while (lst->next)
		{
			lst = lst->next;
			if (!(map->next = f(lst)))
				return (NULL);
			map = map->next;
		}
		return (rot);
	}
	return (NULL);
}
