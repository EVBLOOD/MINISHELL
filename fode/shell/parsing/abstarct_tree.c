/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstarct_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 23:59:33 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/22 01:45:36 by sakllam          ###   ########.fr       */
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
		if ((nav->TYPE == RDAPP || nav->TYPE == RDHER || nav->TYPE == RDIN || nav->TYPE == RDOUT) && !count)
			node = nav;
		nav = nav->next;
	}
	return (node);
}


t_list	*ft_firstredr(t_list *nav, t_list *end)
{
	int  count;

	count = 0;
	while (nav != end)
	{
		if ((nav)->TYPE == PRTOPEN)
			count++;
		if ((nav)->TYPE == PRTCLOSE)
			count--;
		if ((nav->TYPE == RDAPP || nav->TYPE == RDHER || nav->TYPE == RDIN || nav->TYPE == RDOUT) && !count)
			return (nav);
		nav = nav->next;
	}
	return (NULL);
}


t_list	*ft_createredirectionnode(t_list *redirection)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	node->expanded = redirection->expanded;
	node->fd = redirection->fd;
	node->herdocexp = redirection->herdocexp;
	node->nb = redirection->nb;
	node->splited = redirection->splited;
	node->sqp = redirection->sqp;
	node->TYPE = redirection->TYPE;
	node->next = NULL;
	redirection->sqp = 0;
	return (node);
}

t_list	*noderedirections(t_list *list, t_list *end) // you may need to free the cloned
{
	t_list	*redirection;
	t_list	*newlist;
	t_list	*node;

	redirection = ft_firstredr(list, end);
	redirection  = redirection->next;
	newlist = NULL;
	while (redirection != end && redirection->TYPE == SPACES)
		redirection = redirection->next;
	while (redirection != end && redirection->TYPE != SPACES && isredirections(redirection->TYPE) && redirection->TYPE != PRTOPEN)
	{
		puts("isk tcha?");
		node = ft_createredirectionnode(redirection);
		ft_lstadd_back(&newlist, node);
		redirection = redirection->next;
	}
	return (newlist);
}

t_list	**ft_nextalpha(t_list **list, t_list *end)
{
	t_list	**redirection;

	(*redirection) = ft_firstredr(*list, end);
	(*redirection) = (*redirection)->next;
	while ((*redirection) != end && (*redirection)->TYPE == SPACES)
		(*redirection) = (*redirection)->next;
	while ((*redirection) != end && (*redirection)->TYPE != SPACES)
		(*redirection) = (*redirection)->next;
	while ((*redirection) != end && (*redirection)->TYPE == SPACES)
		(*redirection) = (*redirection)->next;
	return (redirection);
}
int	ft_checkforptr(t_list *lst, t_list *end)
{
	while (lst != end)
	{
		if (lst->TYPE == PRTOPEN)
			return (1);
	}
	return (0);
}
t_tree	*ft_abs(t_list **parsresult, t_list *end)
{
	t_tree	*node;
	t_list	**redtmp;
	t_list	*next;
	t_list	*tmp;
	int		i;

	i = -1;
	node = NULL;
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
		node->type = next->TYPE;
		node->right = ft_abs(&(next->next), end);
		node->left = ft_abs(&tmp, next);
	}
	// else if (ft_lastredr(*parsresult, end))
	// {
	// 	tmp = (*parsresult);
	// 	next = ft_lastredr(*parsresult, end);
	// 	node = malloc(sizeof(t_tree));
	// 	if (next->TYPE == RDHER)
	// 	{
	// 		node->elements = malloc(sizeof(t_list *) * 2);
	// 		node->elements[0] = next;
	// 		node->elements[1] = NULL;
	// 	}
	// 	node->type =  next->TYPE;
	// 	node->left = ft_abs(&(next->next), end);
	// 	node->right = ft_abs(&tmp, next);
	// }
	else if (ft_firstredr(*parsresult, end))
	{
		tmp = (*parsresult);
		next = ft_firstredr(*parsresult, end);
		node = malloc(sizeof(t_tree));
		if (next->TYPE == RDHER)
		{
			node->elements = malloc(sizeof(t_list *) * 2);
			node->elements[0] = next;
			node->elements[1] = NULL;
		}
		node->redirections = noderedirections(*parsresult, end);
		node->type = next->TYPE;
		redtmp = ft_nextalpha(parsresult, end);
		node->right = ft_abs(&tmp, next);
		node->left = ft_abs(redtmp, end);
	}
	else
	{
		while ((*parsresult) && (*parsresult)->TYPE == SPACES)
			(*parsresult) = (*parsresult)->next;
		if (!(*parsresult)) return NULL;
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
				if ((*parsresult)->sqp)
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