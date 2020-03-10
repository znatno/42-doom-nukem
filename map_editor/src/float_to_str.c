/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_to_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 15:16:20 by ggavryly          #+#    #+#             */
/*   Updated: 2019/08/04 15:16:22 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "duke_nukem_editor.h"

static void	float_put_before(char **str, int *len, long double k, int *iter)
{
	char	*tmp;
	int		len0;

	len0 = len[0];
	tmp = *str;
	*iter = len0;
	while (len0)
	{
		tmp[len0 - 1] = (((long long)(k)) % 10) + '0';
		len0--;
		k /= 10;
	}
	*str = tmp;
}

static void	float_put_after(char **str, int *len, long double k, int *iter)
{
	char	*tmp;
	int		len1;
	int		i;

	len1 = len[1];
	i = *iter;
	*iter += ((len1) ? (len1 - 1) : (0));
	tmp = *str;
	while (len1)
	{
		tmp[i++] = ((long long)(k * 10.0) % 10) + '0';
		len1--;
		k *= 10;
	}
	tmp[i - 1] += (((long long)(k * 10.0) % 10) >= 5) ? (1) : (0);
	*str = tmp;
}

static int	float_len_before(long double k)
{
	int len;

	len = 0;
	if (k > 1.0)
	{
		while (k > 1.0)
		{
			k /= 10.0;
			len++;
		}
	}
	else
	{
		len = 1;
	}
	return (len);
}

char		*ft_itof(long double k)
{
	int		len[2];
	int		t;
	char	*str;
	int		i;

	len[0] = float_len_before(k);
	len[1] = 1;
	i = 0;
	t = 1;
	if (!(str = (char *)malloc(sizeof(char) * len[0] + len[1] + 1 + t)))
		return (NULL);
	str[len[0] + len[1] + t] = '\0';
	float_put_before(&str, len, k, &i);
	str[len[0]] = '.';
	i++;
	float_put_after(&str, len, k, &i);
	return (str);
}
