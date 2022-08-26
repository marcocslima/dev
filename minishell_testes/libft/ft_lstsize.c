/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 21:45:08 by mcesar-d          #+#    #+#             */
/*   Updated: 2022/04/17 22:06:11 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		counter;

	if (!lst)
		return (0);
	counter = 0;
	while (lst->next)
	{	
		lst = lst->next;
		counter++;
	}
	return (++counter);
}
