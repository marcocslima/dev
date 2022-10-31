/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/10/31 15:38:49 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(char *argv, t_data **data)
{
	char	**cmd;
	char	*path;

	cmd_space_substitution(argv);
	cmd = ft_split(argv, ' ');
	cmd_one_substitution (cmd);
	path = pathexec(cmd[0], (*data)->envp);
	clean_data(data);
	if (execve(path, cmd, (*data)->envp) == -1)
		exit(exec_error_msg(argv, data));
}

void	execute_pipe(char *argv, t_data **data, t_cursors *crs)
{
	char	**cmd;
	char	*path;
	pid_t	pid;
	int		status;

	signal(SIGINT, child_signal_handler);
	pid = fork();
	if (pid == 0)
	{
		cmd_space_substitution(argv);
		cmd = ft_split(argv, ' ');
		cmd_one_substitution (cmd);
		path = pathexec(cmd[0], (*data)->envp);
		if (execve(path, cmd, (*data)->envp) == -1)
		{
			free(cmd);
			free(path);
			clean_all(data, crs);
			exit(exec_error_msg(argv, data));
		}
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		(*data)->exit_return = WEXITSTATUS(status);
}

void	ft_pipe_close(t_data **data, int status, int pipefd[2], t_cursors *crs)
{
	if (WIFEXITED(status))
		(*data)->exit_return = WEXITSTATUS(status);
	close(pipefd[OUT]);
	dup2(pipefd[IN], STDIN);
	if (crs->flagpipe == 1)
		exit(0);
}

void	ft_pipe(t_data **data, int i, int flag, t_cursors *crs)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	signal(SIGINT, child_signal_handler);
	if (ft_memcmp((*data)->cmds[i][0], "echo", 5))
	{
		pipe (pipefd);
		pid = fork();
		if (pid == 0)
		{
			close (pipefd[IN]);
			dup2 (pipefd[OUT], STDOUT);
			if (flag == 8)
			{
				crs->flagpipe = 0;
				ft_input(data, crs);
				crs->flagpipe = 1;
			}
			else
				builtin_execute(data, crs);
		}
		waitpid(pid, &status, 0);
		ft_pipe_close(data, status, pipefd, crs);
	}
}
