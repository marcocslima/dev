/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:23 by acosta-a          #+#    #+#             */
/*   Updated: 2022/10/31 15:28:02 by mcesar-d         ###   ########.fr       */
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
	char			**envp;
	char			**argv;
	int				**tokens;
	int				*len_tokens;
	int				*slicers;
	int				*slicers_types;
	int				*slicers_seq;
	int				crs;
	int				jump;
	int				*quotes_types;
	int				argc;
	char			*input;
	char			*path;
	char			*pathcd;
	char			*home_path;
	char			*tmp;
	char			*tmp2;
	char			**st_cmds;
	char			**params;
	char			*dollar;
	char			***cmds;
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
	char			*str;
	char			*temp;
	char			*str2;
	int				counter;
	int				flagpipe;
	int				flag;
	int				flagecho;
	int				flagfork;
	int				len;
	int				output;
	int				input;
	int				saved_stdout;
	int				saved_stdin;
	int				status;
	pid_t			pid;
	int				err;
	char			*ret;
}	t_cursors;

int		no_error_msg(char *message);
int		error_msg(char *message);
void	signal_handler(int input);
void	child_signal_handler(int input);
char	*ft_strjoin_2(char *s1, char *s2);
int		parser(t_data **data);
void	reset_conters(t_cursors	**cursor);
void	get_params_exchange(t_data **data, t_cursors *crs, int n);
void	init_crs(t_cursors	**cursor);

/*MAIN FUNCTIONS*/
void	cmd_check(t_data **data);
void	cmd_check_2(t_data **data, t_cursors	*crs);
void	cmd_check_2_1(t_data **data, t_cursors *crs);
void	builtin_execute(t_data **data, t_cursors *crs);
void	builtin_execute_2(t_data **data, char *cmd2, t_cursors *crs);
/*BUILTINS*/
int		ft_export(t_data **data, char *input, t_cursors *crs);
int		ft_unset(t_data **data, char *input);
int		ft_cd(t_data **data, char *input, int i);
void	ft_cd_2(t_data **data, char *path);
int		ft_env(t_data **data, char *input);
int		ft_pwd(void);
void	ft_echo(t_data **data, char **input, t_cursors	*crs);
void	echo_input_change(t_data **data, int k, int i, int j);
void	ft_here_doc(t_data **data, t_cursors *crs);
void	ft_bash(t_data **data);
/*DELIMITERS*/
void	one_substitution_2(char **cmd, int i, int x);
char	**cmd_one_substitution(char **cmd);
void	ft_pipe(t_data **data, int i, int flag, t_cursors *crs);
void	ft_output(t_data **data, t_cursors *crs);
void	ft_output_2(t_data **data, t_cursors *crs);
void	ft_input(t_data **data, t_cursors *crs);
void	ft_doc_pipe_2(t_data **data, t_cursors *crs);
void	ft_fork_1(t_data **data, t_cursors *crs);
void	ft_input_doc_pipe(t_data **data, t_cursors *crs);
void	execute(char *argv, t_data **data);
//void	execute_pipe(char *argv, t_data **data);
char	*cmd_space_substitution(char *argv);
void	*pathexec(char *cmd, char *envp[]);
void	execute_pipe(char *argv, t_data **data, t_cursors *crs);
int		ft_in_output(t_data **data, t_cursors *crs);
void	ft_here_doc_2(t_data **data, t_cursors *crs, int fd[2]);
void	redir_stdin(t_data **data, t_cursors *crs);
void	redir_stdin_out(t_data **data, t_cursors *crs);
void	no_input(t_data **data, t_cursors *crs, int flag);

/*utils*/

void	init_struct(t_data **data, char **argv, char **envp);
int		verify_quotes(t_data **data);
int		is_token(char s);
int		exec_error_msg(char *path, t_data **data);
char	*ft_clean_quotes(char *s, char c);
void	quotes_index(char *s, char c, int init, int end);
int		input_error_msg(char *path, t_data **data, t_cursors *crs);
int		input_error_msg_noexit(char *path, t_data **data, t_cursors *crs);

/*Exit and Clean*/
void	clean_data(t_data **data);
int		count_cmds(t_data **data);
void	free_paths(char *home_path, char *pathcd);
void	destroy_pointers_int(int **p);
int		len_input(char **p);
void	print_error(int e);
char	**copy_env(char **envp, int add);
int		get_expand(t_data **data, char *param);
void	clean_all(t_data **data, t_cursors *crs);
void	ft_exit(t_data **data, t_cursors *crs);
void	destroy_pointers_char(char **p);
void	init_scream(void);
void	clean_init(t_data **data);

#endif
