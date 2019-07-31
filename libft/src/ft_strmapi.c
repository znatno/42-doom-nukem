/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 17:51:17 by ggavryly          #+#    #+#             */
/*   Updated: 2018/10/29 18:01:30 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*res;
	unsigned int	i;

	i = 0;
	if (s && (res = malloc(ft_strlen(s) + 1)))
	{
		while (s[i])
		{
			res[i] = f(i, *(s + i));
			i++;
		}
		res[i] = '\0';
		return (res);
	}
	return (NULL);
}
