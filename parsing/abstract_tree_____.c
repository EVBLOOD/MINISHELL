/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstract_tree_____.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:28:13 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/26 00:25:54 by foulare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

t_tree	*ft_abs(t_list **parsresult, t_list *end)
{
	t_tree	*node;
	int		i;

	i = -1;
	node = NULL;
	if (!(*parsresult) || (*parsresult) == end)
		return (NULL);
	if (ft_lastop(*parsresult, end))
		node = ft_operatorsnode(parsresult, end);
	else if (ft_lastpipe(*parsresult, end))
		node = ft_pipes(parsresult, end);
	else if (ft_firstredr(*parsresult, end))
		node = redirections(parsresult, end);
	else
		node = wordsandstuf(parsresult, end);
	return (node);
}
