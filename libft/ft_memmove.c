/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <chaves_87@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 19:31:15 by acosta-a          #+#    #+#             */
/*   Updated: 2022/04/17 22:04:08 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	char	*s;
	char	*d;
	size_t	i;

	s = (char *) src;
	d = (char *) dest;
	i = 0;
	if (d > s)
	{
		while (size)
		{
			d[size - 1] = s[size - 1];
			size--;
		}
	}
	else
	{
		while (i < size)
		{
			d[i] = s[i];
			i++;
		}	
	}
	return (dest);
}
