/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <chaves_87@hotmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 01:53:55 by acosta-a          #+#    #+#             */
/*   Updated: 2022/06/14 03:58:03 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_lenfunc(char const *s, char c)
{
	unsigned int	word_len;

	word_len = 0;
	while (s[word_len] != c && s[word_len] != '\0')
	{
		word_len++;
	}
	return (word_len);
}

static	int	count_words(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

char	**ft_split(char *s, char c)
{
	int		i;
	int		j;
	int		numwords;
	int		word_len;
	char	**array;

	i = 0;
	j = 0;
	numwords = count_words(s, c);
	array = (char **)malloc(sizeof(char *) * (numwords + 1));
	if (!s || !array)
		return (NULL);
	while (numwords > j)
	{
		word_len = 0;
		while (s[i] == c && s[i != '\0'])
			i++;
		word_len = word_lenfunc(&s[i], c);
		while (s[i] != c && s[i] != '\0')
			i++;
		array [j++] = ft_substr(s, i - word_len, word_len);
	}
	array[j] = 0;
	return (array);
}
