/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <chaves_87@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 19:31:15 by acosta-a          #+#    #+#             */
/*   Updated: 2022/04/07 14:50:19 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t size)
{
	size_t			i;
	unsigned char	*s1pt;
	unsigned char	*s2pt;

	s1pt = (unsigned char *)s1;
	s2pt = (unsigned char *)s2;
	i = 0;
	if (size == 0)
		return (0);
	while (*s1pt == *s2pt && (i < size - 1))
	{
		s1pt++;
		s2pt++;
		i++;
	}
	return ((unsigned char)*s1pt - (unsigned char)*s2pt);
}
