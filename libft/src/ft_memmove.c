/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 18:17:57 by ggavryly          #+#    #+#             */
/*   Updated: 2018/10/29 16:04:16 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*s1;
	const char	*s2;

	s1 = dst;
	s2 = src;
	if (s1 > s2)
	{
		i = len;
		while (i > 0)
		{
			s1[i - 1] = s2[i - 1];
			i--;
		}
	}
	else if (s1 < s2)
		ft_memcpy(s1, s2, len);
	return ((void *)dst);
}
