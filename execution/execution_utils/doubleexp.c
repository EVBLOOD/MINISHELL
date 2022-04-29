/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubleexp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:38:22 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/26 23:53:25 by sakllam          ###   ########.fr       */
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
	if (ft_strlen(s + start) < (int) len)
		p = (char *) ft_malloc((ft_strlen(s + start) + 1) * sizeof(char));
	else
		p = (char *) ft_malloc(((int) len + 1) * sizeof(char));
	if (!p)
		return (NULL);
	while (i < (int) len && s[i + start] && !((int)start >= ft_strlen(s)))
	{
		p[i] = s[i + start];
		i++;
	}
	p[i] = '\0';
	return (p);
}

void	ft_expandvariablesdq(char **var, char **env)
{
	int		i;
	int		found;
	char	*tmp;

	i = -1;
	found = 0;
	tmp = *var;
	if (!ft_strcmp(*var, "?"))
	{
		*var = ft_strdup(ft_itoa(g_exec.returnvalue));
		return ;
	}
	while (env[++i])
	{
		if (!ft_strncmp(env[i], *var, ft_strlen(*var))
			&& env[i][ft_strlen(*var)] == '=')
		{
			found = 1;
			break ;
		}
	}
	if (!found)
		*var = ft_strdup("");
	else
		*var = ft_strdup(&env[i][ft_strlen(*var) + 1]);
}

int	varlenghcounting(t_list *list, char **env, int *i)
{
	char	*var;
	int		j;
	int		count;

	j = 2;
	count = 0;
	if (ft_isdigit(list->splited[(*i) + 1]) || list->splited[(*i) + 1] == '?')
		var = ft_substr(list->splited, (*i) + 1, 1);
	else
	{
		j = 1;
		while (list->splited[(*i) + j]
			&& !ft_varvalidating(list->splited[(*i) + j]))
			j++;
		var = ft_substr(list->splited, (*i) + 1, j - 1);
	}
	ft_expandvariablesdq(&var, env);
	if (j == 1)
		count += 1;
	else
		count += ft_strlen(var);
	(*i) += j - 1;
	return (count);
}

int	ft_expand_dqcount(t_list *list, char **env)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (list->splited[++i])
	{
		if (ft_strchr(list->splited[i], "$"))
			count += varlenghcounting(list, env, &i);
		else
			count++;
	}
	return (count - 1);
}

void	ft_outerret(t_list *list, char **env, char **var)
{
	int		j;

	j = 1;
	if (ft_isdigit(list->splited[1]) || list->splited[1] == '?')
		*var = ft_substr(list->splited, 1, 1);
	else
	{
		while (list->splited[j] && !ft_varvalidating(list->splited[j]))
			j++;
		*var = ft_substr(list->splited, 1, j - 1);
		j--;
	}
	ft_expandvariablesdq(var, env);
	list->splited += j;
}
