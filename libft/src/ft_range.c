/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 19:43:56 by ggavryly          #+#    #+#             */
/*   Updated: 2018/11/04 19:43:57 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_range(int min, int max)
{
	int	i;
	int g;
	int	*h;

	h = NULL;
	if (min < max)
	{
		i = max - min;
		g = 0;
		if ((h = (int *)malloc(sizeof(int) * i)) != NULL)
		{
			while (g < i)
				h[g++] = min++;
		}
	}
	return (h);
}
