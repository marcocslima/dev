/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 11:59:29 by acosta-a          #+#    #+#             */
/*   Updated: 2022/10/17 22:17:37 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_2(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*dest;

	i = 0;
	j = 0;
	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	dest = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	if (s1)
		while (s1[i] != '\0')
			dest[i++] = s1[j++];
	j = 0;
	while (s2[j])
		dest[i++] = s2[j++];
	dest[i] = '\0';
	return (dest);
}

void	reset_conters(t_cursors	**cursor)
{
	(*cursor)->counter = 0;
	(*cursor)->flag = 0;
}

void	init_crs(t_cursors	**cursor)
{
	(*cursor) = (t_cursors *)ft_calloc(sizeof(t_cursors), 1);
	(*cursor)->counter = 0;
	(*cursor)->flag = 0;
	(*cursor)->flagpipe = 8;
	(*cursor)->flagfork = 0;
	(*cursor)->i = 0;
	(*cursor)->j = 0;
	(*cursor)->i2 = 0;
	(*cursor)->j2 = 0;
	(*cursor)->k2 = 0;
	(*cursor)->w = 0;
	(*cursor)->k = 0;
	(*cursor)->r = 0;
	(*cursor)->s = 0;
	(*cursor)->l = -1;
	(*cursor)->m = -1;
	(*cursor)->n = -1;
	(*cursor)->begin = 0;
	(*cursor)->last = 0;
	(*cursor)->c = '\0';
	(*cursor)->q = '\0';
	(*cursor)->h = '\0';
	(*cursor)->len = 0;
	(*cursor)->err = 0;
}

int	is_token(char s)
{
	char	token[9] = ";|'\" $\\<>";
	int		i;

	i = 0;
	while (token[i] != s)
		i++;
	if (token[i] == s)
		return (1);
	return (0);
}

char	*ft_clean_quotes(char *s, char c)
{
	int	init;
	int	end;
	int	len;
	int	flag;

	init = 0;
	end = 0;
	flag = 0;
	len = -1;
	while (s[++len])
	{
		if (flag == 0 && (s[len] == '"' || (s[len] == '\\' && (
			s[len + 1] == '\'' || s[len + 1] == '"' || s[len + 1] == '\\'
				|| s[len + 1] == c))))
		{
			init++;
			len ++;
			flag = 1;
		}
		else if (s[len] == '"' || s[len] == '\'' || s[len] == '\\')
			end = len - 1;
	}
	if (init > 0)
		s = ft_substr(s, init, end);
	return (s);
}
