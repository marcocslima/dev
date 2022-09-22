/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/09/18 02:19:47 by acosta-a         ###   ########.fr       */
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
	if (execve(path, cmd, (*data)->envp)  == -1)
		exit(ERROR);
//		exec_error_msg(path);
}

void	execute_pipe(char *argv, t_data **data)
{
	char	**cmd;
	char	*path;
	pid_t	pid;
	int		status;
	pid = fork();

	if (pid == 0)
	{
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
	if (execve(path, cmd, (*data)->envp)  == -1)
		exit(ERROR);
//		exec_error_msg(path);
	}
	waitpid(pid, &status, 0);
//	dup2(pipefd[IN], STDIN);
//	close(pipefd[OUT]);
}

void	ft_pipe(t_data **data, int i, int flag, t_cursors *crs)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	pipe (pipefd);
	pid = fork();
	if (pid == 0)
	{
		close (pipefd[IN]);
		dup2 (pipefd[OUT], STDOUT);
		builtin_execute(data, i, flag, crs);
	}
	waitpid(pid, &status, 0);
	close(pipefd[OUT]);
	dup2(pipefd[IN], STDIN);
//	dup2(pipefd[IN], STDIN);
//	close(pipefd[OUT]);
}

void	ft_output(t_data **data, t_cursors *crs)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (!ft_strncmp((*data)->cmds[crs->i2][crs->j2], ">", 2) && !ft_strncmp
			((*data)->cmds[crs->i2 + 1][0], ">", 2))
			crs->output = open((*data)->cmds[crs->i2 + 1][1], O_CREAT
					| O_WRONLY | O_APPEND, S_IRWXU);
		else if (!ft_strncmp((*data)->cmds[crs->i2][crs->j2], ">", 2) && ft_strncmp
			((*data)->cmds[crs->i2 + 1][0], ">", 2))
		crs->output = open((*data)->cmds[crs->i2 + 1][0], O_CREAT | O_WRONLY
					| O_TRUNC, S_IRWXU);
		if (crs->output == -1)
		{
			ft_putstrs("bash:", (*data)->cmds[crs->i2][1],
			": No such file or directory" , STDERR);
			(*data)->exit_return = 1;
			return ;
		}
	crs->saved_stdout = dup(STDOUT);
		dup2(crs->output, STDOUT);
		builtin_execute(data, crs->i2, crs->flag, crs);
		dup2(crs->saved_stdout, STDOUT);
		close(crs->saved_stdout);
		crs->j2+=2; //adicionado erro
	}
		waitpid(pid, &crs->status, 0);
}
/*
void	ft_output_doc(t_data **data, t_cursors *crs)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (!ft_strncmp((*data)->cmds[crs->i][crs->j], ">", 2) && !ft_strncmp
			((*data)->cmds[crs->i + 1][0], ">", 2))
			crs->output = open((*data)->cmds[crs->i + 1][1], O_CREAT
					| O_WRONLY | O_APPEND, S_IRWXU);
		else if (!ft_strncmp((*data)->cmds[crs->i][crs->j], ">", 2) && ft_strncmp
			((*data)->cmds[crs->i + 1][0], ">", 2))
		crs->output = open((*data)->cmds[crs->i + 1][0], O_CREAT | O_WRONLY
					| O_TRUNC, S_IRWXU);
		if (crs->output == -1)
		{
			ft_putstrs("bash:", (*data)->cmds[crs->i][1],
				": No such file or directory" , STDERR);
			(*data)->exit_return = 1;
			return ;
		}
	crs->saved_stdout = dup(STDOUT);
		dup2(crs->output, STDOUT);
		builtin_execute(data, crs->i, crs->flag);
		dup2(crs->saved_stdout, STDOUT);
		close(crs->saved_stdout);
	}
	waitpid(pid, &crs->status, 0);
}
*/
void	ft_input(t_data **data, t_cursors *crs)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (!ft_strncmp((*data)->cmds[crs->i2][2], "<", 2) && ft_strncmp
			((*data)->cmds[crs->i2 + 1][0], "<", 2))
			crs->input = open((*data)->cmds[crs->i2 + 1][0], O_RDONLY, S_IRWXU);
		if (crs->input == -1)
		{
			ft_putstrs("bash:", (*data)->cmds[crs->i2][1],
			": No such file or directory" , STDERR);
			(*data)->exit_return = 1;
			return ;
		}
	crs->saved_stdin = dup(STDIN);
		dup2(crs->input, STDIN);
		builtin_execute(data, crs->i, crs->flag, crs);
		dup2(crs->saved_stdin, STDIN);
		close(crs->saved_stdin);
	}
	if (!ft_strncmp((*data)->cmds[crs->i2][crs->j2], "<", 2) && !ft_strncmp
			((*data)->cmds[crs->i2 + 1][0], "<", 1))
	{
			crs->flag = 1;
			crs->j2 = 2;
			ft_here_doc(data, crs);
	}
	waitpid(pid, &crs->status, 0);
}
