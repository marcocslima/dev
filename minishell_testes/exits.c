/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/08/13 11:51:07 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

int	error_msg(char *message)
{
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	exit(ERROR);
}

int	no_error_msg(char *message)
{
	ft_putstr_fd(message, 1);
	ft_putstr_fd("\n", 1);
//	if (stack->array_a[0])
	{
//		free(stack->array_a);
//		free(stack->array_b);
	}
	exit(0);
}
