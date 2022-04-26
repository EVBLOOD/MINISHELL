/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstract_tree_.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:21:05 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/26 04:20:07 by foulare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

t_list	*ft_firstredr(t_list *nav, t_list *end)
{
	int	count;

	count = 0;
	while (nav != end)
	{
		if ((nav)->type == PRTOPEN)
			count++;
		if ((nav)->type == PRTCLOSE)
			count--;
		if ((nav->type == RDAPP || nav->type == RDHER
				|| nav->type == RDIN || nav->type == RDOUT) && !count)
			return (nav);
		nav = nav->next;
	}
	return (NULL);
}

t_list	*ft_createredirectionnode(t_list *redirection)
{
	t_list	*node;

	node = ft_malloc(sizeof(t_list));
	node->expanded = redirection->expanded;
	node->fd = redirection->fd;
	node->herdocexp = redirection->herdocexp;
	node->nb = redirection->nb;
	node->splited = redirection->splited;
	node->sqp = redirection->sqp;
	node->type = redirection->type;
	node->next = NULL;
	redirection->sqp = 0;
	return (node);
}

t_list	*noderedirections(t_list *list, t_list *end)
{
	t_list	*redirection;
	t_list	*newlist;
	t_list	*node;

	redirection = ft_firstredr(list, end);
	redirection = redirection->next;
	newlist = NULL;
	while (redirection != end && redirection->type == SPACES)
		redirection = redirection->next;
	while (redirection != end && redirection->type != SPACES
		&& isredirections(redirection->type) && redirection->type != PRTOPEN)
	{
		node = ft_createredirectionnode(redirection);
		ft_lstadd_back(&newlist, node);
		redirection = redirection->next;
	}
	return (newlist);
}

t_list	**ft_nextalpha(t_list **list, t_list *end)
{
	t_list	**redirection;

	redirection = NULL;
	(*redirection) = ft_firstredr(*list, end);
	(*redirection) = (*redirection)->next;
	while ((*redirection) != end && (*redirection)->type == SPACES)
		(*redirection) = (*redirection)->next;
	while ((*redirection) != end && (*redirection)->type != SPACES)
		(*redirection) = (*redirection)->next;
	while ((*redirection) != end && (*redirection)->type == SPACES)
		(*redirection) = (*redirection)->next;
	return (redirection);
}

int	ft_checkforptr(t_list *lst, t_list *end)
{
	while (lst != end)
	{
		if (lst->type == PRTOPEN)
			return (1);
	}
	return (0);
}
