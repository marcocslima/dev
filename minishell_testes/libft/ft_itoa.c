/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <chaves_87@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 02:49:20 by acosta-a          #+#    #+#             */
/*   Updated: 2022/04/25 02:13:24 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_intlen(long i)
{
	long	len;

	len = 0;
	if (i < 0 || i == 0)
	{
		i = i * (-1);
		len++;
	}
	while (i >= 10)
	{
		i = i / 10;
		len++;
	}
	return (len + 1);
}

static	char	*ft_nzero(int x)
{
	char	*nzero;

	nzero = malloc(2 * sizeof(char));
	if (x == 0)
	{
		nzero[0] = '0';
		nzero[1] = '\0';
	}
	return (nzero);
}

char	*ft_itoa(int n)
{	
	int		i;
	char	*str;
	long	n2;

	n2 = n;
	i = ft_intlen(n2);
	if (n2 != 0)
		str = malloc((i + 1) * sizeof(char));
	if (n2 == 0)
		return (ft_nzero(n2));
	if (n2 < 0)
	{
		str[0] = '-';
		n2 = n2 * (-1);
	}
	if (n2 > 0)
		str[i--] = '\0';
	while (n2 > 0)
	{
		str[i--] = (n2 % 10) + '0';
		n2 = n2 / 10;
	}
	return (str);
}
