/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/09/18 02:14:14 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "minishell.h"

char	*here_doc_str(t_data **data, t_cursors *crs)
{
	crs->len = ft_strlen((*data)->cmds[crs->i2 + 1][1]);
	while (!crs ->str || ft_strncmp(crs->temp, (*data)->cmds[crs->i2 + 1][1], crs->len))
	{
	//	crs->temp = crs->str;
	//	crs->str = ft_strjoin(crs->str, crs->str);
	//	free (crs->str);
		crs->temp = readline("> ");
//		if (!crs ->str && !ft_strncmp(crs->temp, (*data)->cmds[crs->i + 1][1], crs->len))
//			return (0);
		if (!ft_strncmp(crs->temp, (*data)->cmds[crs->i2 + 1][1], crs->len))
			return (crs->str);
		crs->str = ft_strjoin(crs->str, crs->temp);
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
			crs->i++;;
			return ;
		}
		crs->output = open((*data)->cmds[crs->i2 + 2][0], O_CREAT
					| O_WRONLY | O_TRUNC, S_IRWXU);
		crs->saved_stdout = dup(STDOUT);
		dup2(crs->output, STDOUT);
//		write (crs->output, crs->str, ft_strlen(crs->str));
		write (fd[1], crs->str, ft_strlen(crs->str));
		close (fd[1]);
		dup2(fd[0], STDIN);
		builtin_execute(data, crs->i2, crs->flag, crs);
		dup2(crs->saved_stdout, STDOUT);
		close(crs->saved_stdout);
		crs->i++;
	//	close(crs->input);
//	}
//		free(crs->c[1]);
//		close(fd(STDOUT));
//	}
//	return (crs->str);
}
