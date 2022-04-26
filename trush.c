/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trush.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 20:09:15 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/26 04:10:25 by foulare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

t_trush	*ft_trushlast(t_trush *lst)
{
	t_trush	*temp;

	if (!lst)
		return (NULL);
	while (lst)
	{
		temp = lst;
		lst = lst->next;
	}
	return (temp);
}

void	ft_trushadd_front(t_trush **lst, t_trush *new)
{
	new->next = *lst;
	*lst = new;
}

void	ft_trushadd_back(t_trush **lst, t_trush *new)
{
	t_trush	*ptr;

	if (!*lst)
		ft_trushadd_front(lst, new);
	else
	{
		ptr = ft_trushlast((*lst));
		ptr->next = new;
	}
}

int	ft_trushlengh(t_trush *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	ft_addtotrush(void *ptr, t_trush **head, int nb)
{
	t_trush	*node;

	node = malloc (sizeof(t_trush));
	node->element = ptr;
	node->dmn = nb;
	node->next = NULL;
	ft_trushadd_back(head, node);
}
