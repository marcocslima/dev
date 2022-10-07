/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/10/06 08:50:46 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//Pode deletar essa função len_cmds?
int	len_cmds(t_data **data, t_cursors *crs, int c)
{
	crs->i2 = 0;
	while ((*data)->cmds[c][crs->i2])
		crs->i2++;
	return (crs->i2);
}

void	cmd_check(t_data **data)
{
	char		*cmd2;
	t_cursors	*crs;

	init_crs(&crs);
	cmd_check_2(data, crs);
	if (crs->i2 < crs->k2 && crs->i2 > 0 && (*data)->cmds[crs->i2][0]
		&& ft_strncmp((*data)->cmds[crs->i2][0], ">", 1) && (*data)->cmds
			[crs->i2 - 1][2] && ft_strncmp ((*data)->cmds[crs->i2 - 1][2], ">",
			1))
		cmd2 = ft_strdup((*data)->cmds[crs->i2][0]);
	if (crs->i2 > 0 && (*data)->cmds[crs->i2] && ft_strncmp((*data)->cmds
			[crs->i2][0], ">", 1) && (*data)->cmds[crs->i2 - 1][2] && ft_strncmp
				((*data)->cmds[crs->i2 - 1][2], ">", 1))
		cmd2 = ft_strjoin_2(cmd2, " ");
	if (crs->i2 < crs->k2 && crs->i2 > 0 && (*data)->cmds[crs->i2][1] &&
		ft_strncmp((*data)->cmds[crs->i2][0], ">", 1) && (*data)->cmds[crs->i2
			- 1][2] && ft_strncmp((*data)->cmds[crs->i2 - 1][2], ">", 1))
		cmd2 = ft_strjoin_2(cmd2, (*data)->cmds[crs->i2][1]);
	if (crs->i2 < crs->k2 && ft_memcmp((*data)->cmds[crs->i2][0], ">",
		2) && ft_memcmp((*data)->cmds[crs->i2][0], ">", 2))
	{
		crs->flag = 1;
		builtin_execute(data, crs->i2, crs->flag, crs);
	}
	dup2(crs->saved_stdin, STDIN);
	free(crs); // adicionado
}

void	cmd_check_2(t_data **data, t_cursors *crs)
{
	crs->saved_stdin = dup(STDIN);
	if ((*data)->cmds[crs->k2])
		while ((*data)->cmds[crs->k2])
			crs->k2++;
	while (crs->i2 < crs->k2 - 1 && (*data)->cmds[crs->i2])
	{
		crs->j2 = 0;
		crs->flag = 0;
		if ((*data)->cmds[crs->i2] && (*data)->cmds[crs->i2][0][0] == '>')
			crs->j2++;
		if (crs->i2 >= 1 && (*data)->cmds[crs->i2 - 1][2] && (*data)->cmds
			[crs->i2 - 1][2][0] == '>')
		{
			crs->i2++;
			crs->j2 = 0;
		}
		while (crs->i2 < crs->k2 && (*data)->cmds[crs->i2][crs->j2])
		{
			cmd_check_2_1(data, crs);
		}
		if (crs->i2 < crs->k2 - 1)
			crs->i2++;
	}
}

void	cmd_check_2_1(t_data **data, t_cursors *crs)
{
	if ((*data)->cmds[crs->i2][crs->j2] && !ft_memcmp((*data)->cmds
		[crs->i2][crs->j2], "|", 2))
		ft_pipe(data, crs->i2, crs->flag, crs);
	if ((*data)->cmds[crs->i2][crs->j2] && !ft_memcmp((*data)->cmds
		[crs->i2][crs->j2], ">", 2))
	{
		ft_output(data, crs);
		while((*data)->cmds[crs->w])
		{
			if((*(*data)->cmds[crs->w][0] == '>') | (*(*data)->cmds[crs->w][0] == '<'))
				crs->i2++;
			crs->w++;
		}
		crs->i2++;
	}
	while ((*data)->cmds[crs->i2] && (*data)->cmds[crs->i2][crs->j2] &&
		!ft_memcmp((*data)->cmds[crs->i2][crs->j2], "<", 2))
		ft_input(data, crs);
	if (crs->i2 < (*data)->qtd_cmds && (*data)->cmds[crs->i2]
		&& (*data)->cmds[crs->i2][crs->j2] &&
			!ft_memcmp((*data)->cmds[crs->i2][crs->j2], ";", 2))
	{
		crs->flag = 1;
		builtin_execute(data, crs->i2, crs->flag, crs);
	}
	crs->j2++;
}

void	builtin_execute(t_data **data, int i, int flag, t_cursors *crs)
{
	char	*cmd1;
	int		j;

	j = 1;
	if (((*data)->cmds[i][0] && crs->i > 0 && (*data)->cmds[i - 1][2] &&
		ft_strncmp((*data)->cmds[i - 1][2], ">", 1)) || ((*data)->cmds[i][0] &&
			crs->i == 0))
		cmd1 = ft_strdup((*data)->cmds[i][0]);
	while ((*data)->cmds[i] && (*data)->cmds[i][j])
	{
		if ((*data)->cmds[i][j] && ft_strncmp((*data)->cmds[i][j], "<", 1)
			&& ft_strncmp((*data)->cmds[i][j], ">", 1) && ft_strncmp((*data)
				->cmds[i][j], "|", 1) && ft_strncmp((*data)->cmds[i][j], ";",
					1))
		{
			cmd1 = ft_strjoin_2(cmd1, " ");
			cmd1 = ft_strjoin_2(cmd1, (*data)->cmds[i][j]);
		}
		j++;
	}
	if (!ft_memcmp((*data)->cmds[i][0], "echo", 5))
	{
		crs->flagecho = 0;
		ft_echo(data, (*data)->cmds[i], crs);
		if ((*data)->cmds[i][2] && ft_memcmp((*data)->cmds[i][1], "-n", 2) &&
			(*data)->cmds[i][2][0] != '\0' && ft_memcmp((*data)->cmds[i]
				[2], ";", 2))// adicionado por atila mas tem que estar
		exit(0);
	}
	else
		builtin_execute_2(data, i, flag, cmd1, crs);
}

void	builtin_execute_2(t_data **data, int i, int flag, char *cmd1, t_cursors *crs)
{
	if (!ft_memcmp((*data)->cmds[i][0], "./", 2) ||
			!ft_memcmp((*data)->cmds[i][0], "../", 3) ||
				!ft_memcmp((*data)->cmds[i][0], "/", 1))
		ft_bash(data);
	else if (!ft_memcmp((*data)->cmds[i][0], "pwd", 4))
		ft_pwd();
	else if (!ft_memcmp((*data)->cmds[i][0], "cd", 3))
		ft_cd(data, (*data)->cmds[i][1], i);
	else if (!ft_memcmp((*data)->cmds[i][0], "export", 7))
		ft_export(data, (*data)->cmds[i][1]);
	else if (!ft_memcmp((*data)->cmds[i][0], "unset", 6))
		ft_unset(data, (*data)->cmds[i][1]);
	else if (!ft_memcmp((*data)->cmds[i][0], "env", 4))
		ft_env(data, (*data)->cmds[i][1]);
	else if (!ft_memcmp((*data)->cmds[i][0], "exit", 5))
		ft_exit(data, crs);
	else if (flag == 0)
		execute(cmd1, data);
	else
		execute_pipe(cmd1, data);
}
