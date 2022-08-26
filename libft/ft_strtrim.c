/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <chaves_87@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 19:31:15 by acosta-a          #+#    #+#             */
/*   Updated: 2022/04/18 03:43:10 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_checkchar(char a, char const *set)
{
	int	len;

	len = ft_strlen(set);
	while (len >= 0)
	{
		if (set[len] == a)
			return (1);
		len--;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	unsigned int	len;
	char			*x;

	start = 0;
	if (s1[0] == '\0')
	{
		x = (char *)malloc(1);
		x[0] = '\0';
		return (x);
	}
	len = ft_strlen(s1);
	while (s1[start] && ft_checkchar(s1[start], set))
		start++;
	while (s1[len - 1] && ft_checkchar(s1[len], set) && len > start)
		len --;
	if (start > len || len == 0)
	{
		x = (char *)malloc(1);
		x[0] = '\0';
		return (x);
	}
	return (ft_substr((char *)s1, start, len + 1 - start));
}
