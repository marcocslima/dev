/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:43:17 by mcesar-d          #+#    #+#             */
/*   Updated: 2022/09/26 22:18:52 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(int e)
{
	char	*erros[] = {"OK", "unclosed quotes"};

	ft_putstr_fd("Error: ", 1);
	ft_putstr_fd(erros[e], 1);
	ft_putstr_fd("\n", 1);
}

int	exec_error_msg(char *path)
{
	int	fd;
	DIR	*folder;

	fd = open(path, O_WRONLY);
	if (path)
		folder = opendir(path);
	ft_putstrs("minishell: ", path, NULL, STDERR);
	if (access(path, F_OK) != 0)
	{
		ft_putstr_fd(": command not found", STDERR);
		return (127);
	}
	else if (fd == -1 && folder == NULL)
	{
		ft_putstr_fd ("No such file or directory", STDERR);
		return (127);
	}
	else if (fd == -1 && folder != NULL)
		ft_putstr_fd (": is a directory", STDERR);
	else if (fd != -1 && folder == NULL)
		ft_putstr_fd (": Permission denied", STDERR);
	if (folder)
		closedir(folder);
	close(fd);
	return (126);
}

int	error_msg(char *message)
{
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	exit(ERROR);
}
