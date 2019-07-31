/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 12:28:52 by ggavryly          #+#    #+#             */
/*   Updated: 2018/10/28 12:40:05 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *l;

	l = NULL;
	while (*s)
	{
		if (*s == (char)c)
		{
			l = (char *)s;
			s++;
		}
		else
			s++;
	}
	if ((char)c != '\0')
		return (l);
	else
		return ((char *)s);
	return (l);
}
