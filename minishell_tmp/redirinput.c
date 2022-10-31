/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirinput.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/10/31 15:34:56 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_input(t_data **data, t_cursors *crs)
{
	pid_t	pid;

	ft_input_doc_pipe(data, crs);
	if (crs->flagpipe == 10 || crs->flag == 5 || crs->flag == 1
		|| crs->flagpipe == 9)
		return ;
	pid = fork();
	if (pid == 0)
	{
		ft_fork_1(data, crs);
		if (!ft_in_output(data, crs))
			return ;
		no_input(data, crs, 0);
		redir_stdin(data, crs);
	}
	waitpid(pid, &crs->status, 0);
	if ((*data)->cmds[crs->i2 + 1] && (*data)->cmds[crs->i2 + 1][1] && (*data)
		->cmds[crs->i2 + 1][1][0] == '>')
		crs->i2 += 3;
	else if ((*data)->cmds[crs->i2][2] && (*data)->cmds[crs->i2][2][0] == '|')
		return ;
	else
		crs->i2 += 2;
}

void	ft_input_doc_pipe(t_data **data, t_cursors *crs)
{
	if (!ft_strncmp((*data)->cmds[crs->i2][crs->j2], "<", 2) && !ft_strncmp
			((*data)->cmds[crs->i2 + 1][0], "<", 1))
	{
		crs->flag = 1;
		crs->j2 = 1;
		dup2(crs->saved_stdin, STDIN);
		ft_here_doc(data, crs);
		return ;
	}
	if (crs->flagpipe == 8 && (*data)->cmds[crs->i2 + 1] && (*data)->cmds
		[crs->i2 + 1][1] && !ft_strncmp((*data)->cmds[crs->i2 + 1][1], "|",
			2))
	{
		ft_pipe(data, crs->i2, crs->flagpipe, crs);
		crs->flagpipe = 9;
		crs->i2 += 2;
	}
	ft_doc_pipe_2(data, crs);
}

void	ft_doc_pipe_2(t_data **data, t_cursors *crs)
{
	if ((*data)->cmds[crs->i2] && (((*data)->cmds[crs->i2][0] && !(*data)->cmds
			[crs->i2][1]) || ((*data)->cmds[crs->i2][1] && (*data)->cmds[crs->i2
			+ 1] && (*data)->cmds[crs->i2 + 1][1] && ft_strncmp((*data)->cmds
			[crs->i2][1], "<", 2) && ft_strncmp ((*data)->cmds[crs->i2 + 1][1],
				"<", 2))))
	{
		crs->flag = 1;
		builtin_execute(data, crs);
	}
	if (crs->flag == 5)
		return ;
	while ((*data)->cmds[crs->i2 + 1] && (*data)->cmds[crs->i2 + 1][1] &&
		!ft_strncmp((*data)->cmds[crs->i2 + 1][1], "<", 2))
	{
		(*data)->cmds[crs->i2 + 1][0] = ft_clean_quotes((*data)->cmds
			[crs->i2 + 1][0], '\'');
			crs->input = open((*data)->cmds[crs->i2 + 1][0], O_RDONLY,
				S_IRWXU);
		no_input(data, crs, 1);
		crs->i2++;
		(*data)->cmds[crs->i2][0] = ft_strdup((*data)->cmds[0][0]);
		if (ft_strncmp((*data)->cmds[0][1], "<", 2))
			(*data)->cmds[crs->i2][1] = ft_strdup((*data)->cmds[0][1]);
	}
}

void	ft_fork_1(t_data **data, t_cursors *crs)
{
	crs->flagfork = 1;
	if (((*data)->cmds[crs->i2] && (*data)->cmds[crs->i2][2] && !ft_strncmp
		((*data)->cmds[crs->i2][2], "<", 2) && ft_strncmp((*data)->cmds[crs->i2
		+ 1][0], "<", 2)) || (!(*data)->cmds[crs->i2][2] && (*data)->cmds
		[crs->i2][1] && !ft_strncmp((*data)->cmds[crs->i2][1], "<", 2)
		&& ft_strncmp((*data)->cmds[crs->i2 + 1][0], "<", 2)) || (!ft_strncmp
		((*data)->cmds[crs->i2][1], (*data)->cmds[0][1], 2)))
	{
		crs->o = ft_findrchr((*data)->cmds[crs->i2 + 1][0], ' ');
		if (crs->o >= 1 && (*data)->cmds[crs->i2 + 1][1])
			(*data)->cmds[crs->i2 + 1][0] = ft_strchr((*data)->cmds[crs->i2
					+ 1][0], ' ');
		(*data)->cmds[crs->i2 + 1][0] = ft_clean_quotes((*data)->cmds
			[crs->i2 + 1][0], '\'');
		if (crs->o >= 1 && (*data)->cmds[crs->i2 + 1][1])
		{
			(*data)->cmds[0][1] = ft_strdup ((*data)->cmds[crs->i2 + 1][0]);
			builtin_execute(data, crs);
		}
		else
			crs->input = open((*data)->cmds[crs->i2 + 1][0], O_RDONLY,
					S_IRWXU);
	}
}

int	ft_in_output(t_data **data, t_cursors *crs)
{
	if (((*data)->cmds[crs->i2 + 2] && (*data)->cmds[crs->i2 + 2][0]
		&& !ft_strncmp((*data)->cmds[crs->i2 + 2][0], ">", 2)) || ((*data)
			->cmds[crs->i2 + 1] && (*data)->cmds[crs->i2 + 1][1] && !ft_strncmp
			((*data)->cmds[crs->i2 + 1][1], ">", 2)))
	{
		if (!ft_strncmp((*data)->cmds[crs->i2 + 1][crs->j2], ">", 2)
			&& !ft_strncmp((*data)->cmds[crs->i2 + 2][0], ">", 2))
			crs->output = open((*data)->cmds[crs->i2 + 2][1], O_CREAT
					| O_WRONLY | O_APPEND, S_IRWXU);
		else if (!ft_strncmp((*data)->cmds[crs->i2 + 1][crs->j2], ">", 2)
			&& ft_strncmp((*data)->cmds[crs->i2 + 2][0], ">", 2))
		crs->output = open((*data)->cmds[crs->i2 + 2][0], O_CREAT | O_WRONLY
					| O_TRUNC, S_IRWXU);
		if (crs->output == -1)
		{
			ft_putstrs("minishell:", (*data)->cmds[crs->i2][1],
				": No such file or directory", STDERR);
			(*data)->exit_return = 1;
			return (0);
		}
		redir_stdin_out(data, crs);
		return (0);
	}
	return (1);
}
