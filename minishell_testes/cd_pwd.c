/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/09/03 15:36:46 by acosta-a         ###   ########.fr       */
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
			return (ft_substr((*data)->envp[i], j + 1, ft_strlen((*data)->envp[i]) - j));
		}
		i++;
	}
	return (0);
}

void	ft_cd_home(t_data **data, char *home_path, int i, char*	input)
{
	home_path = find_env_val(data,"HOME");
	if (!(home_path))
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		(*data)->exit_return = 1;
	}
	while (input[i++])
		if (input[i] == ' ')
		{
			ft_putstr_fd("cd: too many arguments", 2);
			(*data)->exit_return = 1;
		}
	printf("home_path: %s\n",home_path );
	if (!input || input[0] == '\0' || ft_memcmp("~", input, 1) == 0 || ft_memcmp(input, "--", 2) == 0)
	{
		chdir(home_path);
		(*data)->exit_return = 0;
		return ;
	}
	else
		(*data)->exit_return = 2;
}


void	ft_cd(t_data **data, char *input)
{
	char*	home_path;
	char	cwd[256];
	char*	path;
	int		i;

	i = 0;
	home_path = find_env_val(data,"HOME");
	ft_cd_home(data, home_path, i, input/* ,cwd*/);
	if ((*data)->exit_return != 2)
		return ;
	printf("Current working dir: %s\n", getcwd(cwd, sizeof(cwd)));
	if(ft_memcmp("-", input, ft_strlen(input)) == 0)
	{
		path = find_env_val(data,"OLDPWD");
		if (!(path))
		{
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
			(*data)->exit_return = 1;
		}
		ft_putstr_fd(path, 1);
		ft_putstr_fd("\n", 1);
		chdir(path);
		(*data)->exit_return = 0;
		return ;
	}
	path = getcwd(cwd, sizeof(cwd));
	printf("path: %s\n",path );
	(*data)->exit_return = 1;
	if(access(input, F_OK) == -1)
		ft_putstr_fd("no such file or directory: ", 2);
	else if (access(input, R_OK) == -1)
		ft_putstr_fd("permission denied: ", 2);
	else
	{
		chdir(input);
		(*data)->exit_return = 0;
	}
	printf("Current working dir2: %s\n", getcwd(cwd, sizeof(cwd)));
	return ;
}

int		ft_pwd(void)
{
	char	cwd[4096];

	if (getcwd(cwd, 4096))
	{
		ft_putstr_fd(cwd, 1);
		return (0);
	}
	return(ERROR);
}
