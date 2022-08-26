/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 06:49:55 by mcesar-d          #+#    #+#             */
/*   Updated: 2022/04/17 05:36:44 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*result;

	i = 0;
	result = (char *)malloc(ft_strlen(s) + 1);
	if (!s || !f || !result)
		return (NULL);
	ft_strlcpy(result, s, ft_strlen(s) + 1);
	while (result[i])
	{
		result[i] = (*f)(i, result[i]);
		i++;
	}
	return (result);
}
