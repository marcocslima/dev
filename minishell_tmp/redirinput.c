/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirinput.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/10/23 11:30:50 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_input(t_data **data, t_cursors *crs)
{
	pid_t	pid;

	if (!ft_strncmp((*data)->cmds[crs->i2][crs->j2], "<", 2) && !ft_strncmp
			((*data)->cmds[crs->i2 + 1][0], "<", 1))
	{
		crs->flag = 1;
		crs->j2 = 1;
		ft_here_doc(data, crs);
		return ;
	}
	if (crs->flagpipe == 8 && (*data)->cmds[crs->i2 + 1] && (*data)->cmds
		[crs->i2 + 1][1] && !ft_strncmp((*data)->cmds[crs->i2 + 1][1], "|",
			2))
	{
//		crs->flagpipe = 0;
		ft_pipe(data, crs->i2, crs->flagpipe, crs);
		crs->i2 += 2;
	}
	if (((*data)->cmds[crs->i2][0] && !(*data)->cmds[crs->i2][1]) ||
		((*data)->cmds[crs->i2][1] && (*data)->cmds[crs->i2 + 1][1] &&
			ft_strncmp((*data)->cmds[crs->i2][1], "<", 2) && ft_strncmp
				((*data)->cmds[crs->i2 + 1][1], "<", 2)))
//		{
		builtin_execute(data, crs->i2, 1, crs);
//		exit(0);
//		}
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
//			crs->flagpipe = 10;
//		}
	if (crs->flagpipe == 10)
		return ;
	pid = fork();
	if (pid == 0)
	{
		crs->flagfork = 1;
		if (((*data)->cmds[crs->i2][2] && !ft_strncmp((*data)->cmds[crs->i2]
				[2], "<", 2) && ft_strncmp((*data)->cmds[crs->i2 + 1][0], "<",
			2)) || (!(*data)->cmds[crs->i2][2] && (*data)->cmds[crs->i2][1] &&
			!ft_strncmp((*data)->cmds[crs->i2][1], "<", 2) && ft_strncmp((*data)
			->cmds[crs->i2 + 1][0], "<", 2)) || (!ft_strncmp((*data)->cmds
			[crs->i2][1], (*data)->cmds[0][1], 2)))
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
//				crs->input = 1;
				builtin_execute(data, crs->i2, crs->flag, crs);
			}
			else
				crs->input = open((*data)->cmds[crs->i2 + 1][0], O_RDONLY,
						S_IRWXU);
		}
		if (((*data)->cmds[crs->i2 + 2] && (*data)->cmds[crs->i2 + 2][0]
			&& !ft_strncmp((*data)->cmds[crs->i2 + 2][0], ">", 2)) || ((*data)
			->cmds[crs->i2 + 1] && (*data)->cmds[crs->i2 + 1][1] && !ft_strncmp
			((*data)->cmds[crs->i2 + 1][1], ">", 2)))
		{
			ft_in_output(data, crs);
			return ;
		}
		no_input(data, crs, 0);
		redir_stdin(data, crs);
	}
	waitpid(pid, &crs->status, 0);
	if (WIFEXITED(crs->status))
        (*data)->exit_return = WEXITSTATUS(crs->status);
	if ((*data)->cmds[crs->i2 + 1] && (*data)->cmds[crs->i2 + 1][1] && (*data)
		->cmds[crs->i2 + 1][1][0] == '>')
	{
		crs->i2 += 3;
//		crs->j2--;
	}
	else if ((*data)->cmds[crs->i2][2] && (*data)->cmds[crs->i2][2][0] == '|')
		return ;
	else
		crs->i2 += 2;
}

void	ft_in_output(t_data **data, t_cursors *crs)
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
		ft_putstrs("bash:", (*data)->cmds[crs->i2][1],
			": No such file or directory", STDERR);
		(*data)->exit_return = 1;
		return ;
	}
	redir_stdin_out(data, crs);
}

void	redir_stdin(t_data **data, t_cursors *crs)
{
	if (crs->input > 0)
	{
		crs->saved_stdin = dup(STDIN);
		dup2(crs->input, STDIN);
		builtin_execute(data, crs->i2, crs->flag, crs);
		dup2(crs->saved_stdin, STDIN);
		close(crs->saved_stdin);
		close(crs->input);
	}
}

void	redir_stdin_out(t_data **data, t_cursors *crs)
{
	crs->saved_stdin = dup(STDIN);
	dup2(crs->input, STDIN);
	crs->saved_stdout = dup(STDOUT);
	dup2(crs->output, STDOUT);
	builtin_execute(data, crs->i2, crs->flag, crs);
	dup2(crs->saved_stdout, STDOUT);
	dup2(crs->saved_stdin, STDIN);
	close(crs->saved_stdin);
	close(crs->input);
	close(crs->output);
	close(crs->saved_stdout);
}

void	no_input(t_data **data, t_cursors *crs, int flag)
{
	char	cwd[4096];
	char	*path;

	if (crs->input == -1)
	{
		getcwd(cwd, 4096);
		path = ft_strdup(cwd);
		path = ft_strjoin_2(cwd, "/");
		path = ft_strjoin_2(path, (*data)->cmds[crs->i2 + 1][0]);
		if (flag == 0)
		{
			input_error_msg(path);
			free(path);
		}
		if (flag == 1)
		{
			input_error_msg_noexit(path);
			crs->i2++;
		}
		//free(path); // MUDEI PARA A LINHA 175
	}
}
