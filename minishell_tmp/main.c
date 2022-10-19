/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/10/17 22:45:34 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env(char **envp, int add)
{
	int		i;
	int		len;
	char	**copy;

	len = 0;

	while (envp[len])
		len++;
	if (!(copy = (char **)ft_calloc(sizeof(char *), (len + add + 1))))
		return (0);
	i = -1;
	while (i++ < len - 1)
		copy[i] = ft_strdup(envp[i]);
	return (copy);
}

void	init_struct(t_data **data, char **argv, char **envp)
{
	(*data) = (t_data *)malloc(sizeof(t_data));
	(*data)->envp = copy_env(envp, 3);
	(*data)->argv = argv;
	(*data)->cmds = NULL;
	(*data)->dollar = NULL;
	(*data)->crs = 0;
	(*data)->qtd_cmds = 0;
}

void	open_prompt(char **envp)
{
//	char	*home;
	char	cwd[4097];
	char	*path;

	while (ft_memcmp("HOME=", *envp, 5))
		envp++;
//	home = *envp + 5;
	getcwd(cwd, 4096);
	path = ft_strdup(cwd);
/*	if (ft_memcmp(cwd, home, ft_strlen(home)))
		path = ft_strdup(cwd);
	else
		path = ft_strjoin_2("~", cwd + ft_strlen(home));*/
	ft_putstr_fd( path , 1);
	ft_putstr_fd( ": " , 1);
	free(path);
}

void		get_input(t_data **data)
{
	(*data)->input = (char *)ft_calloc(sizeof(char *), 4097);
	(*data)->input = readline(" ");
	add_history((*data)->input);
}

int	verify_quotes(t_data **data)
{
	t_cursors	*c;

	init_crs(&c);
	while ((*data)->input[++c->l])
		if ((*data)->input[c->l] == '"' && (*data)->input[c->l - 1] != '\\')
			c->i++;
		else if ((*data)->input[c->l] == '\'' && (*data)->input[c->l - 1] != '\\')
			c->j++;
	c->len = c->i + c->j;
	if (c->len % 2 != 0)
		return (1);
	free(c);
	return (0);
}

void input_preper(t_data **data)
{
	t_cursors *crs;
	char slicers[4] = ";|<>";
	char slicer;
	char *clean_pointer;

	init_crs(&crs);
	clean_pointer = (*data)->input; 
	(*data)->tmp = (char *)ft_calloc(sizeof(char *), 4097);
	crs->len = ft_strlen(slicers);
	if((*data)->input && (*data)->input[crs->i]) // TAVA DANDO SEGMENTATION FAULT
	{
		while((*data)->input[crs->i])
		{
			crs->l = -1;
			slicer = '\0';
			while(++crs->l < crs->len)
				if ((*data)->input[crs->i] == slicers[crs->l])
				{
					slicer = slicers[crs->l];
					break ;
				}
			if ((*data)->input[crs->i] == slicer && (*data)->input[crs->i - 1] != '\\')
			{

				(*data)->tmp[crs->j] = ' ';
				(*data)->tmp[crs->j + 1] = (*data)->input[crs->i];
				crs->j = crs->j + 2;
				if ((*data)->input[crs->i + 1] == (*data)->input[crs->i]
					&& (((*data)->input[crs->i] == '>') | ((*data)->input[crs->i] == '<')))
				{
					(*data)->tmp[crs->j] = (*data)->input[crs->i + 1];
					crs->i++;
					crs->j++;
				}
				(*data)->tmp[crs->j] = ' ';
			}
			else
				(*data)->tmp[crs->j] = (*data)->input[crs->i];
			crs->i++;
			crs->j++;
		}
	}

	(*data)->input = (*data)->tmp;
	free(clean_pointer);
	free(crs);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	int		ret_parser;
	int		ret_quotes;

	if (argc != 1)
		error_msg("Please type only one argument");
	init_struct(&data, argv, envp);
	signal(SIGQUIT, signal_handler);
	while (1)
	{
		open_prompt(data->envp);
		signal(SIGINT, signal_handler);
		get_input(&data);
		input_preper(&data);	
		data->slicers = ft_calloc(ft_strlen(data->input),sizeof(int));
		data->slicers_types = ft_calloc(ft_strlen(data->input),sizeof(int) + 1);
		ret_parser = parser(&data);
		ret_quotes = verify_quotes(&data);
		if (ret_parser + ret_quotes == 0)
			cmd_check(&data);
		else
			print_error(ret_quotes);
		clean_data(&data);
//		exit (0); //retirar
	}
	return (0);
}
