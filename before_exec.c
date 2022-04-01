/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saad <saad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 13:55:00 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/01 15:16:43 by saad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

int	ft_countchars(t_list **list, int start, int end)
{
	int	i;
	int	extra_i;
	int	count;

	i = start;
	count = 0;
	while (i <= end)
	{
		if (list[i]->TYPE == VARIABLE && i != end)
		{
			extra_i = 0;
			while (list[i]->elements[extra_i])
				i++;
			count += ft_strlen(list[i]->elements[extra_i -1]);
		}
		if (list[i]->TYPE == VARIABLE && i == end)
		{
			count += ft_strlen(list[i]->elements[0]);
		}
		if (list[i]->TYPE == SQ)
			count += ft_strlen(list[i]->splited);
		if (list[i]->TYPE == DQ)
			count += ft_strlen(list[i]->splited);
		if (list[i]->TYPE == WORD)
			count += ft_strlen(list[i]->splited);
		i++;
	}
}

void	ft_substrlist(t_list **list, int start, int end)
{
	// int		i;
	// int		lengh;
	// int		extra_i;
	// char	*str;

	// i = 0;
	// lengh = ft_countchars(list, start, end);
	int		i;
	int		extra_i;
	char	*str;
	char	*tmp;

	i = start;
	str = ft_strdup("");
	while (i <= end)
	{
		if (list[i]->TYPE == VARIABLE && i != end)
		{
			extra_i = 0;
			while (list[i]->elements[extra_i])
				extra_i++;
			tmp = str;
			str = ft_strjoin(str, list[i]->elements[extra_i -1]);
			free(tmp);
		}
		if (list[i]->TYPE == VARIABLE && i == end)
		{
			tmp = str;
			str = ft_strjoin(str, list[i]->elements[0]);
			free(tmp);
		}
		if (list[i]->TYPE == SQ)
		{
			tmp = str;
			str = ft_strjoin(str, list[i]->splited);
			free(tmp);
		}
		if (list[i]->TYPE == DQ)
		{
			tmp = str;
			str = ft_strjoin(str, list[i]->splited);
			free(tmp);
		}
		if (list[i]->TYPE == WORD)
		{
			tmp = str;
			str = ft_strjoin(str, list[i]->splited);
			free(tmp);
		}
		if (list[i]->TYPE == WILD)
		{
			tmp = str;
			str = ft_strjoin(str, "*");
			free(tmp);
			while (list[i] && list[i]->TYPE == WILD)
				i++
			i--;
		}
		i++;
	}
	i = 0;
	// while
	return (str);
}

void	ft_expandingwildcard(t_list **list, char **env, int red)
{
	int		i;
	int		laststart;
	int		wild;

	i = 0;
	laststart = 0;
	wild = 0;
	while (list[i])
	{
		if (list[i]->TYPE == WILD)
			wild = 1;
		if (list[i]->TYPE == VARIABLE)
		{
			if ((!list[i]->elements[0] || list[i]->elements[1]) && wild)
			{
				ft_substrlist(list, laststart, i);
				wild = 0;
			}
			if (!list[i]->elements[0] || list[i]->elements[1])
				laststart = i;

		}
		if (list[i]->TYPE == SPACES)
		{
			if (wild)
			{
				ft_substrlist(list, laststart, i);
				wild = 0;
			}
			laststart = i;
		}
		i++;
	}
}

void	ft_replaceall(t_list **list, char **env, int red)
{
	int		i;
	char	*str;

	i = 0;
	while (list[i])
	{
		if (list[i]->TYPE == VARIABLE)
		{
			list[i]->elements = ft_expandvariables(list, env);
			if (!(list[0]->elements) && red)
				break;
		}
		if (list[i]->TYPE == SQ)
		{
			str = ft_expand_sq(list[i]);
			free(list[i]->splited);
			list[i]->splited = str;
		}
		if (list[i]->TYPE == DQ)
		{
			str = ft_expand_dq(list[i], env);
			free(list[i]->splited);
			list[i]->splited = str;
		}
		if (list[i]->TYPE == SPACES && red)
			break;
		i++;
	}
}

char	**ft_dealwithlist(t_list **list, char **env, int red)
{
	ft_replaceall(list, env, red);
	ft_expandingwildcard(list, env, red);
}