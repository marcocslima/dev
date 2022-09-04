/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/09/03 15:42:05 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "minishell.h"

//funciona parcialmente, ela não imprimi mais de 1 argumento
void	ft_echo(t_data **data, char *input)
{
	int		i;
	int		n_flag;

	i = 0;
	if (!input || input[0] == '\0')
	{
		write(1, "\n", 1);
		(*data)->exit_return = 1;
	}
	while (input[i] && input[i] == ' ')
		i++;
	if (input[i] == '-' && input [i + 1] == 'n')
	{
		n_flag = 1;
		i+=3;
	}
	input = ft_substr(input, i, ft_strlen(input) - i);
	ft_putstr_fd (input, 1);
	if (n_flag == 0)
		write (1, "\n", 1);
	(*data)->exit_return = 0;
}
