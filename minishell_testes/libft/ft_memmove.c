/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 21:58:25 by mcesar-d          #+#    #+#             */
/*   Updated: 2022/04/28 11:25:15 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	int	i;

	if (!dest && !src)
		return (0);
	i = 0;
	if ((size_t)dest - (size_t)src < size)
	{
		i = (int) size - 1;
		while (i >= 0 && i < (int) size)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i--;
		}
	}
	else
	{
		ft_memcpy(dest, src, size);
	}
	return (dest);
}
