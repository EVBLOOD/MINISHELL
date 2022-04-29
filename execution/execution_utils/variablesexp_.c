/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variablesexp_.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:55:02 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/26 23:52:43 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

char	**ft_splitvar(char const *s, char *cmp)
{
	char		**table;
	size_t		i;
	size_t		len;
	int			spaces;

	i = 0;
	spaces = 0;
	if (!ft_splitchecks(s, &table, cmp))
		return (NULL);
	while (*s)
	{
		while (*s && ft_strchr(*s, cmp))
			normsplitvars(&s, &spaces);
		ft_spaces(&table, &i, &spaces, &len);
		while (s[len] && !ft_strchr(s[len], cmp))
			len++;
		if (len != 0)
			table[i++] = ft_substr(s, 0, len);
		if (len != 0 && !table[i - 1])
			return (NULL);
		s += len;
	}
	table[i] = NULL;
	return (table);
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	ft_addtotrush(ptr, &(g_exec.trush), 1);
	return (ptr);
}

char	**ft_varreturn(void)
{
	char	**var;

	var = ft_malloc(sizeof(char *) * 2);
	var[0] = ft_itoa(g_exec.returnvalue);
	var[1] = NULL;
	return (var);
}

char	*ft_cmdpathfound(char **env, t_list *list, int *found, int *i)
{
	char	*var;

	var = NULL;
	while (env[*i])
	{
		var = &list->splited[1];
		if (!ft_strncmp(env[*i], var, ft_strlen(var))
			&& env[*i][ft_strlen(var)] == '=')
		{
			*found = 1;
			break ;
		}
		(*i)++;
	}
	return (var);
}

char	**ft_expandvariables(t_list *list, char **env)
{
	int		i;
	int		strlen;
	int		found;
	char	*var;

	i = 0;
	found = 0;
	if (!ft_strcmp(list->splited, "$?"))
		return (ft_varreturn());
	var = ft_cmdpathfound(env, list, &found, &i);
	strlen = ft_strlen(var);
	var = list->splited;
	if (!found)
		list->splited = ft_strdup("");
	else
		list->splited = ft_strdup(&env[i][strlen + 1]);
	return (ft_splitvar(list->splited, " \t\n\v\f\r"));
}
