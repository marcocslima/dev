/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/09/17 17:35:00 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_cmds(t_data **data, t_cursors *crs, int c)
{
	crs->i = 0;
	while((*data)->cmds[c][crs->i])
		crs->i++;
	return (crs->i);
}

//checando qual comando de input
int	cmd_check(t_data **data)
{
	t_cursors *crs;

	init_crs(&crs);
	while((*data)->cmds[++crs->l])
	{
		if (!ft_memcmp((*data)->cmds[crs->l][0], "echo", 5))
		{
			crs->flag = 0;
			ft_echo(data, (*data)->cmds[crs->l], crs);
		}
		else if (!ft_memcmp((*data)->cmds[crs->l][0], "pwd", 4))
			ft_pwd();
		else if (!ft_memcmp((*data)->cmds[crs->l][0], "cd", 3))
			ft_cd(data, (*data)->cmds[crs->l][1]);
		else if (!ft_memcmp((*data)->cmds[crs->l][0], "export", 7))
			ft_export(data, (*data)->cmds[crs->l][1]);
		else if (!ft_memcmp((*data)->cmds[crs->l][0], "unset", 6))
			ft_unset(data, (*data)->cmds[crs->l][1]);
		crs->len = len_cmds(data, crs, crs->l);
		if((*data)->cmds[crs->l] && *(*data)->cmds[crs->l][crs->len - 1] != ';')
			break;
	}
	return (0);
}
