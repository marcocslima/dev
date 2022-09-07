/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/09/07 15:16:27 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "minishell.h"

int	len_input(char **p)
{
	t_cursors	*crs;

	init_crs(&crs);
	while(p[crs->l])
		crs->l++;
	return (crs->l);
}

void echo_preper(t_data **data, char **input, t_cursors	*crs)
{
	crs->len = len_input(input);
	if (!input[0] || input[0][0] == '\0')
	{
		write(1, "\n", 1);
		(*data)->exit_return = 1;
	}
	crs->i = 0;
	crs->j = 0;
	if((*data)->qtd_cmds > 1)
	{
		crs->len = crs->len -1;
		(*data)->qtd_cmds--;
	}
}

void	rotate_char(t_data ** data, char *param, char c)
{
	t_cursors	*crs;

	init_crs(&crs);
	crs->len = ft_strlen(param);
	char	new[crs->len];
	while (crs->k < crs->len)
	{
		new[crs->k] = 0;
		crs->k++;
	}
	ft_bzero((*data)->tmp, 10);
	while (crs->counter < crs->len)
	{
		if (param[crs->counter] != c)
		{
			new[crs->i] = param[crs->counter];
			crs->i++;
		}
		else if (param[crs->counter] == c && param[crs->counter] != '\'')
		{
			new[crs->i] = param[crs->counter + 1];
			crs->i++;
			crs->counter++;
		}
		crs->counter++;
	}
	(*data)->tmp = new;
	free(crs);
}

int handle_quotes(t_data **data, char *param)
{
	t_cursors *c;
	
	init_crs(&c);
	if (param[0] == '"' || param[0] == '\'')
	{
		while (param[++c->l])
			if (param[c->l] == '"')
				c->i++;
			else if (param[c->l] == '\'')
				c->j++;
	}
	if((c->i + c->j) % 2 != 0)
		return (1);
	if (param[0] == '"' || param[0] == '\'')
		c->flag = param[0];
	rotate_char(data, param, c->flag);
	return (0);
}

void	ft_echo(t_data **data, char **input, t_cursors	*crs)
{
	echo_preper(data, input, crs);
	while (++crs->i < crs->len)
	{
		while (input[crs->i][crs->j] && input[crs->i][crs->j] == ' ')
			crs->j++;
		if (input[crs->i][crs->j] == '-' && input [crs->i][crs->j + 1] == 'n')
		{
			crs->flag = 1;
			crs->i++;
		}
		int h = handle_quotes(data, input[crs->i]);
		if (h == 0)
			input[crs->i] = (*data)->tmp;
		if (crs->flag == 1 &&  crs->i == crs->len - 1)
			ft_putstr_fd (ft_strjoin(input[crs->i], ""), 1);
		else
			ft_putstr_fd (ft_strjoin(input[crs->i], " "), 1);
	}
	if (crs->flag == 0)
			write (1, "\n", 1);
	(*data)->exit_return = 0;
}
