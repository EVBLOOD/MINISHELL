/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstarct_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 23:59:33 by sakllam           #+#    #+#             */
/*   Updated: 2022/03/26 16:59:43 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

t_list	*ft_lastop(t_list *nav, t_list *end)
{
	t_list	*node;
	int  count;

	count = 0;
	node = NULL;
	while (nav != end)
	{
		if ((nav)->TYPE == PRTOPEN)
			count++;
		if ((nav)->TYPE == PRTCLOSE)
			count--;
		if ((nav->TYPE == AND || nav->TYPE == OR) && !count)
			node = nav;
		nav = nav->next;
	}
	return (node);
}

t_list	*ft_lastpipe(t_list *nav, t_list *end)
{
	t_list	*node;
	int  count;

	count = 0;
	node = NULL;
	while (nav != end)
	{
		if ((nav)->TYPE == PRTOPEN)
			count++;
		if ((nav)->TYPE == PRTCLOSE)
			count--;
		if (nav->TYPE == PIPE && !count)
			node = nav;
		nav = nav->next;
	}
	return (node);
}

int	ft_size(t_list *parsresult, t_list *end)
{
	int	i;
	t_list *tmp;

	i = 0;
	while (parsresult != end && (parsresult->TYPE == SPACES || parsresult->TYPE == WORD || parsresult->TYPE == VARIABLE
				|| parsresult->TYPE == WILD || parsresult->TYPE == DQ || parsresult->TYPE == SQ))
	{
		i++;
		parsresult = parsresult->next;
	}
	return (i + 1);
}


t_list	*ft_lastredr(t_list *nav, t_list *end)
{
	t_list	*node;
	int  count;

	count = 0;
	node = NULL;
	while (nav != end)
	{
		if ((nav)->TYPE == PRTOPEN)
			count++;
		if ((nav)->TYPE == PRTCLOSE)
			count--;
		if ((nav->TYPE == RDAPP || nav->TYPE == RDHER || nav->TYPE == RDIN || nav->TYPE == RDOUT) && !count)
			node = nav;
		nav = nav->next;
	}
	return (node);
}


t_tree	*ft_abs(t_list **parsresult, t_list *end)
{
	t_tree	*node;
	t_list	*next;
	t_list	*tmp;
	int		i;

	i = -1;
	if ((*parsresult) == end)
		return (NULL);
	if (ft_lastop(*parsresult, end))
	{
		tmp = (*parsresult);
		next = ft_lastop(*parsresult, end);
		node = malloc(sizeof(t_tree));
		node->type =  next->TYPE;
		node->right = ft_abs(&(next->next), end);
		node->left = ft_abs(&tmp, next);
	}
	else if (ft_lastpipe(*parsresult, end))
	{
		tmp = (*parsresult);
		next = ft_lastpipe(*parsresult, end);
		node = malloc(sizeof(t_tree));
		node->type =  next->TYPE;
		node->right = ft_abs(&(next->next), end);
		node->left = ft_abs(&tmp, next);
	}
	else if (ft_lastredr(*parsresult, end))
	{
		tmp = (*parsresult);
		next = ft_lastredr(*parsresult, end);
		node = malloc(sizeof(t_tree));
		node->type =  next->TYPE;
		node->left = ft_abs(&(next->next), end);
		node->right = ft_abs(&tmp, next);
	}
	else
	{
		if ((*parsresult)->TYPE == PRTCLOSE || (*parsresult)->TYPE == PRTOPEN)
			node = ft_abs(&((*parsresult)->next), end);
		else
		{
			node = malloc(sizeof(t_tree));
			node->elements = malloc(ft_size(*parsresult, end) * sizeof(t_list *));
			node->type = LIST;
			while (*parsresult != end && ((*parsresult)->TYPE == SPACES || (*parsresult)->TYPE == WORD || (*parsresult)->TYPE == VARIABLE
				|| (*parsresult)->TYPE == WILD || (*parsresult)->TYPE == DQ || (*parsresult)->TYPE == SQ))
			{
				node->elements[++i] = *parsresult;
				(*parsresult) = (*parsresult)->next;
			}
			node->elements[++i] = NULL;
			node->left = NULL;
			node->right = NULL;
		}
	}
	return (node);
}