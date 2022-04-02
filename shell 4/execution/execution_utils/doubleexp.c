/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubleexp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 03:41:58 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/01 20:25:57 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*p;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s + start) < len)
		p = (char *) malloc((ft_strlen(s + start) + 1) * sizeof(char));
	else
		p = (char *) malloc(((int) len + 1) * sizeof(char));
	if (!p)
		return (NULL);
	while (i < (int) len && s[i + start] && !(start >= ft_strlen(s)))
	{
		p[i] = s[i + start];
		i++;
	}
	p[i] = '\0';
	return (p);
}

void	ft_expandvariablesdq(char **var, char **env)
{
	int	i;
	int	found;

	i = -1;
	found = 0;
	while (env[++i])
		if (!ft_strncmp(env[i], *var, ft_strlen(*var)) && env[i][ft_strlen(*var)] == '=')
		{
			found = 1;
			break;
		}
	free(*var);
	if (!found)
		*var = ft_strdup("");
	else
		*var = ft_strdup(&env[i][ft_strlen(*var) + 1]);
}

int	ft_expand_dqcount(t_list *list, char **env)
{
	int		i;
	int		j;
	int		count;
	char	*var;

	i = -1;
	count = 0;
	while (list->splited[++i])
	{
		if (ft_strchr(list->splited[i], "$"))
		{
			j = 2;
			if (ft_isdigit(list->splited[i + 1]))
				var = ft_substr(list->splited, i + 1, 1);
			else
			{
				j = 1;
				while (list->splited[i + j] && !ft_varvalidating(list->splited[i + j]))
					j++;
				var = ft_substr(list->splited, i + 1, j - 1);
			}
			ft_expandvariablesdq(&var, env);
			if (j == 1)
				count += 1;
			else
				count += ft_strlen(var);
			free(var);
			i += j - 1;
		}
		else
			count++;
	}
	return (count - 1);
}

char	*ft_expand_dq(t_list *list, char **env)
{
	char	*var;
	char	*result;
	int		i;
	int		j;
	int		index;

	result = malloc(ft_expand_dqcount(list, env));
	i = 0;
	index = -1;
	while (list->splited[++i])
	{
		if (ft_strchr(list->splited[i], "$"))
		{
			j = 2;
			if (ft_isdigit(list->splited[i + 1]))
				var = ft_substr(list->splited, i + 1, 1);
			else
			{
				j = 1;
				while (list->splited[i + j] && !ft_varvalidating(list->splited[i + j]))
					j++;
				var = ft_substr(list->splited, i + 1, j - 1);
			}
			ft_expandvariablesdq(&var, env);
			i += j - 1;
			if (j == 1)
				result[++index] = list->splited[i];
			else
			{
				j = -1;
				while (var[++j])
					result[++index] = var[j];
			}
			free(var);
		}
		else
			result[++index] = list->splited[i];
	}
	result[index] = '\0';
	return (result);
}
