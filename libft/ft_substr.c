/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <chaves_87@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 12:47:58 by acosta-a          #+#    #+#             */
/*   Updated: 2022/06/14 04:00:34 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*dest;
	size_t	lens;

	i = 0;
	lens = ft_strlen(s);
	if (start >= lens)
		dest = (char *)malloc(1);
	else if (len >= lens)
		dest = (char *)malloc(lens - start + 1);
	else
		dest = (char *)malloc (len + 1);
	if (!dest)
		return ((char *)s);
	while (start < lens && i < len)
	{
		dest[i] = s[start];
		i++;
		start++;
	}
	dest [i] = '\0';
	return (dest);
}
