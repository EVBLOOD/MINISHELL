/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_exec__.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:34:50 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/25 01:35:43 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

char	*ft_wildmerging(t_list **list, char **str, int *wild, int *i)
{
	*str = ft_replaceandjoin(str, "*");
	(*wild)++;
	while (list[*i] && list[*i]->TYPE == WILD)
		(*i)++;
	(*i)--;
	return (*str);
}

char	*ft_dq_sq_wrdmerging(t_list *list, char **str, int *wild)
{
	int	i;

	i = 0;
	*str = ft_replaceandjoin(str, list->splited);
	while (list->splited[i])
	{
		if (list->splited[i] == '*')
			(*wild)--;
		i++;
	}
	return (*str);
}

void	ft_merginginspaces(int *wild, t_befexec **head, char **str)
{
	if ((*wild) > 0)
		ft_wildmergin(str, head);
	else
		ft_ofcadd_back(head, ft_createnode(*str));
	*str = ft_strdup("");
	*wild = 0;
}

t_befexec	*ft_merging(t_list **list, char **env)
{
	t_befexec	*head;
	int			wild;
	int			i;
	char		*str;

	wild = 0;
	i = 0;
	head = NULL;
	str = ft_strdup("");
	while (list[i] && (list[i]->TYPE == SPACES || !list[i]->sqp))
		i++;
	while (list[i])
	{
		if (list[i]->TYPE == VARIABLE)
			ft_varmerging(list[i], &str, &wild, &head);
		if (list[i]->TYPE == DQ || list[i]->TYPE == SQ || list[i]->TYPE == WORD)
			str = ft_dq_sq_wrdmerging(list[i], &str, &wild);
		if (list[i]->TYPE == WILD)
			str = ft_wildmerging(list, &str, &wild, &i);
		if (list[i]->TYPE == SPACES || !list[i + 1])
			ft_merginginspaces(&wild, &head, &str);
		i++;
	}
	return (head);
}

char	**ft_dealwithlist(t_list **list, char **env)
{
	char		**converted;
	t_befexec	*ret;
	t_befexec	*tmp;
	int			i;

	ft_replaceall(list, env);
	ret = ft_merging(list, env);
	converted = ft_convertfromlisttochar(ret);
	while (ret)
	{
		tmp = ret;
		ret = ret->next;
	}
	return (converted);
}
