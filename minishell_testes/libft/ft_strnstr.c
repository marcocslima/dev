/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <chaves_87@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 12:47:58 by acosta-a          #+#    #+#             */
/*   Updated: 2022/04/17 22:36:21 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t size)
{
	size_t	i;
	size_t	j;

	if (*s2 == '\0' || ft_strlen(s2) == 0)
		return ((char *)s1);
	i = 0;
	while (s1[i] && i < (size))
	{
		j = 0;
		while (s1[j + i] == s2[j] && i + j < size)
		{
			if (s2[j + 1] == '\0')
				return ((char *)&s1[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
