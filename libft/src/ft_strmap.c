/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 17:35:34 by ggavryly          #+#    #+#             */
/*   Updated: 2018/10/29 17:50:51 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*res;
	char	*fnl;

	if (s && (res = malloc(ft_strlen(s) + 1)))
	{
		fnl = res;
		while (*s)
		{
			*res++ = f(*s++);
		}
		*res = '\0';
		return (fnl);
	}
	return (NULL);
}
