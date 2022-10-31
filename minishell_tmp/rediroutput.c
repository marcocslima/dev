/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rediroutput.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/10/31 15:36:22 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_sep(char c)
{
	t_cursors	*crs;
	char		slicers[4];

	ft_strlcpy(slicers, ";|", 4);
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
	char		*jinput;

	init_crs(&c);
	jinput = ft_calloc(4097, sizeof(char));
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
					free(c);
					return (jinput);
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
	free(c);
	return (jinput);
}

void	ft_output_fork(t_data **data, t_cursors *crs, char *jc, char **ncmd)
{
	while (jc[++crs->l])
	{
		if (jc[crs->l] == '>' && jc[crs->l + 1] == '>')
			crs->output = open(ft_clean_quotes(ncmd[++crs->k], '\''),
					O_CREAT | O_WRONLY | O_APPEND, 0666);
		else if (jc[crs->l] == '>' && jc[crs->l + 1] != '>'
			&& jc[crs->l - 1] != '>')
			crs->output = open(ft_clean_quotes(ncmd[++crs->k], '\''),
					O_CREAT | O_WRONLY | O_TRUNC, 0666);
	}
	if (crs->output == -1)
	{
		ft_putstrs("bash:", (*data)->cmds[crs->i2][1],
			": No such file or directory", STDERR);
		(*data)->exit_return = 1;
		return ;
	}
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
		ft_output_fork(data, crs, jc, ncmd);
		ft_output_2(data, crs);
	}
	destroy_pointers_char(ncmd);
	free(jc);
	waitpid(pid, &crs->status, 0);
	if (WIFEXITED(crs->status))
		(*data)->exit_return = WEXITSTATUS(crs->status);
}

void	ft_output_2(t_data **data, t_cursors *crs)
{
	crs->saved_stdout = dup(STDOUT);
	dup2(crs->output, STDOUT);
	close(crs->output);
	builtin_execute(data, crs);
	dup2(crs->saved_stdout, STDOUT);
	close(crs->saved_stdout);
}
