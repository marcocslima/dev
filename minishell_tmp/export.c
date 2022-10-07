/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/10/01 08:56:03 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env2(t_data **data, int add)
{
	int		i;
	int		len;
	char	**copy;

	len = 0;
	while ((*data)->envp[len])
		len++;
	copy = (char **)ft_calloc(sizeof(char *), (len + add + 1));
	if (!copy)
		return (0);
	i = -1;
	while (i++ < len - 1)
	{
		copy[i] = ft_strdup((*data)->envp[i]);
		printf("%s %d\n", copy[i], i);
	}
	return (copy);
}

int	ft_export_errors(int i, char *input)
{
	if (ft_isdigit(input[0]) == 1 || input[0] == '=')
	{
		ft_putstr_fd("export: not a valid identifier: ", STDERR);
		return (ERROR);
	}
	while (input[i] && input [i] != '=')
	{
		if ((ft_isalnum(input[i]) == 0) && input[i] != '_')
		{
			ft_putstr_fd("export: not valid in this context: ", STDERR);
			return (ERROR);
		}
		i++;
	}
	return (0);
}

int	ft_export(t_data **data, char *input)
{
	int		i;
	int		updated;

	updated = 0;
	i = 0;
	if (!ft_strchr(input, '='))
		return (0);
	if (ft_export_errors(i, input) > 0)
		return (ERROR);
	i = 0;
	while ((*data)->envp[i])
	{
		if (ft_memcmp((*data)->envp[i], input,
				ft_strlen(input) - 1) == 0)
		{
			(*data)->envp[i] = ft_strdup(input);
			updated = 1;
		}
		i++;
	}
	if (updated == 0)
	{
		free((*data)->envp[i]);
		(*data)->envp[i] = ft_strdup(input);
	}
//	free(input);
	return (0);
}

int	ft_unset_errors(int i, char *input)
{
	i = 0;
	while (input[i])
	{
		if ((ft_isalnum(input[i]) == 0) || ft_isdigit(input[0]) == 1)
		{
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
	if (ft_unset_errors(i, input) > 0)
		return (ERROR);
	i = 0;
	len = 0;
	while (input[len])
		len++;
	while ((*data)->envp[i])
	{
		if (ft_memcmp((*data)->envp[i], input, len) == 0)
		{
			ft_bzero((*data)->envp[i], ft_strlen((*data)->envp[i]));
			if ((*data)->envp[i] && (*data)->envp[i + 1])
				(*data)->envp[i] = ft_strdup((*data)->envp[i + 1]);
			j = i - 1;
			while ((*data)->envp[j++] && (*data)->envp[j + 1])
				(*data)->envp[j] = ft_strdup((*data)->envp[j + 1]);
			if ((*data)->envp[j] == NULL || (*data)->envp[j][0] == '\0')
				(*data)->envp[j] = NULL;
		}
		i++;
	}
	return (0);
}
