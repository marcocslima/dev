/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/09/16 23:35:52 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "minishell.h"

char	*find_env_val(t_data **data, char *find)
{
	int	i;
	int	j;

	i = 0;
	while ((*data)->envp[i])
	{
		j = 0;
		if (ft_strncmp((*data)->envp[i], find, ft_strlen(find)) == 0)
		{
			while ((*data)->envp[i][j] != '=')
				j++;
			return (ft_substr((*data)->envp[i], j + 1, ft_strlen((*data)->envp
						[i]) - j));
		}
		i++;
	}
	return (0);
}

void	ft_cd_home(t_data **data, char *home_path, int i, char *input)
{
	home_path = find_env_val(data, "HOME");
	if (!(home_path))
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		(*data)->exit_return = 1;
		return ;
	}
	if ((*data)->cmds[i][2] && (((*data)->cmds[i][2][0] != '\0' &&
		!is_token((*data)->cmds[i][2][0]))))
	{
		ft_putstr_fd("cd: too many arguments", 2);
		(*data)->exit_return = 1;
		return ;
	}
	if (!input || input[0] == '\0' || ft_memcmp("~", input, 1) == 0
		|| ft_memcmp(input, "--", 2) == 0)
	{
		chdir(home_path);
		(*data)->exit_return = 0;
		return ;
	}
	else
		(*data)->exit_return = 2;
}

void	ft_cd_2(t_data **data, char *path)
{
	if (!(path))
	{
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
		(*data)->exit_return = 1;
		return ;
	}
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\n", 1);
	chdir(path);
	(*data)->exit_return = 0;
}

int	ft_cd(t_data **data, char *input, int i)
{
	(*data)->home_path = find_env_val(data, "HOME");
	(*data)->pathcd = find_env_val(data, "OLDPWD");
	ft_cd_home(data, (*data)->home_path, i, input);
	if ((*data)->exit_return != 2)
		return ((*data)->exit_return);
	else if (ft_memcmp("-", input, ft_strlen(input)) == 0)
	{
		(*data)->pathcd = find_env_val(data, "OLDPWD");
		ft_cd_2(data, (*data)->pathcd);
		return ((*data)->exit_return);
	}
	(*data)->exit_return = 1;
	if (access(input, F_OK) == -1)
		ft_putstr_fd("no such file or directory: ", 2);
	else if (access(input, R_OK) == -1)
		ft_putstr_fd("permission denied: ", 2);
	else
	{
		chdir(input);
		(*data)->exit_return = 0;
	}
	free(input);
	return ((*data)->exit_return);
}

int	ft_pwd(void)
{
	char	cwd[4096];

	if (getcwd(cwd, 4096))
	{
		ft_putstr_fd(cwd, 1);
		return (0);
	}
	return (ERROR);
}
