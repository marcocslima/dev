/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/09/24 10:42:44 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_error_msg(char *path)
{
	int	fd;
	DIR *folder;

	fd = open(path, O_WRONLY);
	if (path)
		folder = opendir(path);
	ft_putstrs("minishell: ", path, NULL ,STDERR);
	//if (ft_strchr(path, '/') == NULL)
	if (access(path, F_OK) != 0)
	{
		ft_putstr_fd(": command not found", STDERR);
		exit (127);
	}
	else if (fd == -1 && folder == NULL)
	{
		ft_putstr_fd ("No such file or directory", STDERR);
		exit (127);
	}
	else if (fd == -1 && folder != NULL)
		ft_putstr_fd (": is a directory", STDERR);
	else if (fd != -1 && folder == NULL)
		ft_putstr_fd (": Permission denied", STDERR);
	if (folder)
		closedir(folder);
	close(fd);
	exit (126);
}

void	signal_handler_bash(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		exit(0);
	}
}

void	ft_bash(t_data **data)
{
	char	cmd[256];
	char	tmp[256];
	char	*args[256];
	char	*path;
	int		i;
	int		j = 0;
	int		flag;

	pid_t	pid;
	int status;

	if (!ft_memcmp((*data)->cmds[0][0], "./", 2))
		i = 2;
	else if (!ft_memcmp((*data)->cmds[0][0], "../", 3))
		i = 3;
	else if (!ft_memcmp((*data)->cmds[0][0], "/", 1))
		i = 1;
	flag = i;
	while ((*data)->cmds[0][0][i])
	{
		cmd[j] = (*data)->cmds[0][0][i];
		i++;
		j++;
	}
	cmd[j] = '\0';
	path = getcwd(tmp, sizeof(tmp));
	int len_b = ft_strlen(path);
	if (flag == 3)
	{
		while (flag < 4 || len_b == 0)
		{
			if(path[len_b] == '/')
				flag++;
			len_b--;
		}
		path[len_b + 1] = '\0';
	}
	path = ft_strjoin_2(path, "/");
	path = ft_strjoin_2(path, cmd);

	i = -1;
	while(++i < 257)
		args[i] = NULL;

	i = 0;
	args[0] = path;
	while((*data)->cmds[0][++i])
		args[i] = (*data)->cmds[0][i];
	args[i] = NULL;

	pid = fork();
	if (pid == 0)
	{
		//write(1, "filho \n", 7);
		signal(SIGINT, signal_handler_bash);
		if (execve(path, args, (*data)->envp)  == -1)
			exec_error_msg(path);
	}
	else
	{
		waitpid(pid, &status, 0);
		return ;
	}


//	ft_cd_home(data, home_path, i, input);
//	if ((*data)->exit_return != 2)
//		return ;
}

int	error_msg(char *message)
{
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	exit(ERROR);
}

int	no_error_msg(char *message)
{
	ft_putstr_fd(message, 1);
	ft_putstr_fd("\n", 1);
//	if (stack->array_a[0])
	{
//		free(stack->array_a);
//		free(stack->array_b);
	}
	exit(0);
}

