/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saad <saad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:10:12 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/30 18:21:11 by saad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	ft_herdoccreating(t_list **lst)
{
	char	*lem;
	char	*join;
	t_list	*tmp;

	lem = ft_strdup("");
	tmp = *lst;
	*lst = (*lst)->next;
	while (*lst && (*lst)->type == SPACES)
		*lst = (*lst)->next;
	while (*lst && ((*lst)->type == WILD
			|| (*lst)->type == WORD || (*lst)->type == SQ
			|| (*lst)->type == DQ || (*lst)->type == VARIABLE))
	{
		if (ft_herdocexptype(lst, tmp, &join))
			return (0);
		lem = ft_strjoin(lem, join);
		*lst = (*lst)->next;
	}
	tmp->splited = ft_herdoc(&lem);
	*lst = tmp;
	return (1);
}
