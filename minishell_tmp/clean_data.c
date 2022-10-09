/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:52:45 by mcesar-d          #+#    #+#             */
/*   Updated: 2022/10/07 14:30:37 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_cmds(t_data **data)
{
	int	len;
	int	j;
	int	counter;

	j = 0;
	counter = 0;
	len = 0;
	if ((*data)->input)
		len = ft_strlen((*data)->input);
	while (j < len)
	{
		if ((*data)->slicers[j] != 0)
			counter++;
		j++;
	}
	return (counter);
}

void destroy_pointers_int(int **p)
{
	int i = -1;
	if(p[i + 1])
		while(p[++i])
			free(p[i]);
	free(p);
}

void destroy_cursors(t_cursors *crs)
{
/*	int i = -1;

	if(crs->cursor[i + 1])
		while(crs[++i])
			free(crs[i]);
	free(crs);*/
	free(crs);
}

void destroy_pointers_char(char **p)
{
	int i = -1;

	if(p[i + 1])
		while(p[++i])
			//if(p[i])
				free(p[i]);
	free(p);
}

void destroy_mat_char(t_data **data, char ***p, t_cursors *crs)
{
	init_crs(&crs);
	crs->len = count_cmds(data);
	while(crs->i < crs->len + 1)
	{
		crs->j = 0;
		while(p[crs->i][crs->j])
		{
//			if(*p[crs->i][crs->j] != '\0' && *p[crs->i][crs->j] != '\0')
			{
				free(p[crs->i][crs->j]);
				p[crs->i][crs->j] = NULL;
			}
			crs->j++;
		}
		crs->i++;
	}
	free(p);
	free(crs);
}

void clean_data(t_data **data)
{
	t_cursors *crs;

	init_crs(&crs);
	if((*data)->cmds)
		destroy_mat_char(data, (*data)->cmds, crs);
	destroy_pointers_int((*data)->tokens);
	free((*data)->len_tokens);
	free((*data)->slicers);
	free((*data)->slicers_types);
	free((*data)->slicers_seq);
//		free((*data)->quotes_types);
	free((*data)->input);
	free((*data)->params);
	free((*data)->st_cmds);
//	free((*data)->path);
	//destroy_pointers_char((*data)->params); ERRO VALGRIND
	(*data)->crs = 0;
	free(crs);
}

void clean_all(t_data **data, t_cursors *crs)
{
//	t_cursors *crs;

//	init_crs(&crs);
	clean_data(data);
	destroy_pointers_char((*data)->envp);
	//destroy_pointers_char((*data)->argv); NÃO É MALLOCADO
	(*data)->argv = '\0';
	//destroy_pointers_int((*data)->tokens); //JÁ TEM FREE ANTERIOR
	destroy_cursors(crs);
//	free((*data)->pathcd);
//	free((*data)->home_path);
//	free((*data)->tmp);
//	destroy_pointers_char((*data)->st_cmds);
	free((*data)->dollar);
//	free(crs);
}
