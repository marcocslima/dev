/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/09/17 00:39:45 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//essa função testei separado, ainda não está embutida no parse
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
//		entry_error();
	}
}
void	execute(char *argv, t_data **data)
{
	char	**cmd;
	char	*path;

	cmd_space_substitution(argv);
	cmd = ft_split(argv, ' ');
	cmd_one_substitution (cmd);
	if (cmd[0] == NULL)
	{
		free(cmd[0]);
		free(cmd);
//		entry_error();
	}
	path = pathexec(cmd[0], (*data)->envp);
//	if (path == 0)
//		command_error(cmd);
//	path_error(path, cmd);
	if (execve(path, cmd, (*data)->envp) == -1)
		exit(ERROR);
}


void		ft_pipe(t_data **data)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;
	char	*cmd1 = "ls -l";
	char	*cmd2 = "wc -l";

	pipe (pipefd);
	pid = fork();
	if (pid == 0)
	{
		dup2 (pipefd[OUT], STDOUT);
		close (pipefd[IN]);
		execute (cmd1, data);
	}
	else
	{
		waitpid(pid, &status, 0);
		dup2(pipefd[IN], STDIN);
		close(pipefd[OUT]);
		execute(cmd2, data);
	}
}

void	ft_output(t_data **data)
{
	char	*token = ">>";
	int		output;
	char	*filename = "teste";

	if (token[0] == '>' && token[1] != '>' )
		output = open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (token[0] == '>' && token[1] == '>' )
		output = open(filename, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (output == -1)
	{
		ft_putstr_fd("bash: ", STDERR);
		ft_putstr_fd(token, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		(*data)->exit_return = 1;
		return ;
	}
	dup2(output, STDOUT);
}
/*
void	ft_input(t_data **data)
{
	char	*token = "<";
	int		input;
	char	*filename = "teste";

	if (token[0] == '<' && token[1] != '<' )
		input = open(filename, O_RDONLY, S_IRWXU);
	if (token[0] == '<' && token[1] == '<' )
		output = open(filename, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (input == -1)
	{
		ft_putstr_fd("bash: ", STDERR);
		ft_putstr_fd(token, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		(*data)->exit_return = 1;
		return ;
	}
	dup2(input, STDIN);
}
*/
