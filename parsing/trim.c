/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:49:28 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/24 21:17:39 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static int	ft_front(const char *s1, const char *set)
{
	int	i;
	int	j;
	int	countf;

	i = 0;
	countf = 0;
	while (s1[i])
	{
		j = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
				countf++;
			j++;
		}
		i++;
		if (countf != i)
			break ;
	}
	return (countf);
}

static int	ft_end(const char *s1, const char *set)
{
	int	i;
	int	j;
	int	countb;

	countb = 0;
	i = ft_strlen(s1) - 1;
	while (i >= 0)
	{
		j = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
				countb++;
			j++;
		}
		if ((int)ft_strlen(s1) - i != countb)
			break ;
		i--;
	}
	return (countb);
}

static char	*ft_error(void)
{
	char	*ret;

	ret = ft_malloc(1);
	if (!ret)
		return (NULL);
	ret[0] = '\0';
	return (ret);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		countf;
	int		countb;
	char	*ret;

	if (!s1 || !set)
		return (NULL);
	countf = ft_front(s1, set);
	countb = ft_end(s1, set);
	if ((unsigned int) countb == ft_strlen(s1))
		return (ft_error());
	ret = ft_malloc(((ft_strlen(s1) - (countb + countf)) + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (countf < ((int)ft_strlen(s1) - countb))
	{
		ret[i] = s1[countf];
		countf++;
		i++;
	}
	ret[i] = '\0';
	return (ret);
}