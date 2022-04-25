/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 02:43:17 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/19 01:37:07 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	isredirections(int type)
{
	if (type == RDAPP || type == RDHER || type == RDIN || type == RDOUT)
		return (0);
	return (1);
}

int	isnextaword(t_list *lst)
{
	if (lst->TYPE == WORD || lst->TYPE == WILD)
		return (0);
	return (1);
}

t_list	*ft_createnodes(t_list *lst)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	node->nb = lst->nb;
	node->herdocexp = lst->herdocexp;
	node->splited = lst->splited;
	node->sqp = lst->sqp;
	node->TYPE = lst->TYPE;
	node->nb = lst->nb;
	node->next = NULL;
	return (node);
}

int	ft_redirectiononecon(t_list *lst)
{
	return (lst
		&& lst->TYPE != PIPE
		&& lst->TYPE != OR
		&& lst->TYPE != AND
		&& lst->TYPE != PRTOPEN
		&& lst->TYPE != PRTCLOSE);
}

int	ft_isthatared(t_list *lst)
{
	return (lst->TYPE == RDAPP
		|| lst->TYPE == RDHER
		|| lst->TYPE == RDIN
		|| lst->TYPE == RDOUT);
}

t_list	*ft_creatspacenode(t_list *lst, t_list **head)
{
	t_list *node;

	if (lst && lst->TYPE == SPACES)
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

	node = malloc(sizeof(t_list));
	node->nb = nb;
	node->splited = splited;
	node->TYPE = type;
	node->next = NULL;
	return (node);
}

void	ft_ohmyspace(t_list **head)
{
	t_list *node;

	node = ft_createnodesspaces(0, SPACES, NULL);
	ft_lstadd_back(head, node);
}

t_list	*ft_secondarg(t_list *lst, t_list **head)
{
	t_list	*node;

	while (lst && 
		(lst->TYPE == WORD
		|| lst->TYPE == WILD
		|| lst->TYPE == SQ
		|| lst->TYPE == DQ
		|| lst->TYPE == VARIABLE))
	{
		node = ft_createnodes(lst);
		ft_lstadd_back(head, node);
		lst = lst->next;
	}
	return (lst);
}

t_list	*ft_redirectionone(t_list *lst, t_list **head)
{
	t_list *node;

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

t_list	*passeover(t_list *lst)
{
	while (ft_redirectiononecon(lst))
	{
		lst = lst->next;
		if (lst && lst->TYPE == SPACES)
			lst = lst->next;
		while (lst && 
			(lst->TYPE == WORD
			|| lst->TYPE == WILD
			|| lst->TYPE == SQ
			|| lst->TYPE == DQ
			|| lst->TYPE == VARIABLE))
			lst = lst->next;
		if (lst && lst->TYPE == SPACES)
			lst = lst->next;
		break;
	}
	return (lst);
}

t_list	*ft_redirectiontwo(t_list *lst, t_list *end, t_list **head)
{
	t_list *node;

	if (*head && ft_lstlast(*head)->TYPE != SPACES && lst->TYPE != SPACES)
		ft_ohmyspace(head);
	while (lst != end)
	{
		if (ft_isthatared(lst))
			lst = passeover(lst);
		else
		{
			node = ft_createnodes(lst);
			ft_lstadd_back(head, node);
			lst = lst->next;
		}
	}
	if (lst && !ft_redirectiononecon(lst))
	{
		node = ft_createnodes(lst);
		ft_lstadd_back(head, node);
		lst = lst->next;
		lst = ft_creatspacenode(lst, head);
	}
	return (lst);
}

t_list	*ft_redirectionsset(t_list *lst)
{
	t_list	*end;
	t_list	*head;

	head = NULL;
	while (42)
	{
		end = ft_redirectionone(lst, &head);
		end = ft_redirectiontwo(lst, end, &head);
		lst = end;
		if (!lst)
			break;
	}
	return (head);
}