/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <chaves_87@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 12:47:58 by acosta-a          #+#    #+#             */
/*   Updated: 2022/04/12 16:28:39 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dest;

	i = 0;
	while (s[i])
		i++;
	dest = malloc ((i + 1) * sizeof (char));
	i = 0;
	if (dest == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest [i] = '\0';
	return (dest);
}
