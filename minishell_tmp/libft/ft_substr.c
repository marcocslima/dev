/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 17:54:49 by mcesar-d          #+#    #+#             */
/*   Updated: 2022/10/06 08:56:50 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*dest;
	size_t	lens;

	i = 0;
	if (s)
		lens = ft_strlen(s);
	else
		return (NULL);
	if (start >= lens)
		dest = (char *)malloc(1);
	else if (len >= lens)
		dest = (char *)malloc(lens - start + 2);
	else
		dest = (char *)malloc(lens + 1);
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

//deletar
/*
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ptr;
	unsigned int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (((char *)s)[i] != '\0')
		i++;
	if (i < start)
		return (ft_strdup(""));
	ptr = (char *)malloc(len + 2);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len)
		ptr[i++] = ((char *)s)[start++];
	ptr[i] = '\0';
	return (ptr);
}
*/

//deletar
