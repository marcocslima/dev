/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rediroutput.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/10/21 21:36:45 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void exec_output(t_cursors *crs)//(t_data **data, t_cursors *crs)
{
    int status, pid;
    int fd[2];

    pipe(fd);

    fd[1] = crs->output;
    pid = fork();
    if (pid == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);

        execlp("/usr/bin/ls", "ls", "-la", NULL);
    }
    close(fd[0]);
    close(fd[1]);
    waitpid(pid, &status, 0);
}
*/

int	check_sep(char c)
{
	t_cursors	*crs;
	char slicers[4]	= ";|";

	init_crs(&crs);
	while (crs->i < 2)
	{
		if (c == slicers[crs->i++])
		{
			free(crs);
			return (1);
		}
	}
	free(crs);
	return (0);
}

char	*join_cmds(t_data **data, int cmd)
{
	t_cursors	*c;
	char		*ret;
	char		jinput[4097];

	init_crs(&c);
	while ((*data)->cmds[cmd])
	{
		while ((*data)->cmds[cmd][c->j])
		{
			c->len = ft_strlen((*data)->cmds[cmd][c->j]);
			while (c->k < c->len)
			{
				if (check_sep((*data)->cmds[cmd][c->j][c->k]) == 1)
				{
					jinput[c->w] = '\0';
					ret = jinput;
					free(c);
					return (ret);
				}
				jinput[c->w] = (*data)->cmds[cmd][c->j][c->k];
				c->k++;
				c->w++;
			}
			c->k = 0;
			c->j++;
		}
		c->j = 0;
		cmd++;
	}
	jinput[c->w] = '\0';
	ret = jinput;
	free(c);
	return (ret);
}

void	ft_output(t_data **data, t_cursors *crs)
{
	pid_t	pid;
	char	*jc;
	char	**ncmd;

	jc = join_cmds(data, crs->i2);
	ncmd = ft_split(jc, '>');
	while (ncmd[crs->o])
		crs->o++;
	if ((*data)->qtd_cmds < crs->o + 1)
		(*data)->jump = crs->o;
	else
		(*data)->jump = crs->o + 1;
	pid = fork();
	if (pid == 0)
	{
		while (jc[++crs->l])
		{
			if (jc[crs->l] == '>' && jc[crs->l + 1] == '>')
				crs->output = open(ft_clean_quotes(ncmd[++crs->k], '\''), O_CREAT | O_WRONLY
						| O_APPEND, S_IRWXO);
			else if (jc[crs->l] == '>' && jc[crs->l + 1] != '>'
				&& jc[crs->l - 1] != '>')
				crs->output = open(ft_clean_quotes(ncmd[++crs->k], '\''), O_CREAT | O_WRONLY | O_TRUNC,
						S_IRWXO);
		}
		if (crs->output == -1)
		{
			ft_putstrs("bash:", (*data)->cmds[crs->i2][1],
				": No such file or directory", STDERR);
			(*data)->exit_return = 1;
			return ;
		}
		ft_output_2(data, crs);
	}
	waitpid(pid, &crs->status, 0);
	if ( WIFEXITED(crs->status) )
        (*data)->exit_return = WEXITSTATUS(crs->status);
}

void	ft_output_2(t_data **data, t_cursors *crs)
{
	crs->saved_stdout = dup(STDOUT);
	dup2(crs->output, STDOUT);
	close(crs->output);
	builtin_execute(data, crs->i2, crs->flag, crs);
	dup2(crs->saved_stdout, STDOUT);
	close(crs->saved_stdout);
}
