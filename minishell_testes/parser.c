
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

typedef struct s_conters
{
	int		i;
	int		j;
	int		k;
	char	c;
	int		counter;
	int		flag;
} t_conters;

void init_conters(t_conters *counters)
{
	counters->counter = 0;
	counters->flag = 0;
	counters->i = 0;
	counters->j = 0;
	counters->k = 0;
}

void	get_slicers(t_data **data, int k, int j, int i, int flag, int counter)
{
	char	c;

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
	// PARA TESTES
	i = 0;
	while(i < (int)ft_strlen((*data)->input))
		ft_putnbr_fd((*data)->slicers[i++],1);
	ft_putstr_fd("\n",1);
	// PARA TESTES
}

void slices(t_data **data)
{
	t_conters *cont;

	cont = malloc(sizeof(t_conters) * 1);
	while(cont->j < 2)
	{
		cont->i = 0;
		cont->k = 0;
		if((*data)->len_tokens[cont->j] > 0)
		{
			while(cont->i < (*data)->len_tokens[cont->j])
			{
				cont->flag = 0;
				cont->counter = 0;
				get_slicers(data, cont->k, cont->j, cont->i, cont->flag, cont->counter);
				/*
				while(cont->k < (*data)->tokens[cont->j][cont->i])
				{
					if(((*data)->input[cont->k] == '\'' || (*data)->input[cont->k] == '"') && cont->flag == 0)
					{
						cont->c = (*data)->input[cont->k];
						cont->flag = 1;
					}
					if((*data)->input[cont->k] == cont->c)
						cont->counter++;
					if(cont->j == 0 && cont->counter % 2 == 0 && ((*data)->input[cont->k + 1] == ';'))
						(*data)->slicers[cont->k] = (*data)->tokens[cont->j][cont->i];
					if(cont->j == 1 && cont->counter % 2 == 0 && ((*data)->input[cont->k + 1] == '|'))
						(*data)->slicers[cont->k] = (*data)->tokens[cont->j][cont->i];
					cont->k++;
				}
				*/
			cont->i++;
			}
		}
		cont->j++;
	}
}

/*
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
*/

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
