/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/08/14 01:13:21 by acosta-a         ###   ########.fr       */
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
	//	open_prompt(data->envp);
		signal(SIGINT, signal_handler);
	}
}
