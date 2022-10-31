/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:52:45 by mcesar-d          #+#    #+#             */
/*   Updated: 2022/10/30 10:28:39 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_pointers_int(int **p)
{
	int	i;

	i = -1;
	if (p[i + 1])
		while (p[++i])
			free(p[i]);
	free(p);
}

void	destroy_pointers_char(char **p)
{
	int	i;

	i = 0;
	while (p != NULL && p[i] != NULL)
		free(p[i++]);
	free(p);
}

void	destroy_mat_char(t_data **data, char ***p, t_cursors *crs)
{
	init_crs(&crs);
	crs->len = count_cmds(data);
	if (*p)
	{
		while (crs->i < crs->len + 1)
		{
			crs->j = 0;
			while (p[crs->i][crs->j])
			{
				{
					free(p[crs->i][crs->j]);
					p[crs->i][crs->j] = NULL;
				}
				crs->j++;
			}
			free(p[crs->i]);
			crs->i++;
		}
	}
	free(p);
	free(crs);
}

void	clean_data(t_data **data)
{
	t_cursors	*crs;

	init_crs(&crs);
	if ((*data)->cmds)
		destroy_mat_char(data, (*data)->cmds, crs);
	free((*data)->len_tokens);
	free((*data)->slicers);
	free((*data)->slicers_types);
	free((*data)->slicers_seq);
	free((*data)->input);
	destroy_pointers_char((*data)->st_cmds);
	(*data)->crs = 0;
	free(crs);
}

void	clean_all(t_data **data, t_cursors *crs)
{
	rl_clear_history();
	clean_data(data);
	destroy_pointers_char((*data)->envp);
	(*data)->argv = '\0';
//	free((*data)->tmp);
	free((*data)->dollar);
	free(crs);
	free((*data));
}
