/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <chaves_87@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:37:11 by acosta-a          #+#    #+#             */
/*   Updated: 2022/06/12 07:34:06 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb;

	{
		if (n < 0)
		{
			ft_putchar_fd('-', fd);
			nb = (unsigned int)(n * (-1));
		}
		else
			nb = (unsigned int)n;
		if (nb >= 10)
		{
			ft_putnbr_fd(nb / 10, fd);
			ft_putnbr_fd(nb % 10, fd);
		}
		if (nb < 10)
			ft_putchar_fd (nb + '0', fd);
	}
}
