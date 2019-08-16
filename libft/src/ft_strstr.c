/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 12:42:06 by ggavryly          #+#    #+#             */
/*   Updated: 2018/10/31 18:12:53 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t size;

	size = ft_strlen(needle);
	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack)
	{
		if (ft_strncmp(haystack, needle, size) == 0)
		{
			return ((char *)haystack);
		}
		haystack++;
	}
	return (NULL);
}
