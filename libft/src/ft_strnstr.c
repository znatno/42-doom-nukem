/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 14:33:01 by ggavryly          #+#    #+#             */
/*   Updated: 2018/10/31 17:34:08 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hayst, const char *need, size_t l)
{
	char	*h;
	size_t	size;

	h = (char *)hayst;
	size = ft_strlen(need);
	if (*need == '\0')
		return ((char *)hayst);
	while (*hayst && l >= size)
	{
		if (ft_strncmp(hayst, need, size) == 0)
		{
			return ((char *)hayst);
		}
		hayst++;
		l--;
	}
	return (NULL);
}
