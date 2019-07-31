/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 16:34:05 by ggavryly          #+#    #+#             */
/*   Updated: 2018/10/31 23:23:09 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_minus(long int *n)
{
	ft_putchar('-');
	*n *= -1;
}

void			ft_putnbr(int n)
{
	long int t;

	t = n;
	if (t < 0)
		ft_minus(&t);
	if (t >= 10)
	{
		ft_putnbr(t / 10);
		ft_putchar(t % 10 + '0');
	}
	else
		ft_putchar(t + '0');
}
