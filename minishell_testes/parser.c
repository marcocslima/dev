
#include "minishell.h"

void	get_token(t_data **data, char token, int n)
{
	int	*tok;
	int	lenstr;
	int	i;
	int	t;

	i = -1;
	t = 0;
	lenstr = ft_strlen((*data)->input);
	while ((*data)->input[++i])
		if((*data)->input[i] == token)
			t++;
	if(t == 0)
		(*data)->tokens[n] = NULL;
	else
	{
		(*data)->len_tokens[n] = t;
		tok = calloc(t,sizeof(int));
		i = -1;
		t = 0;
		while (++i < lenstr)
			if((*data)->input[i] == token)
				tok[t++] = i;
		(*data)->tokens[n] = tok;
	}
}

typedef struct s_cursors
{
	int		i;
	int		j;
	int		k;
	int		begin;
	int		last;
	char	c;
	char	q;
	char	h;
	int		counter;
	int		flag;
	int		len;
} t_cursors;

void	reset_conters(t_cursors	*cursor)
{
	cursor->counter = 0;
	cursor->flag = 0;
}

void	init_cursors(t_cursors	*cursor)
{
	reset_conters(cursor);
	cursor->i 		= 0;
	cursor->j 		= 0;
	cursor->k 		= 0;
	cursor->begin	= 0;
	cursor->last	= 0;
	cursor->c		= '\0';
	cursor->q		= '\0';
	cursor->h		= '\0';
	cursor->len		= 0;
}

void get_params(char **cmds, int n)
{
	t_cursors	*crs;

	crs = malloc(sizeof(t_cursors));
	init_cursors(crs);
	crs->len = ft_strlen(cmds[n]);

	while (crs->i < crs->len)
	{
		if(cmds[n][crs->i] == '\'' && crs->flag == 0)
		{
			crs->q = '\'';
			crs->flag = 1;
			crs->begin = crs->i;
		}
		else if(cmds[n][crs->i] == '"' && crs->flag == 0)
		{
			crs->q = '"';
			crs->flag = 1;
			crs->begin = crs->i;
		}
		if (crs->q)
			crs->last = ft_findrchr(cmds[n], crs->q);
		crs->i++;
	}
	free(crs);
}


void get_cmds(t_data ** data, t_cursors *cursor)
{
	init_cursors(cursor);
	cursor->len = ft_strlen((*data)->input);

	while (cursor->i < cursor->len)
	{
		if((*data)->slicers[cursor->i] != 0)
			(*data)->input[cursor->i + 1] = 1;
		ft_putchar_fd((*data)->input[cursor->i], 1);
		cursor->i++;
	}
	ft_putstr_fd("\n\n",1);
	cursor->i = 0;
	while (cursor->i < cursor->len)
	{
		if((*data)->slicers[cursor->i] != 0)
			cursor->counter++;
		cursor->i++;
	}
	char **cmds = malloc(sizeof(size_t) * cursor->counter + 1);
	cmds = ft_split((*data)->input, 1);
	cursor->i = 0;
	while (cursor->i < cursor->counter + 1)
	{
		get_params(cmds, cursor->i);
		cursor->i++;
		/*
		ft_putstr_fd(cmds[cursor->i],1);
		ft_putstr_fd("\n",1);
		cursor->i++;
		*/
	}
	//ft_putstr_fd("\n\n",1);
	free(cursor);
}

void	get_slicers(t_data **data, t_cursors *cursor, char slc, int index)
{
	while(cursor->i < (*data)->len_tokens[index])
	{
		reset_conters(cursor);
		while(cursor->k < (*data)->tokens[index][cursor->i])
		{
			if(((*data)->input[cursor->k] == '\'' || (*data)->input[cursor->k] == '"'))
				cursor->q = (*data)->input[cursor->k];
			if(((*data)->input[cursor->k] == '\'' || (*data)->input[cursor->k] == '"') && cursor->flag == 0)
			{
				cursor->c = (*data)->input[cursor->k];
				cursor->flag = 1;
			}
			if((*data)->input[cursor->k] == cursor->c)
				cursor->counter++;
			if(cursor->counter % 2 == 0 && ((*data)->input[cursor->k + 1] == slc))
			{
				(*data)->slicers[cursor->k] = (*data)->tokens[index][cursor->i];
				(*data)->slicers_types[cursor->k] = cursor->q;
				reset_conters(cursor);
			}
			cursor->k++;
		}
	cursor->i++;
	}
}

void parser(t_data	**data)
{
	char		token[9] = ";|'\" $\\<>";
	char		slicers[1] = ";";
	t_cursors	*cursor;
	int			i;
	int			s;

	i = -1;
	s = -1;
	(*data)->tokens = malloc(sizeof(size_t) * 7);
	(*data)->len_tokens = ft_calloc(7,sizeof(int));
	while(++i < 7)
		get_token(data, token[i], i);
	(*data)->slicers = ft_calloc(ft_strlen((*data)->input),sizeof(int));
	(*data)->slicers_types = ft_calloc(ft_strlen((*data)->input),sizeof(int));
	cursor = malloc(sizeof(t_cursors));
	while(++s < 1)
	{
		init_cursors(cursor);
		get_slicers(data, cursor, slicers[s], s);
	}
	get_cmds(data, cursor);

	/*
	// PARA TESTES*******************************************
	i = 0;
	ft_putstr_fd("\n",1);
	ft_putstr_fd("Posição dos separadores: ", 1);
	while(i < (int)ft_strlen((*data)->input))
	{
		if((*data)->slicers[i] == 0)
			ft_putstr_fd("*", 1);
		else
			ft_putnbr_fd((*data)->slicers[i],1);
		i++;
	}
	i = 0;
	ft_putstr_fd("\n",1);
	ft_putstr_fd("Tipos de aspas: ", 1);
	while(i < (int)ft_strlen((*data)->input))
	{
		if((*data)->slicers_types[i] == 0)
			ft_putstr_fd("*", 1);
		else
			ft_putnbr_fd((*data)->slicers_types[i],1);
		i++;
	}
	ft_putstr_fd("\n\n",1);

	// PARA TESTES*******************************************
	*/
}
