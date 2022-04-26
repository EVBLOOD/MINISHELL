/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_exec__.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:34:50 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/26 02:16:48 by foulare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

char	*ft_wildmerging(t_list **list, char **str, int *wild, int *i)
{
	*str = ft_replaceandjoin(str, "*");
	(*wild)++;
	while (list[*i] && list[*i]->type == WILD)
		(*i)++;
	(*i)--;
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

void	normesok(int *i, int *wild, char **env)
{
	*i = 0;
	*wild = 0;
	(void)env;
}

t_befexec	*ft_merging(t_list **list, char **env)
{
	t_befexec	*head;
	int			wild;
	int			i;
	char		*str;

	normesok(&i, &wild, env);
	head = NULL;
	str = ft_strdup("");
	while (list[i] && (list[i]->type == SPACES || !list[i]->sqp))
		i++;
	while (list[i])
	{
		if (list[i]->type == VARIABLE)
			ft_varmerging(list[i], &str, &wild, &head);
		if (list[i]->type == DQ || list[i]->type == SQ || list[i]->type == WORD)
			str = ft_dq_sq_wrdmerging(list[i], &str, &wild);
		if (list[i]->type == WILD)
			str = ft_wildmerging(list, &str, &wild, &i);
		if (list[i]->type == SPACES || !list[i + 1])
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
