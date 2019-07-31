/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 19:05:19 by ggavryly          #+#    #+#             */
/*   Updated: 2018/10/29 19:05:21 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	size_t	start;
	size_t	final;
	size_t	i;

	if (s)
	{
		i = 0;
		while (s[i] && (WHTSPC))
			i++;
		start = i;
		final = i;
		while (s[i])
		{
			while (s[i] && (WHTSPC))
				i++;
			while (s[i] && !(WHTSPC))
			{
				i++;
				final = i;
			}
		}
		return (ft_strsub(s, start, final - start));
	}
	return (NULL);
}
