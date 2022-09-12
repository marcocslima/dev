/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/09/12 11:23:41 by mcesar-d         ###   ########.fr       */
/*                                                                            */
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
	crs->len = ft_strlen(param) + 1;
	char	new[crs->len];
	ft_bzero(new, crs->len);
	(*data)->tmp = malloc(sizeof(size_t));
	(*data)->tmp = new;
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

int handle_quotes(t_data **data, char *param)
{
	t_cursors *c;
	
	init_crs(&c);
	if (param[0] == '"' || param[0] == '\'')
	{
		while (param[++c->l])
			if (param[c->l] == '"' && param[c->l - 1] != '\\')
				c->i++;
			else if (param[c->l] == '\'' && param[c->l - 1] != '\\')
				c->j++;
	}
	c->len = c->i + c->j;
	if(c->len % 2 != 0)
		return (1);
	if (param[0] == '"' || param[0] == '\'')
		c->q = param[0];
	rotate_char(data, param, c->q);
	return (0);
}

char	*get_value(char **envp, char *var)
{
	int len = ft_strlen(var);
	int i = 0;
	int ret;
	while (envp[i])
	{
		ret = ft_strncmp(var, *envp, len);
		i++;
	}
	while (--i > 0 && ft_strncmp(var, *envp, len))
		envp++;
	if (i == 0)
		return (0);
	return (*envp + len + 1);
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
		crs->err = handle_quotes(data, input[crs->i]);
		if (crs->err == 0)
		{
			while ((*data)->tmp[++crs->m])
			{
				if(input[crs->i][0] != '\'')
					if((*data)->tmp[crs->m] == '$' && (*data)->tmp[crs->m + 1] != ' ')
					{
						crs->pos = &(*data)->tmp[crs->m + 1];
						while((*data)->tmp[crs->m] && (*data)->tmp[crs->m] != ' ')
						{
							crs->counter++;
							crs->m++;
						}
						crs->pointer = ft_calloc(sizeof(char), crs->counter);
						ft_strlcpy(crs->pointer, crs->pos, crs->counter);
						crs->ret = get_value((*data)->envp, crs->pointer);
						if(crs->ret)
							ft_putstr_fd(crs->ret, 1);
						else
							crs->m =  crs->m - crs->counter;
					}
				ft_putchar_fd((*data)->tmp[crs->m], 1);
			}
			ft_putchar_fd(' ', 1);
			crs->m = -1;
		}
		else
			print_error(crs->err);
	}
	if (crs->flag == 0)
			write (1, "\n", 1);
	crs->flag = 0;
	(*data)->exit_return = 0;
}
