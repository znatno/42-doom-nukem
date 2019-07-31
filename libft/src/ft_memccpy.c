/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 18:01:12 by ggavryly          #+#    #+#             */
/*   Updated: 2018/10/29 16:02:05 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			iterr;
	unsigned char	*dst1;
	unsigned char	*src1;

	dst1 = (unsigned char *)dst;
	src1 = (unsigned char *)src;
	iterr = 0;
	while (iterr < n)
	{
		dst1[iterr] = src1[iterr];
		if (src1[iterr] == (unsigned char)c)
			return (dst1 + iterr + 1);
		iterr++;
	}
	return (NULL);
}
