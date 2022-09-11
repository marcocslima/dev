/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 12:21:07 by mcesar-d          #+#    #+#             */
/*   Updated: 2022/09/11 20:25:37 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "test.h"

typedef struct s_expand
{
    char            *var;
    char            *value;
    struct s_expand *next;
}                   t_expand;

char	**copy_env(char **envp, int add)
{
	int		i;
	int		len;
	char	**copy;

	len = 0;

	while (envp[len])
		len++;
	if (!(copy = (char **)ft_calloc(sizeof(char *), (len + add + 1))))
		return (0);
	i = -1;
	while (i++ < len - 1)
		copy[i] = ft_strdup(envp[i]);
	return (copy);
}

char	*get_value(char **envp, char *var)
{
	int len = ft_strlen(var);
	while (ft_strncmp(var, *envp, len))
		envp++;
	return (*envp + len + 1);
}

int main(int argc, char **argv, char **envp) {
	(void)argc;
	(void)argv;
	int i = -1;
	int j = -1;
	int len = 0;
	int c;
	char *begin;
	char **mat;
	t_list *list;
	t_list *aux;
	t_expand **exp;
	char	**env;
	//char *ret;
	char input[] = "i $HOME m $PATH t";

	env = copy_env(envp, 3);
	while (input[++i])
		if(input[i] == '$' && input[i + 1] != ' ')
			len++;
	mat = malloc(sizeof(size_t) * len);
	exp = malloc(sizeof(size_t) * len);
	i = -1;
	while (++i < len)
		exp[i] = malloc(sizeof(t_expand));
	i = 0;
	while (i < len)
	{
		while (input[++j])
		{
			c = 0;
			if(input[j] == '$' && input[j + 1] != ' ')
			{
				begin = &input[j + 1];
				while(input[j++] != ' ')
					c++;
				mat[i] = calloc(c, sizeof(char));
				ft_strlcpy(mat[i], begin, c);
				i++;
			}
		}
	}
	i = -1;
	while (++i < len)
		exp[i]->var = mat[i];
	list = ft_lstnew(exp[0]);
	i = 1;
	while (i < len)
	{
		ft_lstadd_back(&list, ft_lstnew(exp[i]));
		i++;
	}
	aux = list;
	i = 0;
	while(i < len)
	{
		((t_expand *)(*aux).content)->value = get_value(env, ((t_expand *)(*aux).content)->var);
		aux = aux->next;
		i++;
	}
	return 0;
}