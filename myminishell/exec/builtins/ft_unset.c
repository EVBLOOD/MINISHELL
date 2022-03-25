/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:12:29 by sakllam           #+#    #+#             */
/*   Updated: 2022/03/08 23:27:26 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_unset(t_env **env, char *str)
{
	t_env	*node;
	t_env	*prev;
	t_env	*next;
	t_env	*tmp;

	node = ft_getenv(env, str);
	if (node)
	{
		tmp = *env;
		while (*env)
		{
			if ((*env)->next == node)
			{
				(*env)->next = node->next;
				free(node);
				break;
			}
			*env = (*env)->next;
		}
	}
	return (0);
}