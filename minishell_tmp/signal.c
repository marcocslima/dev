/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/10/01 06:58:01 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int	input)
{
	char	cwd[4097];

	if (input == SIGINT)
	{
		getcwd(cwd, 4096);
		ft_putstr_fd("\n", 1);
		ft_putstr_fd(cwd, 1);
		ft_putstr_fd( ": " , 1);
		signal(SIGINT, signal_handler);
	}
}

void	child_signal_handler(int input)
{
	if (input == SIGINT)
		write(2, "\n", 1);
}
