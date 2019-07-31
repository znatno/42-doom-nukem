/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 18:55:38 by ggavryly          #+#    #+#             */
/*   Updated: 2018/10/29 15:57:13 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ss1;
	unsigned char	*ss2;
	size_t			iter;

	iter = 0;
	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	while (iter < n)
	{
		if (ss1[iter] != ss2[iter])
			return (ss1[iter] - ss2[iter]);
		iter++;
	}
	return (0);
}
