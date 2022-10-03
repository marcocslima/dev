/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:43:17 by mcesar-d          #+#    #+#             */
/*   Updated: 2022/10/03 03:27:10 by mcesar-d         ###   ########.fr       */
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
		ft_putstr_fd(": command not found\n", STDERR);
		return (127);
	}
	else if (fd == -1 && folder == NULL)
	{
		ft_putstr_fd ("No such file or directory\n", STDERR);
		return (127);
	}
	else if (fd == -1 && folder != NULL)
		ft_putstr_fd (": is a directory\n", STDERR);
	else if (fd != -1 && folder == NULL)
		ft_putstr_fd (": Permission denied\n", STDERR);
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
