/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 17:53:45 by ggavryly          #+#    #+#             */
/*   Updated: 2019/02/05 17:53:47 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static uintmax_t	swap_sign(intmax_t value, int *sign, uintmax_t base)
{
	uintmax_t res;

	if (value < 0 && base == 10)
	{
		*sign = 1;
		res = -value;
	}
	else
		res = value;
	return (res);
}

static	int			numbers(uintmax_t value, uintmax_t base)
{
	int i;

	i = 0;
	while (value >= base)
	{
		value /= base;
		i++;
	}
	return (i);
}

char				*itoa_base(intmax_t value, uintmax_t base, char a_a32)
{
	int			i;
	char		*str;
	uintmax_t	tmp;
	int			sign;

	sign = 0;
	tmp = swap_sign(value, &sign, base);
	i = numbers(tmp, base);
	if (!(str = (char *)malloc(sizeof(char) * (i + 1 + sign))))
		return (NULL);
	str[i + 1 + sign] = '\0';
	if (sign)
		str[0] = '-';
	while (i >= 0)
	{
		value = tmp % base;
		str[i + sign] = (value >= 10) ? value - 10 + a_a32 : value + '0';
		tmp /= base;
		i--;
	}
	return (str);
}

char				*itoa_base_u(uintmax_t value, uintmax_t base, char a_a32)
{
	int			i;
	char		*str;
	uintmax_t	tmp;

	tmp = value;
	i = numbers(tmp, base);
	str = (char *)malloc(sizeof(char) * (i + 1));
	str[i + 1] = '\0';
	while (i >= 0)
	{
		value = tmp % base;
		str[i] = (value >= 10) ? value - 10 + a_a32 : value + '0';
		tmp /= base;
		i--;
	}
	return (str);
}
