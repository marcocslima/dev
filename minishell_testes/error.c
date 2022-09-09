/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:43:17 by mcesar-d          #+#    #+#             */
/*   Updated: 2022/09/09 14:55:38 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_error(int e)
{
	char *erros[] = {"OK", "quotes do not closed"};
	printf("%s %s\n", "Error: ", erros[e]);
}