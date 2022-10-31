/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/10/30 09:11:26 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_input(char **p)
{
	char		slicers[4];
	int			ret;
	t_cursors	*crs;

	ft_strlcpy(slicers, ";|<>", 4);
	init_crs(&crs);
	while (p[++crs->l])
		continue ;
	while (++crs->m < 4)
	{
		if (*p[crs->l - 1] == slicers[crs->m])
		{
			crs->l--;
			break ;
		}
	}
	ret = crs->l;
	free(crs);
	return (ret);
}

void	echo_preper(t_data **data, char **input, t_cursors	*crs)
{
	(*data)->exit_return = 0;
	crs->len = len_input(input);
	if (!input[0] || input[0][0] == '\0')
	{
		write(1, "\n", 1);
		(*data)->exit_return = 1;
	}
	crs->i = 0;
	crs->j = 0;
	if ((*data)->qtd_cmds > 1)
		(*data)->qtd_cmds--;
}

void	rotate_char(t_data **data, char *param, char c)
{
	t_cursors	*crs;
	char		*new;

	init_crs(&crs);
	crs->len = ft_strlen(param) + 1;
	new = ft_calloc(crs->len, sizeof(char));
	(*data)->tmp2 = new;
	while (crs->counter <= crs->len - 1)
	{
		if (param[crs->counter] == '\\' && param[crs->counter + 1] == c)
		{
			new[crs->i] = param[crs->counter + 1];
			crs->i++;
			crs->counter++;
			crs->len = crs->len - 1;
		}
		else if (param[crs->counter] != c)
		{
			new[crs->i] = param[crs->counter];
			crs->i++;
		}
		crs->counter++;
	}
	free(crs);
}

void	handle_quotes_middle(char *param, t_cursors *c)
{
	while (param[++c->l])
	{
		if (param[c->l] == '"')
		{
			if (c->l > 0 && param[c->l - 1] != '\\')
				c->i++;
			else if (c->l == 0)
				c->i++;
		}
		else if (param[c->l] == '\'')
		{
			if (c->l > 0 && param[c->l - 1] != '\\')
				c->j++;
			else if (c->l == 0)
				c->j++;
		}
	}
}

int	handle_quotes(t_data **data, char *param, t_cursors *crs)
{
	t_cursors	*c;

	init_crs(&c);
	if (param[0] == '"' || param[0] == '\'')
		handle_quotes_middle(param, c);
	c->len = c->i + c->j;
	if (c->len % 2 != 0)
		return (1);
	if (param[0] == '"' || param[0] == '\'')
		c->q = param[0];
	rotate_char(data, param, c->q);
	free(c);
	crs->w = ft_strlen((*data)->tmp2) + 1;
	crs->m = -1;
	return (0);
}

char	*get_value(char **envp, char var[], int n)
{
	t_cursors	*crs;
	char		**cp_env;
	char		tmp[n];

	init_crs(&crs);
	while (++crs->l < n)
		tmp[crs->l] = var[crs->l];
	cp_env = copy_env(envp, 3);
	while (cp_env[crs->l])
		crs->l++;
	while (--crs->l > 0 && ft_strncmp(tmp, *cp_env, n))
		cp_env++;
	if (crs->l == 0)
		return (0);
	free(crs);
	return (*cp_env + n + 1);
}

void	print_echo(t_data **data, t_cursors *crs, char **input, char tp[])
{
	crs->s = 0;
	while (tp[crs->s])
	{
		if (input[crs->i][0] != '\'' && tp[crs->s] == '$' && tp[crs->s + 1]
		!= ' ')
		{
			while (tp[crs->s + crs->counter] && tp[crs->s
					+ crs->counter] != ' ' && tp[crs->s + crs->counter]
				!='"' && tp[crs->s + crs->counter] != '\'')
		crs->counter++;
		crs->ret = get_value((*data)->envp, &tp[crs->s + 1], crs->counter - 1);
			if (crs->ret)
			{
				ft_putstr_fd(crs->ret, 1);
				crs->s = crs->s + crs->counter;
			}
		}
		if (crs->s < crs->m)
			ft_putchar_fd(tp[crs->s], 1);
		crs->s++;
		if (tp[crs->s] == '\0' && crs->len - crs->i > 1)
			ft_putchar_fd(' ', 1);
	}
	free((*data)->tmp2);
}

void	echo_input(t_data **data, t_cursors *crs)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 1;
	k = 0;
	while ((*data)->cmds[0][k])
		k++;
	k--;
	while (i < crs->k2 - 1 && (*data)->cmds[i])
	{
		if ((*data)->cmds[i] && (*data)->cmds[i][2]
			&& !ft_memcmp((*data)->cmds[i][2], "<", 2) && (*data)->cmds[i + 1]
			&& (*data)->cmds[i + 1][1] && ft_memcmp((*data)->cmds[i + 1][1]
				, "|", 2) && ft_memcmp((*data)->cmds[i + 1][1], "<", 2))
				crs->input = open((*data)->cmds[i + 1][0], O_RDONLY, S_IRWXU);
		no_input(data, crs, 0);
		i++;
		echo_input_change(data, k, i, j);
		i++;
	}
	crs->flag = 5;
	crs->i2 += 3;
}

void	echo_input_change(t_data **data, int k, int i, int j)
{
	while ((*data)->cmds[i][j])
	{
		(*data)->cmds[0][k] = (*data)->cmds[i][j];
		(*data)->cmds[i][j] = NULL;
		j++;
		k++;
	}
	(*data)->cmds[0][k] = 0;
}

void	ft_echo(t_data **data, char **input, t_cursors	*crs)
{
	char	tp[4097];

	if (crs->input != 0)
		echo_input(data, crs);
	echo_preper(data, input, crs);
	while (++crs->i < crs->len)
	{
		crs->counter = 0;
		if (input[crs->i][crs->j] == '-' && input [crs->i][crs->j + 1] == 'n')
		{
			crs->flagecho = 1;
			crs->i++;
		}
		crs->err = handle_quotes(data, input[crs->i], crs);
		while (++crs->m < crs->w)
			tp[crs->m] = (*data)->tmp2[crs->m];
		tp[crs->m] = '\0';
		if (crs->err == 0)
			print_echo(data, crs, input, tp);
		else
			print_error(crs->err);
	}
	if (crs->flagecho == 0)
		write (1, "\n", 1);
}
