
#include "minishell.h"


//@@@@@@@@ Para testes @@@@@@@@
void	ver(char *scr)
{
	t_cursors	*crs;

	init_crs(&crs);
	while(scr[crs->i])
	{
		ft_putchar_fd(scr[crs->i], 1);
		crs->i++;
	}
	ft_putchar_fd('\n', 1);
	while(scr[crs->j])
	{
		ft_putnbr_fd(scr[crs->j], 1);
		ft_putchar_fd(' ', 1);
		crs->j++;
	}
	ft_putchar_fd('\n', 1);
	free(crs);
}
//@@@@@@@@ Para testes @@@@@@@@

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

void	get_limits(t_cursors **crs, char **st_cmds, int n, int i)
{
	(*crs)->flag = 0;
	while (i < (*crs)->len)
	{
		if(st_cmds[n][i] == '\'' && (*crs)->flag == 0)
		{
			(*crs)->q = '\'';
			(*crs)->flag = 1;
			(*crs)->begin = i;
		}
		else if(st_cmds[n][i] == '"' && (*crs)->flag == 0)
		{
			(*crs)->q = '"';
			(*crs)->flag = 1;
			(*crs)->begin = i;
		}
		if ((*crs)->q && (*crs)->last < (*crs)->begin)
			(*crs)->last = ft_findrchr(st_cmds[n], (*crs)->q);
		i++;
	}
}

void get_params(t_data ** data, char *st_cmd, int n)
{
	t_cursors	*crs;

	init_crs(&crs);
	crs->len = ft_strlen(st_cmd);
	get_limits(&crs, &st_cmd, 0, crs->i); // 0 era n : VERIFICAR !!
	while (crs->l++ < crs->len)
	{
		if(crs->l > crs->last)
			get_limits(&crs, &st_cmd, 0, crs->i = crs->l);
		if(crs->l > crs->begin && crs->l < crs->last)
			if(st_cmd[crs->l] == ' ')
				st_cmd[crs->l] = 1;
	}
	(*data)->params = ft_split(st_cmd, ' ');
	while((*data)->params[crs->r] != NULL)
	{
		while((*data)->params[crs->r][crs->m])
			if((*data)->params[crs->r][++crs->m] == 1)
				(*data)->params[crs->r][crs->m] = ' ';
		crs->m = 0;
		crs->r++;
	}
	(*data)->cmds[n] = (*data)->params;
	free(crs);
}

void get_cmds(t_data ** data, t_cursors *cursor)
{
	init_crs(&cursor);
	cursor->len = ft_strlen((*data)->input);
	while (cursor->i < cursor->len)
	{
		if((*data)->slicers[cursor->i] != 0)
			(*data)->input[cursor->i + 1] = 1;
		cursor->i++;
	}
	while (cursor->j < cursor->len)
	{
		if((*data)->slicers[cursor->j] != 0)
			cursor->counter++;
		cursor->j++;
	}
	(*data)->st_cmds = malloc(sizeof(size_t) * cursor->counter + 1);
	(*data)->cmds = malloc(sizeof(size_t) * cursor->counter + 1);
	while (cursor->k < cursor->counter + 1)
		(*data)->cmds[cursor->k++] = malloc(sizeof(size_t));
	(*data)->st_cmds = ft_split((*data)->input, 1);
	while (cursor->r < cursor->counter + 1)
	{
		get_params(data, (*data)->st_cmds[cursor->r], cursor->r);
		cursor->r++;
	}
	free(cursor);
}

void	get_slicers(t_data **data, t_cursors *cursor, char slc, int index)
{
	while(cursor->i < (*data)->len_tokens[index])
	{
		reset_conters(&cursor);
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
				reset_conters(&cursor);
			}
			cursor->k++;
		}
	cursor->i++;
	}
}

void parser(t_data	**data)
{
	char		token[9] = ";|'\" $\\<>";
	char		slicers[2] = ";|";
	t_cursors	*cursor;
	int			i;
	int			s;

	i = -1;
	s = -1;
	(*data)->tokens = malloc(sizeof(size_t) * 9);
	(*data)->len_tokens = ft_calloc(9,sizeof(int));
	while(++i < 9)
		get_token(data, token[i], i);
	(*data)->slicers = ft_calloc(ft_strlen((*data)->input),sizeof(int));
	(*data)->slicers_types = ft_calloc(ft_strlen((*data)->input),sizeof(int));
	while(++s < 2)
	{
		init_crs(&cursor);
		get_slicers(data, cursor, slicers[s], s);
	}
	get_cmds(data, cursor);
}
