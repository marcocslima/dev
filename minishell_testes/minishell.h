/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:23 by acosta-a          #+#    #+#             */
/*   Updated: 2022/09/10 19:15:30 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <fcntl.h>
# include <dirent.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
#include <stdio.h> //deletar
# define ERROR 1
# define EMPTY 0
# define CMD 1
# define ARG 2
# define TRUNC 3
# define APPEND 4
# define INPUT 5
# define PIPE 6
# define COLON 7

# define IN 0
# define OUT 1
# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_data
{
	char	**envp;
	char	**argv;
	int		**tokens;
	int		*len_tokens;
	int		*slicers;
	int		*slicers_types;
	int		*slicers_seq;
	int		crs;
	int		*quotes_types;
	int		argc;
	char	*input;
	char	*path;
	char	*tmp;
	char	**st_cmds;
	char	**params;
	char	***cmds;
	int		qtd_cmds;
	int		exit_return;
}	t_data;

typedef struct s_cursors
{
	int		i;
	int		j;
	int		k;
	int		r;
	int		l;
	int		m;
	int		n;
	int		begin;
	int		last;
	char	c;
	char	q;
	char	h;
	int		counter;
	int		flag;
	int		len;
	int		err;
	char	*pointer;
}	t_cursors;

int		no_error_msg(char *message);
int		error_msg(char *message);
void	signal_handler(int	input);
char	*ft_strjoin_2(char *s1, char *s2);
int		parser(t_data **data);
void	reset_conters(t_cursors	**cursor);
void	init_crs(t_cursors	**cursor);

//adicionado atila
int		cmd_check(t_data **data);
int		ft_export(t_data **data, char *input);
int		ft_unset(t_data **data, char *input);
void	ft_cd(t_data **data, char *input);
int		ft_pwd(void);
void	ft_echo(t_data **data, char **input, t_cursors	*crs);
void	one_substitution_2(char **cmd, int i, int x);
char	**cmd_one_substitution(char **cmd);
void	ft_pipe(t_data **data);
void	ft_output(t_data **data);

//adicionado por Marco
void clean_data(t_data **data);
int	len_input(char **p);
void print_error(int e);

#endif
