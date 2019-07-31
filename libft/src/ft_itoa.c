/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 14:46:44 by ggavryly          #+#    #+#             */
/*   Updated: 2018/10/30 15:41:31 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_isneg(int *n, int *neg)
{
	if (*n < 0)
	{
		*n *= -1;
		*neg = 1;
	}
}

static char		*ft_limit(int n)
{
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else if (n == 2147483647)
		return (ft_strdup("2147483647"));
	return (NULL);
}

static char		*ft_zapis(char *num, size_t nul, int n, int neg)
{
	num[nul] = '\0';
	while (nul--)
	{
		num[nul] = n % 10 + '0';
		n /= 10;
	}
	if (neg)
		num[0] = '-';
	return (num);
}

char			*ft_itoa(int n)
{
	int			i;
	int			len;
	int			neg;
	char		*t;

	if (n == -2147483648 || n == 2147483647)
		return (ft_limit(n));
	i = n;
	len = 1;
	neg = 0;
	ft_isneg(&n, &neg);
	while (i /= 10)
		len++;
	if ((t = (char *)malloc(sizeof(char) * (len + neg) + 1)) != NULL)
	{
		ft_zapis(t, len + neg, n, neg);
		return (t);
	}
	return (NULL);
}
