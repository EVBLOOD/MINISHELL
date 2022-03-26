/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:03:23 by sakllam           #+#    #+#             */
/*   Updated: 2022/03/26 17:18:29 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		k;
	int		count;
	char	*p;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	k = ft_strlen(s2);
	count = i + k + 1;
	p = (char *) malloc(count * sizeof(char));
	if (!p)
		return (NULL);
	i = 0;
	k = i;
	while (s1[k])
		p[i++] = s1[k++];
	k = 0;
	while (s2[k])
		p[i++] = s2[k++];
	p[i] = '\0';
	return (p);
}

static size_t	ft_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			if ((s[i - 1] == c || i == 0))
				count++;
			i++;
		}
	}
	return (count);
}

static char	**free_table(char **table)
{
	int	i;

	i = 0;
	while (table[i])
		free(table[i++]);
	free(table);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char		**table;
	size_t		i;
	size_t		len;

	i = 0;
	if (!s)
		return (0);
	table = (char **)malloc((ft_count(s, c) + 1) * sizeof(*table));
	if (!table)
		return (table);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		len = 0;
		while (s[len] && s[len] != c)
			len++;
		if (len != 0)
			table[i++] = ft_substr(s, 0, len);
		if (len != 0 && !table[i - 1])
			return (free_table(table));
		s += len;
	}
	table[i] = NULL;
	return (table);
}
