/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/10/30 09:39:47 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_print(t_data **data, t_cursors *crs)
{
	int	i;

	i = 0;
	if (((*data)->cmds[0][1] && (!ft_memcmp((*data)->cmds[0][1], "|", 2)
		|| !ft_memcmp((*data)->cmds[0][1], ">", 2))) || !(*data)->cmds[0][1])
	{
		while ((*data)->envp[i])
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstrs((*data)->envp[i], "\n", 0, 1);
			i++;
		}
	}
	if ((*data)->cmds[0][1] && (!ft_memcmp((*data)->cmds[0][1], "|", 2)
		|| !ft_memcmp((*data)->cmds[0][1], ">", 2)))
	{
		clean_all(data, crs);
		exit (0);
	}
	if (!(*data)->cmds[0][1])
		return (0);
	return (1);
}

int	ft_export_errors(int i, char *input, t_data **data)
{
	if (ft_isdigit(input[0]) == 1 || input[0] == '=')
	{
		ft_putstr_fd("export: not a valid identifier: ", STDERR);
		(*data)->exit_return = ERROR;
		return (ERROR);
	}
	while (input[i] && input [i] != '=')
	{
		if ((ft_isalnum(input[i]) == 0) && input[i] != '_')
		{
			ft_putstr_fd("export: not valid in this context: ", STDERR);
			(*data)->exit_return = ERROR;
			return (ERROR);
		}
		i++;
	}
	return (0);
}

int	ft_export(t_data **data, char *input, t_cursors *crs)
{
	int		i;
	int		updated;

	updated = 0;
	i = 0;
	if (export_print(data, crs) == 0)
		return (0);
	if (ft_export_errors(i, input, data) > 0)
		return (ERROR);
	i = 0;
	while ((*data)->envp[i])
	{
		if (ft_memcmp((*data)->envp[i], input, ft_strlen(input) - 1) == 0)
		{
			(*data)->envp[i] = ft_strdup(input);
			updated = 1;
		}
		i++;
	}
	if (updated == 0)
	{
//		if ((*data)->envp[i])
//		free((*data)->envp[i]);
//		(*data)->envp[i] = ft_calloc(sizeof(char *),ft_strlen(input));
		(*data)->envp[i] = ft_strdup(input);
//		ft_memmove((*data)->envp[i], input, sizeof(input));
//		(*data)->envp[i + 1] = NULL;
//		if(input && (*data)->envp[i])
//			ft_strlcpy((*data)->envp[i], input, ft_strlen(input));
	}
	return (0);
}

int	ft_unset_errors(int i, char *input, t_data **data)
{
	i = 0;
	while (input[i])
	{
		if ((ft_isalnum(input[i]) == 0) || ft_isdigit(input[0]) == 1)
		{
			(*data)->exit_return = ERROR;
			ft_putstr_fd("unset: not a valid identifier", STDERR);
			return (ERROR);
		}
		i++;
	}
	i = 0;
	return (0);
}

int	ft_unset(t_data **data, char *input)
{
	int		i;
	int		j;
	int		len;

	i = -1;
	len = 0;
	(*data)->exit_return = 0;
	if (ft_unset_errors(i, input, data) > 0)
		return (ERROR);
	i = 0;
	while (input[len])
		len++;
	while ((*data)->envp[i])
	{
		if (ft_memcmp((*data)->envp[i], input, len) == 0)
		{
			ft_bzero((*data)->envp[i], ft_strlen((*data)->envp[i]));
			if ((*data)->envp[i] && (*data)->envp[i + 1])
//				(*data)->envp[i] = ft_strdup((*data)->envp[i + 1]);
				(*data)->envp[i] =(*data)->envp[i + 1];
			j = i - 1;
			while ((*data)->envp[j++] && (*data)->envp[j + 1])
//				(*data)->envp[j] = ft_strdup((*data)->envp[j + 1]);
				(*data)->envp[j] = (*data)->envp[j + 1];
			if ((*data)->envp[j] == NULL || (*data)->envp[j][0] == '\0')
				(*data)->envp[j] = NULL;
		}
		i++;
	}
//	if ((*data)->envp[j + 1] == NULL || (*data)->envp[j][0] == '\0')
//	free((*data)->envp[i]);
//	free((*data)->envp[i + 1]);
	return (0);
}
