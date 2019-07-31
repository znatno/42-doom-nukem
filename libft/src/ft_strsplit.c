/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 20:32:20 by ggavryly          #+#    #+#             */
/*   Updated: 2018/10/31 23:26:08 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_delim(char const *s, char d)
{
	size_t		k;
	size_t		i;

	if (s)
	{
		i = 0;
		k = 0;
		while (s[i])
		{
			while (s[i] && s[i] == d)
				i++;
			if (s[i] && !(s[i] == d))
			{
				while (s[i] && !(s[i] == d))
					i++;
				k++;
			}
		}
		return (k);
	}
	return (0);
}

static int	ft_strln(const char *s, char d)
{
	int	i;

	i = 0;
	while (s[i] != d && s[i])
	{
		i++;
	}
	return (i);
}

char		**ft_strsplit(char const *s, char c)
{
	size_t		i;
	size_t		j;
	size_t		k;
	char		**res;

	j = 0;
	i = 0;
	k = ft_delim(s, c);
	if (s && (res = malloc(sizeof(char *) * k + 1)))
	{
		res[k] = NULL;
		k = 0;
		while (s[i])
		{
			while (s[i] == c && s[i])
				i++;
			j = ft_strln(s + i, c);
			if (s[i] && (res[k] = ft_strsub(s, i, j)))
				k++;
			while (s[i] != c && s[i])
				i++;
		}
		return (res);
	}
	return (NULL);
}
