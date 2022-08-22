
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
int *sort_slicers(int *list_a, int *list_b)
{
    int i,j;
    int a[5]={1,4,8,9,11};
    int b[6]={3,6,7,10,15,25};
    int c[11];
    int aux;

    Copia vetor 'a' para a primeira metade do vetor 'c' 
    memcpy( c, a, sizeof(a) );

    Copia vetor 'b' para a segunda metade do vetor 'c'
    memcpy( c + 5, b, sizeof(b) );

    for(i=0;i<10;i++){
        for(j=0;j<10;j++){
        if(c[i] < c[j]){
           //nesta parte que ocorre a troca e ordenação de varíaveis
           aux = c[i]; //recebe o menor valor, na varável temporária aux
           c[i] = c[j]; // repete com todos os valores no loop
           c[j] = aux; // recebe em ordem crescente no vetor c[j]

        }
      }
    }

    for(i=0;i<10;i++){
        printf("%d\n",c[i]); //imprime os resultados em ordem crescente
    }
}

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
	int *slc_scolon;
	int *slc_pipe;

	slc_scolon = ft_calloc((*data)->len_tokens[0] + 1,sizeof(int));
	slc_pipe = ft_calloc((*data)->len_tokens[1] + 1,sizeof(int));
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
					if((*data)->input[k] == '\'' && flag == 0)
					{
						c = '\'';
						flag = 1;
					}
					else if ((*data)->input[k] == '"' && flag == 0)
					{
						c = '"';
						flag = 1;
					}
					if((*data)->input[k] == c)
						counter++;
					if(j == 0 && counter % 2 == 0 && (*data)->input[k + 1] == ';')
						slc_scolon[i] = (*data)->tokens[j][i];
					else if(j == 1 && counter % 2 == 0 && (*data)->input[k + 1] == '|')
						slc_pipe[i] = (*data)->tokens[j][i];
					k++;
				}
				i++;
			}
		}
		j++;
	}
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
	slices(data);
}
