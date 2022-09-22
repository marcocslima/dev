/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 17:54:49 by mcesar-d          #+#    #+#             */
/*   Updated: 2022/04/20 22:57:50 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t size)
{
	size_t	i;
	size_t	len_s;
	char	*nstr;

	len_s = ft_strlen(s);
	i = 0;
	if (start >= len_s)
		nstr = (char *)malloc(1);
	else if (size >= len_s)
		nstr = (char *)malloc(len_s - start + 1);
	else
		nstr = (char *)malloc(size + 1);
	if (!nstr)
		return ((char *)s);
	while (start < len_s && i < size)
		nstr[i++] = s[start++];
	nstr[i] = '\0';
	return (nstr);
}
