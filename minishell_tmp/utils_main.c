/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 10:35:15 by acosta-a          #+#    #+#             */
/*   Updated: 2022/10/30 10:37:53 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verify_quotes(t_data **data)
{
	t_cursors	*c;

	init_crs(&c);
	while ((*data)->input[++c->l])
	{
		if ((*data)->input[c->l] == '"' && (*data)->input[c->l - 1] != '\\')
			c->i++;
		else if ((*data)->input[c->l] == '\'' && (*data)->input[c->l - 1]
			!= '\\')
			c->j++;
	}
	c->len = c->i + c->j;
	if (c->len % 2 != 0)
		return (1);
	free(c);
	return (0);
}

void	init_struct(t_data **data, char **argv, char **envp)
{
	(*data) = (t_data *)malloc(sizeof(t_data));
	(*data)->envp = copy_env(envp, 3);
	(*data)->argv = argv;
	(*data)->cmds = NULL;
	(*data)->dollar = NULL;
	(*data)->crs = 0;
	(*data)->qtd_cmds = 0;
	(*data)->tmp = NULL;
	if ((*data)->tmp)
		free((*data)->tmp);
}
