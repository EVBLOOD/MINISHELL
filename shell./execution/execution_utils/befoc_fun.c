/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   befoc_fun.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 09:01:44 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/01 17:42:54 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

t_befexec	*ft_ofclast(t_befexec *lst)
{
	t_befexec	*temp;

	if (!lst)
		return (NULL);
	while (lst)
	{
		temp = lst;
		lst = lst->next;
	}
	return (temp);
}

void	ft_ofcadd_front(t_befexec **lst, t_befexec *new)
{
	new->next = *lst;
	*lst = new;
}

void	ft_ofcadd_back(t_befexec **lst, t_befexec *new)
{
	t_befexec	*ptr;

	if (!*lst)
		ft_ofcadd_front(lst, new);
	else
	{
		ptr = ft_ofclast((*lst));
		ptr->next = new;
	}
}

int	ft_ofclengh(t_befexec *lst)
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
