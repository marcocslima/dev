/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:43:17 by mcesar-d          #+#    #+#             */
/*   Updated: 2022/09/17 20:09:28 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(int e)
{
	char *erros[] = {"OK", "unclosed quotes"};
	ft_putstr_fd("Error: ", 1);
	ft_putstr_fd(erros[e], 1);
	ft_putstr_fd("\n", 1);
}
