/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varexp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 03:38:03 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/01 21:29:19 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

int	countspacesofvar(char *var)
{
	int	i;
	int	count;
	char	*str;

	str  = ft_strtrim(var, " \t\n\v\f\r");
	i = -1;
	count = 0;
	while (str[++i])
	{
		if (ft_strchr(str[i], " \t\n\v\f\r"))
		{
			count++;
			while (str[++i] && ft_strchr(str[i], " \t\n\v\f\r"));
			if (!str[i])
				break;
			i--;
		}
	}
	free(str);
	return (count);
}

char	**ft_splitvar(char *splited)
{
	int		i;
	int		j;
	int		x;
	char	**ret;

	i = -1;
	x = -1;
	j = 0;
	ret = malloc(sizeof(char *) * (countspacesofvar(splited) + 1));
	while (splited[++i])
	{
		if (ft_strchr(splited[i], " \t\n\v\f\r") || !splited[i + 1])
		{
			if (!splited[i + 1])
				(j++, i++);
			ret[++x] = ft_substr(splited, i - j, j);
			j = 0;
			while (splited[++i] && ft_strchr(splited[i], " \t\n\v\f\r"));
			if (!splited[i])
				break;
		}
		j++;
	}
	ret[++x] = NULL;
	x = 0;
	return (ret);
}

char	**ft_expandvariables(t_list *list, char **env)
{
	int		i;
	char	**val;
	int		found;
	char	*var;

	i = -1;
	found = 0;
	while (env[++i])
	{
		var = &list->splited[1];
		if (!ft_strncmp(env[i], var, ft_strlen(var)) && env[i][ft_strlen(var)] == '=')
		{
			found = 1;
			break;
		}
	}
	free(list->splited);
	if (!found)
		list->splited = ft_strdup("");
	else
		list->splited = ft_strdup(&env[i][ft_strlen(var) + 1]);
	var = list->splited;
	list->splited = ft_strtrim(list->splited, " \t\n\v\f\r");
	free(var);
	return (ft_splitvar(list->splited));
}