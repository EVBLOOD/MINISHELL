/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstract_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:19:35 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/25 01:20:51 by sakllam          ###   ########.fr       */
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
	while (parsresult != end && (parsresult->TYPE == SPACES
		|| parsresult->TYPE == WORD || parsresult->TYPE == VARIABLE
		|| parsresult->TYPE == WILD || parsresult->TYPE == DQ
		|| parsresult->TYPE == SQ))
	{
		if (parsresult->sqp)
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
		if ((nav->TYPE == RDAPP || nav->TYPE == RDHER || nav->TYPE == RDIN
			|| nav->TYPE == RDOUT) && !count)
			node = nav;
		nav = nav->next;
	}
	return (node);
}