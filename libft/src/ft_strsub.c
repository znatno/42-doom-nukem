/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 18:08:25 by ggavryly          #+#    #+#             */
/*   Updated: 2018/10/29 18:18:01 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *res;
	char *fnl;

	if (s && (res = malloc(len + 1)))
	{
		fnl = res;
		while (s[start] && len-- > 0)
		{
			*res++ = s[start];
			start++;
		}
		*res = '\0';
		return (fnl);
	}
	return (NULL);
}
