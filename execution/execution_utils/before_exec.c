/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saad <saad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:30:51 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/30 18:25:28 by saad             ###   ########.fr       */
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
	return (str);
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

	i = 0;
	while (list[i] && (list[i]->type == SPACES || !list[i]->sqp))
		i++;
	while (list[i])
	{
		if (list[i]->type == VARIABLE)
			list[i]->expanded = ft_expandvariables(list[i], env);
		if (list[i]->type == SQ)
			list[i]->splited = ft_replaceexpand_sq(&(list[i]));
		if (list[i]->type == DQ)
			list[i]->splited = ft_replaceexpand_dq(&(list[i]), env);
		if (list[i]->type == WORD)
			list[i]->splited = ft_strdup(list[i]->splited);
		i++;
	}
}
