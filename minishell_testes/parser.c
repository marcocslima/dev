
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
/*
void quotes(t_data **data)
{
	if ((*data)->tokens[2] && (*data)->tokens[3])
	{
		if(((*data)->tokens[2][0] < (*data)->tokens[3][0]))
			{
				ft_putstr_fd("single quotes ", 1);
				ft_putnbr_fd((*data)->len_tokens[2], 1);
				ft_putstr_fd("\n", 1);
			}
			else
			{
				ft_putstr_fd("double quotes ", 1);
				ft_putnbr_fd((*data)->len_tokens[3], 1);
				ft_putstr_fd("\n", 1);
			}
	}
}
*/
void slices(t_data **data)
{
	int i;
	int k;

	i = 0;
	k = -1;
	if((*data)->len_tokens[0] > 0)
	{
		while(i < (*data)->len_tokens[0])
		{	
			while((*data)->tokens[2] && ((*data)->tokens[2][k] < (*data)->tokens[0][i]))
				k++;
			if(k % 2 == 0)
				ft_putstr_fd("É um separador ", 1);
			i++;
		}
	}
}

void parser(t_data	**data)
{
	char	token[7] = ";|'\" $\\";
	int		i;

	i = -1;
	(*data)->tokens = malloc(sizeof(size_t) * 7);
	(*data)->len_tokens = calloc(7,sizeof(int));
	while(++i < 7)
		get_token(data, token[i], i);
	slices(data);
}
