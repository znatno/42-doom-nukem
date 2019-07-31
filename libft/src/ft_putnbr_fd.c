/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggavryly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 17:29:36 by ggavryly          #+#    #+#             */
/*   Updated: 2018/10/31 23:22:46 by ggavryly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_minus(long int *n, int fd)
{
	ft_putchar_fd('-', fd);
	*n *= -1;
}

void			ft_putnbr_fd(int n, int fd)
{
	long int t;

	t = n;
	if (t < 0)
		ft_minus(&t, fd);
	if (t >= 10)
	{
		ft_putnbr_fd(t / 10, fd);
		ft_putchar_fd(t % 10 + '0', fd);
	}
	else
		ft_putchar_fd(t + '0', fd);
}
