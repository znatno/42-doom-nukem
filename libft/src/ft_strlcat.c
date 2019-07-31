/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 11:39:30 by ggavryly          #+#    #+#             */
/*   Updated: 2018/10/28 11:58:18 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	res;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (dst[i] && i < size)
		i++;
	res = i;
	while (src[i - res] && i < size - 1)
	{
		dst[i] = src[i - res];
		i++;
	}
	if (res < size)
		dst[i] = '\0';
	return (res + ft_strlen(src));
}
