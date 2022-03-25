/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_findtypeofword.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 10:03:25 by sakllam           #+#    #+#             */
/*   Updated: 2022/03/10 08:53:55 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	ft_findouttype(char *element)
{
	int	i;

	i = 0;
	if (element[0] == '$')
		return ('v');
	if (element[0] == 39)
		return('s');
	if (element[0] == 34)
		return ('d');
	if (element[0] == 42)
		return ('c');
	return ('w');
}

int	ft_findvarinsided(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (line[i] == '$')
			return (i);
	return (-1);
}

char	*ft_variableshow(char *var, t_env **env)
{
	char	*finded;
	t_env	*node;

	node = ft_getenv(env, var);
	if (!node)
		return (ft_strdup(""));
	return (ft_strdup(&node->value[ft_strlen(var)]));
}

char	*ft_variablename(char *line, t_env **env)
{
	int		i;
	int		y;
	char	*var;

	i = ft_findvarinsided(line);
	line = line + i;
	i = 0;
	if(line[i]  != '_' && !ft_isalpha(line[i]))
	{
		while (line[++i] && ft_varvalidating(line[i]));
		var = malloc(i + 2);
		if (!var)
			return (NULL);
		y = -1;
		while (++y < i)
			var[y] = line[y];
		var[y] = '=';
		var[y + 1] = '\0';
	}
	return (var);
}

int	ft_strlenfuture(char *line, t_env *env)
{
	int	x;

	x = 0;
	while (1)
	{
		if (ft_findvarinsided(line) >= 0)
		{
			x += ft_findvarinsided(line);
			line = line + x;
			x += ft_strlen(ft_variableshow(line, &env));
			line = line + ft_strlen(ft_variablename(line, &env));
		}
	}
	return (x);
}

char	*ft_scanvar(char **line, t_env *env)
{
	int		nbr_alloc;
	char	*var;
	char	*value;
	char	*new;
	int		i;
	int		y;
	int		j;
	int		end;

	i = -1;
	y = -1;
	nbr_alloc = ft_strlenfuture(*line, env);
	new = malloc(nbr_alloc + 1);
	// tmp = *line;
	end = ft_findvarinsided(*line);
	while ((*line)[++i])
	{
		if (i == end)
		{
			if (ft_findvarinsided(&(*line)[i + 1]) >= 0)
				end = ft_findvarinsided(&(*line)[i + 1]) + i + 1;
			var = ft_variablename(&(*line)[i], &env);
			value = ft_variableshow(var, &env);
			free (var);
			j = -1;
			while (value[++j])
				new[++y] = value[j];
			free(value);
		}
		new[++y] = (*line)[i];
	}
	new[++y] = '\0';
	return (new);
}