/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variablesexp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:52:24 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/25 01:53:20 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

void	normsplitvars(char const **s, int *spaces)
{
	(*s)++;
	*spaces = 1;
}
void	normsplitvarstwo(int *i, int *spaces)
{
	(*i)++;
	(*spaces) = 1;
}

static size_t	ft_count(char const *s, char *cmp)
{
	int	i;
	int	count;
	int	spaces;

	i = 0;
	count = 0;
	spaces = 0;
	while (s[i] != '\0')
	{
		while (s[i] && ft_strchr(s[i], cmp))
			normsplitvarstwo(&i, &spaces);
		if (spaces)
		{
			count++;
			spaces = 0;
		}
		if (s[i] != '\0')
		{
			if ((ft_strchr(s[i - 1], cmp) || i == 0))
				count++;
			i++;
		}
	}
	return (count);
}

void	ft_spaces(char ***str, size_t *i, int *spaces, size_t *len)
{
	if (*spaces)
	{
		(*str)[(*i)++] = ft_strdup(" ");
		*spaces = 0;
	}
	*len = 0;
}

char	**ft_splitchecks(char const *s, char ***table, char *cmp)
{
	if (!s)
		return (NULL);
	if (!(*table))
		return (*table);
	*table = (char **)ft_malloc((ft_count(s, cmp) + 1) * sizeof(char *));
	return (*table);
}
