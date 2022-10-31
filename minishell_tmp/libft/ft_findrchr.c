/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_findrchr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 10:15:53 by acosta-a          #+#    #+#             */
/*   Updated: 2022/10/30 10:15:55 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_findrchr(const char *s, int c)
{
	int	len_str;

	len_str = ft_strlen(s) - 1;
	if (s == NULL)
		return (0);
	if (c > 255)
		return (0);
	if (c == 0)
		return (0);
	while (len_str >= 0)
	{
		if (s[len_str] == 0 && s[len_str] != c)
			return (0);
		if (s[len_str] == c)
			return (len_str);
		len_str--;
	}
	return (0);
}
