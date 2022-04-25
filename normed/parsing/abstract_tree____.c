/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstract_tree____.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:25:11 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/25 01:28:15 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

t_tree	*redirections(t_list **parsresult, t_list *end)
{
	t_list	**redtmp;
	t_list	*next;
	t_tree	*node;
	t_list	*tmp;

	tmp = (*parsresult);
	next = ft_firstredr(*parsresult, end);
	node = ft_malloc(sizeof(t_tree));
	if (next->TYPE == RDHER)
	{
		node->elements = ft_malloc(sizeof(t_list *) * 2);
		if (ft_protrctionone(node))
			return (NULL);
		node->elements[0] = next;
		node->elements[1] = NULL;
	}
	node->redirections = noderedirections(*parsresult, end);
	if (ft_protrctiontwo(node))
		return (NULL);
	node->type = next->TYPE;
	redtmp = ft_nextalpha(parsresult, end);
	node->right = ft_abs(&tmp, next);
	node->left = ft_abs(redtmp, end);
	return (node);
}

int	sqpspaces(t_list **parsresult, t_list *end)
{
	while ((*parsresult) && (*parsresult)->TYPE == SPACES)
		(*parsresult) = (*parsresult)->next;
	if (!(*parsresult))
		return (0);
	return (1);
}

int	isitexpandable(int x)
{
	return (x == SPACES
		|| x == WORD || x == VARIABLE
		|| x == WILD || x == DQ
		|| x == SQ);
}

t_tree	*words(t_list **parsresult, t_list *end)
{
	t_tree	*node;
	int		i;

	i = -1;
	node = ft_malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	node->elements = ft_malloc(ft_size(*parsresult, end) * sizeof(t_list *));
	if (!node->elements)
		return (NULL);
	node->type = LIST;
	while (*parsresult != end && isitexpandable((*parsresult)->TYPE))
	{
		if ((*parsresult)->sqp)
			node->elements[++i] = *parsresult;
		(*parsresult) = (*parsresult)->next;
	}
	node->elements[++i] = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_tree	*wordsandstuf(t_list **parsresult, t_list *end)
{
	t_tree	*node;

	node = NULL;
	if (sqpspaces(parsresult, end) == 0)
		return (NULL);
	if ((*parsresult)->TYPE == PRTCLOSE || (*parsresult)->TYPE == PRTOPEN)
		node = ft_abs(&((*parsresult)->next), end);
	else
		node = words(parsresult, end);
	return (node);
}
