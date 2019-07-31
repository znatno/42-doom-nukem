/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 13:47:56 by ggavryly          #+#    #+#             */
/*   Updated: 2018/10/31 13:47:58 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*res;

	if ((res = (t_list *)malloc(sizeof(t_list))) != NULL)
	{
		res->next = NULL;
		if (!(res->content = malloc(content_size)))
			return (NULL);
		if (!(content) || !(content_size))
		{
			res->content = NULL;
			res->content_size = 0;
		}
		else
		{
			res->content = ft_memcpy(res->content, content, content_size);
			res->content_size = content_size;
		}
		res->next = NULL;
		return (res);
	}
	return (NULL);
}
