/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 13:55:08 by ggavryly          #+#    #+#             */
/*   Updated: 2018/10/29 15:46:34 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long int	res;
	long int	znk;

	res = 0;
	znk = 1;
	while (*str == 32 || (*str <= 13 && *str >= 9))
	{
		str++;
	}
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			znk = -1;
		str++;
	}
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (res * znk);
		else
			res = res * 10 + (long int)(*str - '0');
		str++;
	}
	return (res * znk);
}
