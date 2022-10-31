/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/10/30 10:30:53 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*pathexec(char *cmd, char *envp[])
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (cmd);
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path, cmd);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	free(paths);
	return (0);
}

char	*cmd_space_substitution(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] == '\'' || argv[i] == '\"')
		{
			i++;
			if (argv[i] == '\'' || argv[i] == '\"')
				i++;
			while (argv[i] != '\'' && argv[i] != '\"' && argv[i])
			{
				if (argv[i] == ' ')
					argv[i] = 1;
				i++;
			}
		}
		i++;
	}
	if (argv[i] != '\0')
		argv[i] = '\0';
	return (argv);
}

char	**cmd_one_substitution(char **cmd)
{
	int		i;
	int		x;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '\'' || cmd[i][0] == '\"')
		{
			x = 1;
			if (cmd[i][x] == '\'' || cmd[i][x] == '\"')
				x++;
			while ((cmd[i][x] != '\'' && cmd[i][x] != '\"' ) && cmd[i][x])
			{
				if (cmd[i][x] == 1)
				cmd[i][x] = ' ';
				x++;
			}
			if (cmd[i][x + 1] != '\0' )
				x++;
			one_substitution_2(cmd, i, x);
		}
		i++;
	}
	return (cmd);
}

void	one_substitution_2(char **cmd, int i, int x)
{
	char	*tmp;

	tmp = ft_substr(cmd[i], 1, x - 1);
	free(cmd[i]);
	cmd[i] = tmp;
}

void	path_error(char *path, char **cmd)
{
	int		i;

	i = -1;
	if (!path)
	{
		while (cmd[i++])
			free(cmd[i]);
		free(cmd);
	}
}
