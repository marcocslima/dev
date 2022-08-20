/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <chaves_87@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 19:31:15 by acosta-a          #+#    #+#             */
/*   Updated: 2022/04/22 20:40:39 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	size_t			i;
	char			*dest2;
	char			*src2;

	i = 0;
	dest2 = (char *) dest;
	src2 = (char *) src;
	if (!dest && !src)
		return (NULL);
	while (i < size)
	{
		dest2[i] = src2[i];
		i++;
	}
	return (dest);
}
