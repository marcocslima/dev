/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 17:03:55 by mcesar-d          #+#    #+#             */
/*   Updated: 2022/09/12 04:36:18 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
char	*get_value(char **envp, char *var)
{
	int len = ft_strlen(var);
	while (ft_strncmp(var, *envp, len))
		envp++;
	return (*envp + len + 1);
}

int		get_expand(t_data **data, char *param)
{
	t_cursors	*crs;
	t_list		*list;
	t_list		*aux;
	t_expand	**exp;
	char		**mat;

	init_crs(&crs);
	while (param[++crs->l])
		if(param[crs->l] == '$' && param[crs->l + 1] != ' ')
			crs->len++;
	mat = malloc(sizeof(size_t) * crs->len);
	exp = malloc(sizeof(size_t) * crs->len);
	while (++crs->m < crs->len)
		exp[crs->m] = malloc(sizeof(t_expand));
	while (crs->k < crs->len)
	{
		while (param[crs->j])
		{
			crs->c = 0;
			if(param[crs->j] == '$' && param[crs->j + 1] != ' ')
			{
				crs->pointer = &param[crs->j + 1];
				while(param[crs->j++])
					crs->c++;
				mat[crs->k] = ft_calloc(crs->c, sizeof(char));
				ft_strlcpy(mat[crs->k], crs->pointer, crs->c);
				crs->k++;
			}
			crs->j++;
		}
	}
	while (++crs->n < crs->len)
		exp[crs->n]->var = mat[crs->n];
	list = ft_lstnew(exp[0]);
	while (++crs->r < crs->len)
		ft_lstadd_back(&list, ft_lstnew(exp[crs->r]));
	aux = list;
	while(crs->s < crs->len)
	{
		((t_expand *)(*aux).content)->value = get_value((*data)->envp, ((t_expand *)(*aux).content)->var);
		aux = aux->next;
		crs->s++;
	}
	free(crs);
	return 0;
}
*/