/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:23 by acosta-a          #+#    #+#             */
/*   Updated: 2022/09/26 23:59:42 by acosta-a         ###   ########.fr       */
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
# include <stdio.h>
# define ERROR 1
# define IN 0
# define OUT 1
# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_expand
{
	char			*var;
	char			*value;
	struct s_expand	*next;
}					t_expand;

typedef struct s_data
{
	char			**envp; /*clean_all*/
	char			**argv; /*clean_all*/
	int				**tokens; /*clean_all*/
	int				*len_tokens; /*clean_data*/
	int				*slicers; /*clean_data*/
	int				*slicers_types; /*clean_data*/
	int				*slicers_seq; /*clean_data*/
	int				crs; /*clean_data*/
	int				*quotes_types; /*clean_data*/
	int				argc;
	char			*input; /*clean_data*/
	char			*path; /*clean_data*/
	char			*pathcd;  /*clean_all*/
	char			*home_path; /*clean_all*/
	char			*tmp; /*clean_all*/
	char			**st_cmds; /*clean_all*/
	char			**params;  /*clean_data*/
	char			*dollar;  /*clean_all*/
	char			***cmds;  /*clean_data*/
	int				qtd_cmds;
	int				exit_return;
}	t_data;

typedef struct s_cursors
{
	int				i;
	int				j;
	int				i2;
	int				j2;
	int				k2;
	int				w;
	int				k;
	int				r;
	int				s;
	int				l;
	int				m;
	int				n;
	int				o;
	int				begin;
	int				last;
	char			c;
	char			q;
	char			h;
	char			*str; /*atila*/
	char			*temp;/*atila*/
	char			*str2;/*atila*/
	int				counter;
	int				flag;
	int				flagecho;
	int				len;
	int				output;/*atila*/
	int				input;/*atila*/
	int				saved_stdout;/*atila*/
	int				saved_stdin;/*atila*/
	int				status;/*atila*/
	pid_t			pid;/*atila*/
	int				err;
	//char			*pos;
	char			*ret;
	//char			*pointer;
}	t_cursors;

int		no_error_msg(char *message);
int		error_msg(char *message);
void	signal_handler(int	input);
char	*ft_strjoin_2(char *s1, char *s2);
int		parser(t_data **data);
void	reset_conters(t_cursors	**cursor);
void	init_crs(t_cursors	**cursor);

/*adicionado atila*/
/*MAIN FUNCTIONS*/
void	cmd_check(t_data **data);
void	cmd_check_2(t_data **data, t_cursors	*crs);
void	builtin_execute(t_data **data, int i, int flag, t_cursors *crs);
void	builtin_execute_2(t_data **data, int i, int flag, char *cmd1);
/*BUILTINS*/
int		ft_export(t_data **data, char *input);
int		ft_unset(t_data **data, char *input);
int		ft_cd(t_data **data, char *input, int i);
void	ft_cd_2(t_data **data, char *path);
int		ft_env(t_data **data, char *input);
int		ft_pwd(void);
void	ft_echo(t_data **data, char **input, t_cursors	*crs);
void	ft_here_doc(t_data **data, t_cursors *crs);
void	ft_bash(t_data **data);
/*DELIMITERS*/
void	one_substitution_2(char **cmd, int i, int x);
char	**cmd_one_substitution(char **cmd);
void	ft_pipe(t_data **data, int i, int flag, t_cursors *crs);
void	ft_output(t_data **data, t_cursors *crs);
void	ft_output_2(t_data **data, t_cursors *crs);
void	ft_input(t_data **data, t_cursors *crs);
void	execute(char *argv, t_data **data);
void	execute_pipe(char *argv, t_data **data);
void	ft_in_output(t_data **data, t_cursors *crs);
void	ft_here_doc_2(t_data **data, t_cursors *crs, int fd[2]);

/*utils*/
int		is_token(char s);
int		exec_error_msg(char *path);

/*adicionado por Marco*/
void	clean_data(t_data **data);
int		len_input(char **p);
void	print_error(int e);
char	**copy_env(char **envp, int add);
int		get_expand(t_data **data, char *param);
void	clean_all(t_data **data);
void	ft_exit(t_data **data);

#endif
