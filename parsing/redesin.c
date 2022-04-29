/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redesin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:11:18 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/28 21:30:20 by sakllam          ###   ########.fr       */
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
	if (lst->type == WORD || lst->type == WILD)
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
	node->type = lst->type;
	node->nb = lst->nb;
	node->next = NULL;
	return (node);
}

int	ft_redirectiononecon(t_list *lst)
{
	return (lst
		&& lst->type != PIPE
		&& lst->type != OR
		&& lst->type != AND
		&& lst->type != PRTOPEN
		&& lst->type != PRTCLOSE);
}

int	ft_isthatared(t_list *lst)
{
	return (lst->type == RDAPP
		|| lst->type == RDHER
		|| lst->type == RDIN
		|| lst->type == RDOUT);
}
