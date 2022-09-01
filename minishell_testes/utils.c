/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 11:59:29 by acosta-a          #+#    #+#             */
/*   Updated: 2022/08/30 02:51:51 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_2(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*dest;

	i = 0;
	j = 0;
	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	dest = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	if (s1)
		while (s1[i] != '\0')
			dest[i++] = s1[j++];
	j = 0;
	while (s2[j])
		dest[i++] = s2[j++];
	dest[i] = '\0';
//	free(s1);
	return (dest);
}

void	reset_conters(t_cursors	**cursor)
{
	(*cursor)->counter	= 0;
	(*cursor)->flag		= 0;
}

void	init_crs(t_cursors	**cursor)
{
	(*cursor) = (t_cursors *)malloc(sizeof(t_cursors));
	(*cursor)->counter	= 0;
	(*cursor)->flag		= 0;
	(*cursor)->i 		= 0;
	(*cursor)->j 		= 0;
	(*cursor)->k 		= 0;
	(*cursor)->r 		= 0;
	(*cursor)->l 		= -1;
	(*cursor)->m 		= -1;
	(*cursor)->n 		= -1;
	(*cursor)->begin	= 0;
	(*cursor)->last		= 0;
	(*cursor)->c		= '\0';
	(*cursor)->q		= '\0';
	(*cursor)->h		= '\0';
	(*cursor)->len		= 0;
}
