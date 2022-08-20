/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <chaves_87@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 02:49:20 by acosta-a          #+#    #+#             */
/*   Updated: 2022/04/25 23:03:02 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *s)
{
	int	i;
	int	sign;
	int	number;

	sign = 1;
	i = 0;
	number = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	if (s[i] == '+' || s[i] == '-')
		if (s[i++] == '-')
			sign = -1;
	while ((s[i] >= '0') && (s[i] <= '9'))
	{
		number = number * 10 + (s[i] - '0');
		i++;
	}
	return (number * sign);
}
