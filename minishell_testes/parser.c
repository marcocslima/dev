
#include "minishell2.h"

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
	char	c;
	int		counter;
	int		flag;
} t_cursors;

void	init_cursors(t_cursors	**cursor)
{
	(*cursor)->counter = 0;
	(*cursor)->flag = 0;
	(*cursor)->i = 0;
	(*cursor)->j = 0;
	(*cursor)->k = 0;
}

void	get_slicers(t_data **data, t_cursors **cursor, char slc, int index)
{
	while((*cursor)->i < (*data)->len_tokens[index])
	{
		(*cursor)->flag = 0;
		(*cursor)->counter = 0;
		while((*cursor)->k < (*data)->tokens[index][(*cursor)->i])
		{
			if(((*data)->input[(*cursor)->k] == '\'' || (*data)->input[(*cursor)->k] == '"') && (*cursor)->flag == 0)
			{
				(*cursor)->c = (*data)->input[(*cursor)->k];
				(*cursor)->flag = 1;
			}
			if((*data)->input[(*cursor)->k] == (*cursor)->c)
				(*cursor)->counter++;
			if((*cursor)->counter % 2 == 0 && ((*data)->input[(*cursor)->k + 1] == slc))
				(*data)->slicers[(*cursor)->k] = (*data)->tokens[index][(*cursor)->i];
			(*cursor)->k++;
		}
	(*cursor)->i++;
	}
}

void parser(t_data	**data)
{
	char		token[7] = ";|'\" $\\";
	char		slicers[2] = ";|";
	t_cursors	**cursor;
	int			i;
	int			s;

	i = -1;
	s = -1;
	(*data)->tokens = malloc(sizeof(size_t) * 7);
	(*data)->len_tokens = ft_calloc(7,sizeof(int));
	while(++i < 7)
		get_token(data, token[i], i);
	(*data)->slicers = ft_calloc(ft_strlen((*data)->input),sizeof(int));
	(*data)->quotes_type = ft_calloc(ft_strlen((*data)->input),sizeof(int));
	cursor = malloc(sizeof(t_cursors));
	while(++s < 2)
	{
		init_cursors(cursor);
		get_slicers(data, cursor, slicers[s], s);
	}
	free(cursor);

	// PARA TESTES*******************************************
	i = 0;
	while(i < (int)ft_strlen((*data)->input))
		ft_putnbr_fd((*data)->slicers[i++],1);
	ft_putstr_fd("\n",1);
	i = 0;
	while(i < (int)ft_strlen((*data)->input))
		ft_putnbr_fd((*data)->quotes_type[i++],1);
	ft_putstr_fd("\n",1);
	// PARA TESTES*******************************************
}
