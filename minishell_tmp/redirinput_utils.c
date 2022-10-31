/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirinput_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/10/31 15:37:42 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_stdin(t_data **data, t_cursors *crs)
{
	if (crs->input > 0)
	{
		crs->saved_stdin = dup(STDIN);
		dup2(crs->input, STDIN);
		builtin_execute(data, crs);
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
	builtin_execute(data, crs);
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
		path = ft_strjoin_2(cwd, "/");
		path = ft_strjoin(path, (*data)->cmds[crs->i2 + 1][0]);
		if (flag == 0)
		{
			input_error_msg(path, data, crs);
			free(path);
		}
		if (flag == 1)
		{
			input_error_msg_noexit(path, data, crs);
			crs->i2++;
		}
	}
}
