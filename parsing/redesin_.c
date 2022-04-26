/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redesin_.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:13:01 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/26 04:31:46 by foulare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

t_list	*ft_creatspacenode(t_list *lst, t_list **head)
{
	t_list	*node;

	if (lst && lst->type == SPACES)
	{
		node = ft_createnodes(lst);
		ft_lstadd_back(head, node);
		return (lst->next);
	}
	else
		return (lst);
}

t_list	*ft_createnodesspaces(int nb, int type, char *splited)
{
	t_list	*node;

	node = ft_malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->nb = nb;
	node->splited = splited;
	node->type = type;
	node->next = NULL;
	return (node);
}

void	ft_ohmyspace(t_list **head)
{
	t_list	*node;

	node = ft_createnodesspaces(0, SPACES, NULL);
	ft_lstadd_back(head, node);
}

t_list	*ft_secondarg(t_list *lst, t_list **head)
{
	t_list	*node;

	while (lst && (lst->type == WORD
			|| lst->type == WILD
			|| lst->type == SQ
			|| lst->type == DQ
			|| lst->type == VARIABLE))
	{
		node = ft_createnodes(lst);
		ft_lstadd_back(head, node);
		lst = lst->next;
	}
	return (lst);
}

t_list	*ft_redirectionone(t_list *lst, t_list **head)
{
	t_list	*node;

	while (ft_redirectiononecon(lst))
	{
		if (ft_isthatared(lst))
		{
			node = ft_createnodes(lst);
			ft_lstadd_back(head, node);
			lst = lst->next;
			lst = ft_creatspacenode(lst, head);
			lst = ft_secondarg(lst, head);
			lst = ft_creatspacenode(lst, head);
		}
		else
			lst = lst->next;
	}
	return (lst);
}
