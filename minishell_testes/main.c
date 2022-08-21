/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/08/21 01:35:56 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "minishell2.h"

char	**copy_env(char **envp, int add)
{
	int		i;
	int		len;
	char	**copy;

	len = 0;

	while (envp[len])
		len++;
	if (!(copy = (char **)ft_calloc(sizeof(char *), (len + add + 1))))
		return (0);
	i = -1;
	while (i++ < len - 1)
	{
		copy[i] = ft_strdup(envp[i]);
//		printf("%s %d\n", copy[i], i);
	}
	return (copy);
}

void	init_struct(t_data **data, char **argv, char **envp)
{
	(*data) = (t_data *)malloc(sizeof(t_data));
	(*data)->envp = copy_env(envp, 0);
	(*data)->argv = argv;
	(*data)->input = (char *)ft_calloc(sizeof(char *), 4097);
	(*data)->pars_inpt = (char **)ft_calloc(sizeof(char *), (4097));

}

void	open_prompt(char **envp)
{
	char	*home;
	char	cwd[4097];
	char	*path;

	while (ft_memcmp("HOME=", *envp, 5))
		envp++;
	home = *envp + 5;
	getcwd(cwd, 4096);
	if (ft_memcmp(cwd, home, ft_strlen(home)))
		path = ft_strdup(cwd);
	else
		path = ft_strjoin_2("~", cwd + ft_strlen(home));
	ft_putstr_fd( path , 1);
	ft_putstr_fd( ": " , 1);
	free(path);
}

void		get_input(t_data **data)
{
	char	buf;
	char*	bufstring;
	int		ret;
	int		i;

	i = 0;
	bufstring = ft_calloc(sizeof(char *), 2);
	while((ret = read(0 , &buf, 1)) && buf != '\n')
	{
		bufstring[0] = buf;
		bufstring[1] = '\0';
		(*data)->input = ft_strjoin((*data)->input,bufstring);
		i++;
	}
	free(bufstring);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	if (argc != 1)
		error_msg("Please type only one argument");
	init_struct(&data, argv, envp);
	signal(SIGQUIT, signal_handler);
	while (1)
	{
		open_prompt(data->envp);
		signal(SIGINT, signal_handler);
		get_input(&data);
		parser(&data);
		//exit (0); //retirar
	}
	return (0);
}
