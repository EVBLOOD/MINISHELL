/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstract_tree___.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:22:48 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/25 01:24:02 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

t_tree	*ft_operatorsnode(t_list **parsresult, t_list *end)
{
	t_list	*tmp;
	t_list	*next;
	t_tree	*node;

	node = NULL;
	tmp = (*parsresult);
	next = ft_lastop(*parsresult, end);
	node = ft_malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	node->type =  next->TYPE;
	node->right = ft_abs(&(next->next), end);
	node->left = ft_abs(&tmp, next);
	return (node);
}

t_tree	*ft_pipes(t_list **parsresult, t_list *end)
{
	t_list	*tmp;
	t_list	*next;
	t_tree	*node;

	node = NULL;
	tmp = (*parsresult);
	next = ft_lastpipe(*parsresult, end);
	node = ft_malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	node->type = next->TYPE;
	node->right = ft_abs(&(next->next), end);
	node->left = ft_abs(&tmp, next);
	return (node);
}

int	redirectionsnormtree(t_list *next, t_tree *node, t_list *end, t_list **parsresult)
{
	if (!node)
		return (1);
	if (next->TYPE == RDHER)
	{
		node->elements = ft_malloc(sizeof(t_list *) * 2);
		if (!node->elements)
			return (1);
		node->elements[0] = next;
		node->elements[1] = NULL;
	}
	node->redirections = noderedirections(*parsresult, end);
	if (!node->redirections)
		return (1);
	return (0);
}

int	ft_protrctionone(t_tree *node)
{
	if (!node->elements)
		return (1);
	return (0);
}

int	ft_protrctiontwo(t_tree *node)
{
	if (!node->redirections)
		return (1);
	return (0);
}
