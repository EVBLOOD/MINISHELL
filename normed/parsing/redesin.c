/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redesin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:11:18 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/25 01:12:39 by sakllam          ###   ########.fr       */
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

	node = ft_malloc(sizeof(t_list));
	if (!node)
		return (NULL);
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
