/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/10/17 23:51:27 by mcesar-d         ###   ########.fr       */
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
	}
	path = pathexec(cmd[0], (*data)->envp);
	if (execve(path, cmd, (*data)->envp) == -1)
		exit(exec_error_msg(argv));
}

void	execute_pipe(char *argv, t_data **data)
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
	if (cmd[0] == NULL)
	{
		free(cmd[0]);
		free(cmd);
	}
	path = pathexec(cmd[0], (*data)->envp);
	if (execve(path, cmd, (*data)->envp)  == -1)
		exit(exec_error_msg(argv));
	}
	waitpid(pid, &status, 0);
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
			builtin_execute(data, i, flag, crs);
		}
		waitpid(pid, &status, 0);
		close(pipefd[OUT]);
		dup2(pipefd[IN], STDIN);
	}
}
/*
void exec_output(t_cursors *crs)//(t_data **data, t_cursors *crs)
{
    int status, pid;
    int fd[2];

    pipe(fd);

    fd[1] = crs->output;
    pid = fork();
    if (pid == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);

        execlp("/usr/bin/ls", "ls", "-la", NULL);
    }
    close(fd[0]);
    close(fd[1]);
    waitpid(pid, &status, 0);
}
*/
int check_sep(char c)
{
	t_cursors *crs;
	char slicers[4] = ";|";

	init_crs(&crs);
	while(crs->i < 2)
		if(c == slicers[crs->i++])
		{
			free(crs);
			return (1);
		}
	free(crs);
	return (0);
}

char *join_cmds(t_data **data, int cmd)
{
	t_cursors *c;
	char *ret;
	char jinput[4097];

	init_crs(&c);
	while((*data)->cmds[cmd])
	{
		while((*data)->cmds[cmd][c->j])
		{
			c->len = ft_strlen((*data)->cmds[cmd][c->j]);
			while(c->k < c->len)
			{
				if(check_sep((*data)->cmds[cmd][c->j][c->k]) == 1)
					goto EXT;
				jinput[c->w] = (*data)->cmds[cmd][c->j][c->k];
				c->k++;
				c->w++;
			}
			c->k = 0;
			c->j++;
		}
		c->j = 0;
		cmd++;
	}
	EXT:
	jinput[c->w] = '\0';
	ret = jinput;
	free(c);
	return (ret);	
}

void	ft_output(t_data **data, t_cursors *crs)
{
	pid_t	pid;
	char 	*jc;
	char 	**ncmd;

	jc = join_cmds(data, crs->i2);
	ncmd = ft_split(jc, '>');
	while (ncmd[crs->o])
		crs->o++;
	if ((*data)->qtd_cmds < crs->o + 1)
		(*data)->jump = crs->o;
	else
		(*data)->jump = crs->o + 1;
	pid = fork();
	if (pid == 0)
	{
	while(jc[++crs->l])
	{
		if(jc[crs->l] == '>' && jc[crs->l + 1] == '>')
			crs->output = open(ncmd[++crs->k], O_CREAT | O_WRONLY | O_APPEND, S_IRWXO);
		else if(jc[crs->l] == '>' && jc[crs->l + 1] != '>' && jc[crs->l - 1] != '>')
			crs->output = open(ncmd[++crs->k], O_CREAT | O_WRONLY | O_TRUNC, S_IRWXO);
	}
	if (crs->output == -1)
	{
		ft_putstrs("bash:", (*data)->cmds[crs->i2][1],
		": No such file or directory" , STDERR);
		(*data)->exit_return = 1;
		return ;
	}
	ft_output_2(data, crs);
	}
	waitpid(pid, &crs->status, 0);
}

void	ft_output_2(t_data **data, t_cursors *crs)
{
		//crs->saved_stdout = dup(STDOUT);
		dup2(crs->output, STDOUT);
		close(crs->output);
		builtin_execute(data, crs->i2, crs->flag, crs);
		//dup2(crs->saved_stdout, STDOUT);
		//close(crs->saved_stdout);
}


void	ft_input(t_data **data, t_cursors *crs)
{
	pid_t	pid;

	if (!ft_strncmp((*data)->cmds[crs->i2][crs->j2], "<", 2) && !ft_strncmp
			((*data)->cmds[crs->i2 + 1][0], "<", 1))
	{
		crs->flag = 1;
		crs->j2 = 1;
		ft_here_doc(data, crs);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		if (((*data)->cmds[crs->i2][2] && !ft_strncmp((*data)->cmds[crs->i2][2], "<", 2) && ft_strncmp((*data)->cmds[crs->i2 + 1][0], "<", 2)) || (!(*data)->cmds[crs->i2][2] && (*data)->cmds[crs->i2][1] && !ft_strncmp((*data)->cmds[crs->i2][1], "<", 2) && ft_strncmp((*data)->cmds[crs->i2 + 1][0], "<", 2)))
			crs->input = open((*data)->cmds[crs->i2 + 1][0], O_RDONLY, S_IRWXU);
		if (((*data)->cmds[crs->i2 + 2] && (*data)->cmds[crs->i2 + 2][0] && !ft_strncmp((*data)->cmds[crs->i2 + 2][0], ">", 2)) || ((*data)->cmds[crs->i2 + 1] && (*data)->cmds[crs->i2 + 1][1] && !ft_strncmp((*data)->cmds[crs->i2 + 1][1], ">", 2))){
			ft_in_output(data, crs);
			return ;}
		if (crs->input == -1)
		{
			ft_putstrs("bash:", (*data)->cmds[crs->i2][1],
			": No such file or directory" , STDERR);
			(*data)->exit_return = 1;
			return ;
		}
		if (crs->input > 0)
		{
			crs->saved_stdin = dup(STDIN);
			dup2(crs->input, STDIN);
			builtin_execute(data, crs->i2, crs->flag, crs);
			dup2(crs->saved_stdin, STDIN);
			close(crs->saved_stdin);
			close(crs->input);
		}
	waitpid(pid, &crs->status, 0);
	}
	if ((*data)->cmds[crs->i2 + 1][1] && (*data)->cmds[crs->i2 + 1][1][0] == '>')
	{
		crs->i2 += 3;
		crs->j2--;
	}
	else
		crs->i2+=2;
}

void	ft_in_output(t_data **data, t_cursors *crs)
{
		if (!ft_strncmp((*data)->cmds[crs->i2 + 1][crs->j2], ">", 2) && !ft_strncmp
			((*data)->cmds[crs->i2 + 2][0], ">", 2))
			crs->output = open((*data)->cmds[crs->i2 + 2][1], O_CREAT
					| O_WRONLY | O_APPEND, S_IRWXU);
		else if (!ft_strncmp((*data)->cmds[crs->i2 + 1][crs->j2], ">", 2) && ft_strncmp
			((*data)->cmds[crs->i2 + 2][0], ">", 2))
		crs->output = open((*data)->cmds[crs->i2 + 2][0], O_CREAT | O_WRONLY
					| O_TRUNC, S_IRWXU);
		if (crs->output == -1)
		{
			ft_putstrs("bash:", (*data)->cmds[crs->i2][1],
			": No such file or directory" , STDERR);
			(*data)->exit_return = 1;
			return ;
		}
		crs->saved_stdin = dup(STDIN);
		dup2(crs->input, STDIN);
		crs->saved_stdout = dup(STDOUT);
		dup2(crs->output, STDOUT);
		builtin_execute(data, crs->i2, crs->flag, crs);
		dup2(crs->saved_stdout, STDOUT);
		dup2(crs->saved_stdin, STDIN);
		close(crs->saved_stdin);
		close(crs->input);
		close(crs->output);
		close(crs->saved_stdout);
}
