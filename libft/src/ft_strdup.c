/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 15:21:10 by ggavryly          #+#    #+#             */
/*   Updated: 2018/10/27 15:27:01 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		i;
	char	*t;

	i = 0;
	if (!src)
		return (0);
	while (src[i])
		i++;
	t = (char *)malloc(sizeof(*src) * (i + 1));
	if (t == NULL)
		return (0);
	i = 0;
	while (src[i])
	{
		t[i] = (char)src[i];
		i++;
	}
	t[i] = '\0';
	return (t);
}
