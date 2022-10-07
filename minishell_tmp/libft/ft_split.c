/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosta-a <acosta-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 13:04:31 by mcesar-d          #+#    #+#             */
/*   Updated: 2022/10/06 08:56:45 by acosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
static int		count_substrings(char const *s, char c);
static size_t	add_string_to_arr(char **arr, int i, char *s, char c);
void			free_previous_allocations(char **arr, int i);

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	substring_size;
	int		i;

	if (!s)
		return (NULL);
	arr = malloc(sizeof(char *) * (count_substrings(s, c) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			substring_size = add_string_to_arr(arr, i, (char *)s, c);
			if (!substring_size)
				return (NULL);
			s += substring_size;
			i++;
		}
	}
	arr[i] = NULL;
	return (arr);
}

size_t	add_string_to_arr(char **arr, int i, char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	arr[i] = malloc(sizeof(char) * (len + 20));
	if (!arr[i])
	{
		free_previous_allocations(arr, i);
		return (0);
	}
	if (!(ft_strlcpy(arr[i], s, len + 1)))
		return (0);
	return (len);
}

int	count_substrings(char const *s, char c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	return (i);
}

void	free_previous_allocations(char **arr, int i)
{
	while (i--)
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	free(arr);
	arr = NULL;
}
*/
//delketar
static int	words_counter(const char *s, char c)
{
	size_t	i;
	int		flag;
	int		counter;

	i = 0;
	flag = 0;
	counter = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && s[i] != '\0' && flag == 0)
		{
			counter++;
			flag = 1;
		}
		else if (s[i] == c)
			flag = 0;
		i++;
	}
	return (counter);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		flag;
	char	**result;

	i = 0;
	j = 0;
	flag = -1;
	result = (char **)malloc((words_counter(s, c) + 1) * sizeof(char *));
	if (!s || !result)
		return (0);
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && flag < 0)
			flag = i;
		else if ((s[i] == c || i == ft_strlen(s)) && flag >= 0)
		{
			result[j++] = ft_substr(s, flag, i - flag);
			flag = -1;
		}
		i++;
	}
	result[j] = 0;
	return (result);
}



