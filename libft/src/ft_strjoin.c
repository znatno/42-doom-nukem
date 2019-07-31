/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 18:18:21 by ggavryly          #+#    #+#             */
/*   Updated: 2018/10/29 18:33:36 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	char	*res;
	char	*fnl;

	if (s1 && s2)
		size = ft_strlen(s1) + ft_strlen(s2) + 1;
	if ((s1 && s2) && (res = ft_strnew(size)))
	{
		fnl = res;
		while (size-- > 1)
		{
			if (*s1)
				*res++ = *s1++;
			else if (*s2)
				*res++ = *s2++;
		}
		*res = '\0';
		return (fnl);
	}
	return (NULL);
}
