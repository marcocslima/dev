/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 07:44:08 by acosta-a          #+#    #+#             */
/*   Updated: 2022/08/20 00:53:15 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "minishell2.h"
/*
void	cmd_space_substitution(t_data **data)
{
	int	i;

	i = 0;
	while ((*data)->input[i])
	{
		if ((*data)->input[i] == '\'' || (*data)->input[i] == '\"')
		{
			i++;
			if ((*data)->input[i] == '\'' || (*data)->input[i] == '\"')
				i++;
			while ((*data)->input[i] != '\'' && (*data)->input[i] != '\"' && (*data)->input[i])
			{
				if ((*data)->input[i] == ' ')
					(*data)->input[i] = '9';
				i++;
			}
		}
		i++;
	}
	(*data)->input[i] = '\0';
}
*/

void		parser(t_data **data)
{
//  char *str = "echo abd' hkjhk\'   jlkj'";
//	char **res;
	int *quotes;
	int *spaces;
//	int *slice;
	int q = -1;
	int s = -1;
	int i = 0;
	int len;
	int j = 0;
	int k = 0;

	len = ft_strlen((*data)->input);

	quotes = calloc(len,sizeof(int));
	spaces = calloc(len,sizeof(int));
//	slice = calloc(len,sizeof(int));

	while((*data)->input[i++])
	{
	if((*data)->input[i] == '\'' || (*data)->input[i] == '\"')
		quotes[++q] = i;
	if((*data)->input[i] == ' ')
		spaces[++s] = i;
	}
	len = 0;
	while(quotes[len])
		len++;
	if(len%2 > 0)
		printf("Non finished quotes");
	i = 0;
	s = -1;
	q = 0;
	quotes[-1] = 0;

//função abaixo está separando os inputs fora e dentro das aspas mas essa função apenas verifica se elas forem fechadas e abertas consecutivamente exemplo:
//echo 'a' "b"  .....No caso de ' "a" "b" ' ela não funciona
		while(quotes[q]){
			if (q % 2 == 0){
				(*data)->pars_inpt[k] = ft_substr((*data)->input,j,quotes[q] - j);
				printf("pars_inpt[%d] input: %s  ",k,(*data)->pars_inpt[k]);}
			if (q % 2 != 0){
				(*data)->pars_inpt[k] = ft_substr((*data)->input,j - 1,quotes[q] - j + 2);
				printf("pars_inpt[%d] input: %s  ",k,(*data)->pars_inpt[k]);}
		j = quotes[q] + 1;
		k++;
		q++;
		}
//função abaixo retorna a posição onde a aspas mãe é fechada caso exista uma, caso não ela retorna zero Exemplo: "a 'b'" retorna 6 diferente de "a" 'b' que retorna 0
	i = 0;
	int finalquoteindex = 0;
	while(quotes[finalquoteindex])
	{
		if ((*data)->input[quotes[0]] != (*data)->input[quotes[1]])
			if ((*data)->input[quotes[0]] == (*data)->input[quotes[finalquoteindex]])
				break;
	finalquoteindex ++;
	}
	printf("finalquoteindex[%d] ",quotes[finalquoteindex]);

}
