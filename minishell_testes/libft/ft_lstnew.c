/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <chaves_87@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 20:51:23 by acosta-a          #+#    #+#             */
/*   Updated: 2022/04/22 22:04:38 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*value;

	value = malloc (sizeof(t_list));
	if (value == NULL)
		return (NULL);
	value->content = content;
	value->next = NULL;
	return (value);
}
