/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 02:43:17 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/15 01:35:02 by sakllam          ###   ########.fr       */
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

// void	ft_switch(t_list **head, t_list *new)
// {
// 	if
// }

// t_list	*ft_douleit(t_list *list)
// {
// 	t_list	*list_;
// 	t_list	*start;

// 	list_ = NULL;
// 	start = list;
// 	while (list)
// 	{
// 		list->nb;
// 		list->splited;
// 		list->TYPE;
// 		if (!isredirections(list->TYPE))
// 		{
// 			ft_lstadd_back(&list_, list);
// 			ft_lstadd_back(&list_, list->next);
// 		}
// 		if (list->TYPE == PIPE || list->TYPE == OR || list->TYPE == AND || !list->next)
// 		{
// 			while ()
// 			{

// 			}
// 		}
// 		list = list->next;
// 	}
// }


// t_list	*ft_redirectionsset(t_list *lst)
// {
// 	t_list *words;
// 	t_list *reds;
// 	t_list	*tmp;
// 	t_list	*node;
// 	t_list	*tmpall;

// 	tmp = lst;
// 	tmpall = lst; //to free
// 	reds = NULL;
// 	words = NULL;
// 	while (lst)
// 	{
// 		if (!isredirections(lst->TYPE))
// 		{
// 			node = malloc(sizeof(t_list));
// 			node->nb = lst->nb;
// 			node->splited = lst->splited;
// 			node->TYPE = lst->TYPE;
// 			node->next = NULL;
// 			ft_lstadd_back(&reds, node);
// 			lst = lst->next;
// 			if (lst->TYPE == SPACES)
// 				lst = lst->next;
// 			while (lst && (lst->TYPE == WORD || lst->TYPE == WILD || lst->TYPE == SQ || lst->TYPE == DQ))
// 			{
// 				node = malloc(sizeof(t_list));
// 				node->nb = lst->nb;
// 				node->splited = lst->splited;
// 				node->TYPE = lst->TYPE;
// 				node->next = NULL;
// 				ft_lstadd_back(&reds, node);
// 				lst = lst->next;
// 			}
// 		}
// 		if (!lst || lst->TYPE == PIPE || lst->TYPE == OR || lst->TYPE == AND || lst->TYPE == PRTCLOSE || !lst->next)
// 		{
// 			t_list *end;
// 			if (lst)
// 				end = lst->next;
// 			else
// 				end = lst;
// 			lst = tmp;
// 			while (lst != end)
// 			{
// 				if (isredirections(lst->TYPE))
// 				{
// 					node = malloc(sizeof(t_list));
// 					node->nb = lst->nb;
// 					node->splited = lst->splited;
// 					node->TYPE = lst->TYPE;
// 					node->next = NULL;
// 					ft_lstadd_back(&reds, node);
// 				}
// 				else
// 				{
// 					lst = lst->next;
// 					if (lst->TYPE == SPACES)
// 						lst = lst->next;
// 					while (lst && (lst->TYPE == WORD || lst->TYPE == WILD || lst->TYPE == SQ || lst->TYPE == DQ))
// 						lst = lst->next;
// 					// lst = lst->next;
// 					// while (lst->TYPE == SPACES)
// 					// 	lst = lst->next;
// 					// lst = lst->next;
// 				}
// 				if (lst)
// 					lst = lst->next;
// 			}
// 			tmp = lst;
// 			// while (words)
// 			// {
// 			// 	ft_lstadd_back(&reds, words);
// 			// 	words = words->next;
// 			// }
// 		}
// 		if (lst)
// 			lst = lst->next;
// 	}
// 	// while (reds)
// 	// {
// 	// 	printf("splited: %s\n", reds->splited);
// 	// 	printf("type: %d\n", reds->TYPE);
// 	// 	reds = reds->next;
// 	// }
// 	return (reds);
// }

t_list	*ft_createnodes(int nb, int type, char *splited)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	node->nb = nb;
	node->splited = splited;
	node->TYPE = type;
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
		node = ft_createnodes(lst->nb, lst->TYPE, lst->splited);
		ft_lstadd_back(head, node);
		return (lst->next);
	}
	else
		return (lst);
}

void	ft_ohmyspace(t_list **head)
{
	t_list *node;

	node = ft_createnodes(0, SPACES, NULL);
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
		node = ft_createnodes(lst->nb, lst->TYPE, lst->splited);
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
			node = ft_createnodes(lst->nb, lst->TYPE, lst->splited);
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
			node = ft_createnodes(lst->nb, lst->TYPE, lst->splited);
			ft_lstadd_back(head, node);
			lst = lst->next;
		}
	}
	if (lst && !ft_redirectiononecon(lst))
	{
		node = ft_createnodes(lst->nb, lst->TYPE, lst->splited);
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