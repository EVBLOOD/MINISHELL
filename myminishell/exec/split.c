/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 02:39:21 by sakllam           #+#    #+#             */
/*   Updated: 2022/03/15 19:22:56 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char	*ft_nostart(void)
{
	char	*s;

	s = (char *)malloc(sizeof(char) * 1);
	s[0] = 0;
	return (s);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	int		i;

	i = 0;
	if (!s)
		return (0);
	if (start > ft_strlen(s))
		return (ft_nostart());
	if (len > ft_strlen(s) - start)
		dest = (char *)malloc(sizeof(char) * (ft_strlen(s) - start + 1));
	else
		dest = (char *)malloc(len + 1);
	if (!dest)
		return (NULL);
	while (s[start] && len > 0 && (start < ft_strlen(s)))
	{
		dest[i] = s[start];
		start++;
		i++;
		len--;
	}
	dest[i] = '\0';
	return (dest);
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

static char	**free_tab(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char		**str;
	size_t		i;
	size_t		len;

	i = 0;
	if (!s)
		return (0);
	str = (char **)malloc((ft_count(s, c) + 1) * sizeof(*str));
	if (!str)
		return (str);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		len = 0;
		while (s[len] && s[len] != c)
			len++;
		if (len != 0)
			str[i++] = ft_substr(s, 0, len);
		if (len != 0 && !str[i - 1])
			return (free_tab(str));
		s += len;
	}
	str[i] = NULL;
	return (str);
}