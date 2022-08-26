/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 11:44:29 by mcesar-d          #+#    #+#             */
/*   Updated: 2022/05/01 11:21:13 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	unsigned char	*dest_aux;
	unsigned char	*src_aux;
	size_t			index;

	if (!dest && !src)
		return (NULL);
	dest_aux = (unsigned char *)dest;
	src_aux = (unsigned char *)src;
	index = 0;
	while (index < size)
	{
		*dest_aux = *src_aux;
		dest_aux++;
		src_aux++;
		index++;
	}
	return (dest);
}
