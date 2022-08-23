
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
int *slicers(t_data **data, int n)
{
	int *slc;
	int i;
	int j;

	i = 0;
	j = 0;
	slc = ft_calloc(n,sizeof(int));
	while(i < n)
	{
		if((*data)->tokens[0][i] < (*data)->tokens[1][j])
		{
			slc[i] = (*data)->tokens[0][i];
			i++;
		}
		else
		{
			slc[i] = (*data)->tokens[1][j];
			j++;
		}
	}
}
*/

void slices(t_data **data)
{
	int i;
	int j;
	int k;
	char c;
	int counter;
	int flag;

	j = 0;
	while(j < 2)
	{
		i = 0;
		k = 0;
		if((*data)->len_tokens[j] > 0)
		{
			while(i < (*data)->len_tokens[j])
			{
				flag = 0;
				counter = 0;
				while(k < (*data)->tokens[j][i])
				{
					if(((*data)->input[k] == '\'' || (*data)->input[k] == '"') && flag == 0)
					{
						c = (*data)->input[k];
						flag = 1;
					}
					if((*data)->input[k] == c)
						counter++;
					if(j == 0 && counter % 2 == 0 && ((*data)->input[k + 1] == ';'))
						(*data)->slicers[k] = (*data)->tokens[j][i];
					if(j == 1 && counter % 2 == 0 && ((*data)->input[k + 1] == '|'))
						(*data)->slicers[k] = (*data)->tokens[j][i];
					k++;
				}
				i++;
			}
		}
		j++;
	}
	// PARA TESTES
	i=0;
	while(i < (int)ft_strlen((*data)->input))
		ft_putnbr_fd((*data)->slicers[i++],1);
	ft_putstr_fd("\n",1);
	// PARA TESTES
}

void parser(t_data	**data)
{
	char	token[7] = ";|'\" $\\";
	int		i;

	i = -1;
	(*data)->tokens = malloc(sizeof(size_t) * 7);
	(*data)->len_tokens = ft_calloc(7,sizeof(int));
	while(++i < 7)
		get_token(data, token[i], i);
	(*data)->slicers = ft_calloc(ft_strlen((*data)->input),sizeof(int));
	slices(data);
}
