/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 02:43:17 by sakllam           #+#    #+#             */
/*   Updated: 2022/03/26 16:55:11 by sakllam          ###   ########.fr       */
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


t_list	*ft_redirectionsset(t_list *lst)
{
	t_list *words;
	t_list *reds;
	t_list	*tmp;
	t_list	*node;
	t_list	*tmpall;

	tmp = lst;
	tmpall = lst; //to free
	reds = NULL;
	words = NULL;
	while (lst)
	{
		if (!isredirections(lst->TYPE))
		{
			node = malloc(sizeof(t_list));
			node->nb = lst->nb;
			node->splited = lst->splited;
			node->TYPE = lst->TYPE;
			node->next = NULL;
			ft_lstadd_back(&reds, node);
			lst = lst->next;
			if (lst->TYPE == SPACES)
				lst = lst->next;
			while (lst && (lst->TYPE == WORD || lst->TYPE == WILD || lst->TYPE == SQ || lst->TYPE == DQ))
			{
				node = malloc(sizeof(t_list));
				node->nb = lst->nb;
				node->splited = lst->splited;
				node->TYPE = lst->TYPE;
				node->next = NULL;
				ft_lstadd_back(&reds, node);
				lst = lst->next;
			}
		}
		if (!lst || lst->TYPE == PIPE || lst->TYPE == OR || lst->TYPE == AND || lst->TYPE == PRTCLOSE || !lst->next)
		{
			t_list *end;
			if (lst)
				end = lst->next;
			else
				end = lst;
			lst = tmp;
			while (lst != end)
			{
				if (isredirections(lst->TYPE))
				{
					node = malloc(sizeof(t_list));
					node->nb = lst->nb;
					node->splited = lst->splited;
					node->TYPE = lst->TYPE;
					node->next = NULL;
					ft_lstadd_back(&reds, node);
				}
				else
				{
					lst = lst->next;
					if (lst->TYPE == SPACES)
						lst = lst->next;
					while (lst && (lst->TYPE == WORD || lst->TYPE == WILD || lst->TYPE == SQ || lst->TYPE == DQ))
						lst = lst->next;
					// lst = lst->next;
					// while (lst->TYPE == SPACES)
					// 	lst = lst->next;
					// lst = lst->next;
				}
				if (lst)
					lst = lst->next;
			}
			tmp = lst;
			// while (words)
			// {
			// 	ft_lstadd_back(&reds, words);
			// 	words = words->next;
			// }
		}
		if (lst)
			lst = lst->next;
	}
	// while (reds)
	// {
	// 	printf("splited: %s\n", reds->splited);
	// 	printf("type: %d\n", reds->TYPE);
	// 	reds = reds->next;
	// }
	return (reds);
}
