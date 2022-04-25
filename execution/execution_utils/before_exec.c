/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:30:51 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/25 22:56:12 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

char	*ft_expand_sq(t_list *list)
{
	int		i;
	char	*str;

	str = ft_malloc(ft_strlen(list->splited) - 1);
	if (!str)
		return (NULL);
	i = 1;
	while (list->splited[i] != 39)
	{
		str[i - 1] = list->splited[i];
		i++;
	}
	str[i - 1] = '\0';
	return(str);
}

t_befexec	*ft_createnode(char *str)
{
	t_befexec	*node;

	node = ft_malloc(sizeof(t_befexec));
	node->ofcvalue = str;
	node->next = NULL;
	return (node);
}

char	*ft_replaceexpand_dq(t_list **list, char **env)
{
	char	*tmp;

	tmp = (*list)->splited;
	(*list)->splited = ft_expand_dq(*list, env);
	return ((*list)->splited);
}

char	*ft_replaceexpand_sq(t_list **list)
{
	char	*str;
	str = ft_expand_sq(*list);
	return (str);
}

void	ft_replaceall(t_list **list, char **env)
{
	int		i;
	char	*str;

	i = 0;
	while (list[i] && (list[i]->TYPE == SPACES || !list[i]->sqp))
		i++;
	while (list[i])
	{
		if (list[i]->TYPE == VARIABLE && env)
			list[i]->expanded = ft_expandvariables(list[i], env);
		if (list[i]->TYPE == SQ)
			list[i]->splited = ft_replaceexpand_sq(&(list[i]));
		if (list[i]->TYPE == DQ)
			list[i]->splited = ft_replaceexpand_dq(&(list[i]), env);
		if (list[i]->TYPE == WORD)
		{
			str = list[i]->splited;	
			list[i]->splited = ft_strdup(list[i]->splited);
		}
		i++;
	}
}