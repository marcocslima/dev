/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/09/28 14:57:32 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*here_doc_str(t_data **data, t_cursors *crs)
{
	char	*temp;

	temp = NULL;
	crs->len = ft_strlen((*data)->cmds[crs->i2 + 1][1]);
	while (!crs->str || ft_strncmp(temp, (*data)->cmds[crs->i2 + 1][1],
		crs->len))
	{
		temp = readline("> ");
		if (!ft_strncmp(temp, (*data)->cmds[crs->i2 + 1][1], crs->len))
			return (crs->str);
		crs->str = ft_strjoin(crs->str, temp);
		crs->str = ft_strjoin(crs->str, "\n");
	}
	return (crs->str);
}

void	ft_here_doc(t_data **data, t_cursors *crs)
{
	int		fd[2];

	if (pipe(fd) == -1)
	{
		(*data)->exit_return = 1;
		return ;
	}
	crs->str = here_doc_str(data, crs);
	if (!crs ->str)
	{
		crs->i2++;
		return ;
	}
	if ((*data)->cmds[crs->i2 + 2] && ft_strncmp((*data)->cmds[crs->i2 + 1][2],
		";", 1))
		ft_here_doc_2(data, crs, fd);
	else
	{
		write (fd[1], crs->str, ft_strlen(crs->str));
		close (fd[1]);
		dup2(fd[0], STDIN);
		builtin_execute(data, crs->i2, crs->flag, crs);
		crs->i2 += 2;
	}
}

void	ft_here_doc_2(t_data **data, t_cursors *crs, int fd[2])
{
	if (!ft_strncmp((*data)->cmds[crs->i2 + 1][crs->j2 + 1], ">", 2) &&
		!ft_strncmp((*data)->cmds[crs->i2 + 2][0], ">", 2))
		crs->output = open((*data)->cmds[crs->i2 + 2][1], O_CREAT
				| O_WRONLY | O_APPEND, S_IRWXU);
	else if (!ft_strncmp((*data)->cmds[crs->i2 + 1][crs->j2 + 1], ">", 2) &&
		ft_strncmp((*data)->cmds[crs->i2 + 2][0], ">", 2))
		crs->output = open((*data)->cmds[crs->i2 + 2][0], O_CREAT | O_WRONLY
				| O_TRUNC, S_IRWXU);
	crs->saved_stdout = dup(STDOUT);
	dup2(crs->output, STDOUT);
	write (fd[1], crs->str, ft_strlen(crs->str));
	close (fd[1]);
	dup2(fd[0], STDIN);
	close (fd[0]);
	builtin_execute(data, crs->i2, crs->flag, crs);
	dup2(crs->saved_stdout, STDOUT);
	close(crs->saved_stdout);
	crs->i2 += 3;
	crs->j2--;
}
