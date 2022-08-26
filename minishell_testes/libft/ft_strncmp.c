/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 00:30:22 by mcesar-d          #+#    #+#             */
/*   Updated: 2022/04/22 23:13:34 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t size)
{
	if (size == 0)
		return (0);
	while (*s1 != '\0' && *s2 != '\0' && size - 1 > 0)
	{
		if (*s1 != *s2)
		{
			break ;
		}
		s1++;
		s2++;
		size--;
	}	
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
