/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:23 by acosta-a          #+#    #+#             */
/*   Updated: 2022/08/28 16:57:04 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL2_H
# define MINISHELL2_H
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
# define ECHO 10
# define CD 11
# define PWD 12
# define EXPORT 13
# define UNSET 14
# define ENV 15
# define EXIT 16

typedef struct s_data
{
	char	**envp;
	char	**argv;
	int		**tokens;
	int		*len_tokens;
	int		*slicers;
	int		*slicers_types;
	int		*quotes_types;
	int		argc;
	char	*input;
	char	**pars_inpt;
	char	**pars_type;
	char	*path;
	char	**st_cmds;
	char	**params;
	char	***cmds;
}	t_data;

int		no_error_msg(char *message);
int		error_msg(char *message);
void	signal_handler(int	input);
char	*ft_strjoin_2(char *s1, char *s2);
void	parser(t_data **data);
#endif
