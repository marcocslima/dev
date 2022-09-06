/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/09/06 02:40:40 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "minishell.h"

//funciona parcialmente, ela não imprimi mais de 1 argumento
/*
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
*/

int	len_input(char **p)
{
	t_cursors	*crs;

	init_crs(&crs);
	while(p[crs->l])
		crs->l++;
	return (crs->l);
}

void	ft_echo(t_data **data, char **input)
{
	t_cursors	*crs;

	init_crs(&crs);
	crs->len = len_input(input);
	if (!input[0] || input[0][0] == '\0')
	{
		write(1, "\n", 1);
		(*data)->exit_return = 1;
	}
	while(crs->i < crs->len -1)
	{
		while (input[crs->i][crs->j] && input[crs->i][crs->j] == ' ')
			crs->j++;
		if (input[crs->i][crs->j] == '-' && input [crs->i][crs->j + 1] == 'n')
		{
			crs->flag = 1;
			crs->i += 3;
		}
		input[crs->i] = ft_substr(input[crs->i], crs->i, ft_strlen(input[crs->i]) - crs->i);
		ft_putstr_fd (input[crs->i], 1);
		if (crs->flag == 0)
			write (1, "\n", 1);
		(*data)->exit_return = 0;
		crs->i++;
	}
}
