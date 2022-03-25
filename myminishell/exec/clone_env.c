/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clone_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 19:36:26 by sakllam           #+#    #+#             */
/*   Updated: 2022/03/09 17:17:09 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_lstadd_frontenv(t_env **lst, t_env *new)
{
	new->next = *lst;
	*lst = new;
}

t_env	*ft_lstlastenv(t_env *lst)
{
	t_env	*temp;

	if (!lst)
		return (NULL);
	while (lst)
	{
		temp = lst;
		lst = lst->next;
	}
	return (temp);
}

void	ft_lstadd_backenv(t_env **lst, t_env *new)
{
	t_env	*ptr;

	if (!*lst)
		ft_lstadd_frontenv(lst, new);
	else
	{
		ptr = ft_lstlastenv((*lst));
		ptr->next = new;
	}
}


char	*ft_strdup(const char *s)
{
	int		i;
	char	*p;

	i = 0;
	p = (char *) malloc(ft_strlen(s) + 1);
	if (!p)
		return (NULL);
	while (s[i])
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

t_env	*ft_newelementenv(char *str)
{
	t_env	*node;
	int		i;

	i = -1;
	node = malloc(sizeof(t_env));
	node->value =ft_strdup(str);
	node->next = NULL;
	return (node);
}

void	ft_lstclearenv(t_env **lst)
{
	t_env	*temp;

	temp = NULL;
	if (!*lst)
		return ;
	while (*lst)
	{
		temp = *lst;
		(*lst) = (*lst)->next;
		free(temp->value);
		free(temp);
	}
}

t_env	*ft_cloneenv(char **env)
{
	int		i;
	t_env	*head;
	t_env	*node;

	i = -1;
	head = NULL;
	while (env[++i])
	{
		node = ft_newelementenv(env[i]);
		if (!node)
		{
			ft_lstclearenv(&head);
			return (NULL);
		}
		ft_lstadd_backenv(&head, node);
	}
	return (head);
}
