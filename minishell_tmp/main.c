/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/10/30 10:37:48 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_prompt(char **envp)
{
	char	cwd[4097];
	char	*path;

	while (ft_memcmp("HOME=", *envp, 5))
		envp++;
	getcwd(cwd, 4096);
	path = ft_strdup(cwd);
	ft_putstr_fd(path, 1);
	ft_putstr_fd(": ", 1);
	free(path);
}

void	get_input(t_data **data)
{
	open_prompt((*data)->envp);
	signal(SIGINT, signal_handler);
	(*data)->tmp = readline(" ");
	if (!(*data)->tmp)
	{
		destroy_pointers_char((*data)->envp);
		free((*data));
		ft_putstr_fd("Thanks and bye bye\n", 1);
		exit(0);
	}
	add_history((*data)->tmp);
}

void	input_preper_section_if(t_data **data, t_cursors *crs, char slicer
	, char slicers[])
{
	while (++crs->l < crs->len && crs->k == 0)
	{
		if ((*data)->tmp[crs->i] == slicers[crs->l])
		{
			crs->c = slicers[crs->l];
			crs->k = 1;
		}
	}
	crs->k = 0;
	if ((*data)->tmp[crs->i] == slicer && (*data)->tmp[crs->i - 1] != '\\')
	{
		(*data)->input[crs->j] = ' ';
		(*data)->input[crs->j + 1] = (*data)->tmp[crs->i];
		crs->j = crs->j + 2;
		if ((*data)->tmp[crs->i + 1] == (*data)->tmp[crs->i]
			&& (((*data)->tmp[crs->i] == '>') | ((*data)->tmp[crs->i] == '<')))
		{
			(*data)->input[crs->j] = (*data)->tmp[crs->i + 1];
			crs->i++;
			crs->j++;
		}
		(*data)->input[crs->j] = ' ';
	}
	else
		(*data)->input[crs->j] = (*data)->tmp[crs->i];
}

void	input_preper(t_data **data)
{
	t_cursors	*crs;
	char		slicers[4];

	ft_strlcpy(slicers, ";|<>", 4);
	init_crs(&crs);
	(*data)->input = (char *)ft_calloc(sizeof(char *), 4097);
	crs->len = ft_strlen(slicers);
	if ((*data)->tmp && (*data)->tmp[crs->i])
	{
		while ((*data)->tmp[crs->i])
		{
			crs->l = -1;
			crs->c = '\0';
			input_preper_section_if(data, crs, crs->c, slicers);
			crs->i++;
			crs->j++;
		}
	}
	free((*data)->tmp);
	free(crs);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	int		ret_parser;
	int		ret_quotes;

	if (argc != 1)
		error_msg("Please type only one argument");
	init_scream ();
	init_struct(&data, argv, envp);
	signal(SIGQUIT, signal_handler);
	while (1)
	{
		get_input(&data);
		input_preper(&data);
		data->slicers = ft_calloc(ft_strlen(data->input), sizeof(int));
		data->slicers_types = ft_calloc(ft_strlen(data->input), sizeof(int)
				+ 1);
		ret_parser = parser(&data);
		ret_quotes = verify_quotes(&data);
		if (ret_parser + ret_quotes == 0)
			cmd_check(&data);
		else
			print_error(ret_quotes);
		clean_data(&data);
	}
	return (0);
}
