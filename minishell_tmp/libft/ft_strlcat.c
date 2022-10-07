/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 00:33:29 by mcesar-d          #+#    #+#             */
/*   Updated: 2022/10/03 23:43:06 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	if (size <= ft_strlen(dest))
		return (size + ft_strlen(src));
	i = ft_strlen(dest);
	j = 0;
	while (src[j] != '\0' && i + 1 < size)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (ft_strlen(dest) + ft_strlen(src + j));
}
*/
size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t len;
	size_t len1;
	size_t i;

	len = ft_strlen(src);
	len1 = ft_strlen(dest);
	i = 0;
	if (size <= len1)
		return (len + size);
	else
		len += len1;
	while (src[i] != 0 && len1 + 1 < size)
	{
		dest[len1] = src[i];
		len1++;
		i++;
	}
	dest[len1] = 0;
	return (len);
}
