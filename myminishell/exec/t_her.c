/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_her.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 13:09:37 by sakllam           #+#    #+#             */
/*   Updated: 2022/02/28 13:10:23 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_fronther(t_her **lst, t_her *new)
{
	new->next = *lst;
	*lst = new;
}

void	ft_lstadd_backher(t_her **lst, t_her *new)
{
	t_her	*ptr;

	if (!*lst)
		ft_lstadd_fronther(lst, new);
	else
	{
		ptr = ft_lstlasther((*lst));
		ptr->next = new;
	}
}

t_her	*ft_lstlasther(t_her *lst)
{
	t_her	*temp;

	if (!lst)
		return (NULL);
	while (lst)
	{
		temp = lst;
		lst = lst->next;
	}
	return (temp);
}
