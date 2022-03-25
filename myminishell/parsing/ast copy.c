// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ast.c                                              :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/03/04 15:38:29 by sakllam           #+#    #+#             */
// /*   Updated: 2022/03/09 10:00:37 by sakllam          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../minishell.h"

// t_list	*ft_lastop(t_list *nav, t_list *end)
// {
// 	t_list	*node;
// 	int  count;

// 	count = 0;
// 	node = NULL;
// 	while (nav != end)
// 	{
// 		if ((nav)->TYPE == PRTOPEN)
// 			count++;
// 		if ((nav)->TYPE == PRTCLOSE)
// 			count--;
// 		if ((nav->TYPE == AND || nav->TYPE == OR) && !count)
// 			node = nav;
// 		nav = nav->next;
// 	}
// 	return (node);
// }

// t_list	*ft_lastpipe(t_list *nav, t_list *end)
// {
// 	t_list	*node;
// 	int  count;

// 	count = 0;
// 	node = NULL;
// 	while (nav != end)
// 	{
// 		if ((nav)->TYPE == PRTOPEN)
// 			count++;
// 		if ((nav)->TYPE == PRTCLOSE)
// 			count--;
// 		if (nav->TYPE == PIPE && !count)
// 			node = nav;
// 		nav = nav->next;
// 	}
// 	return (node);
// }

// int	ft_size(t_list *parsresult, t_list *end)
// {
// 	int	i;
// 	t_list *tmp;

// 	i = 0;
// 	while (parsresult != end && parsresult->TYPE == WORD)
// 	{
// 		i++;
// 		parsresult = parsresult->next;
// 	}
// 	return (i + 1);
// }


// t_list	*ft_lastredr(t_list *nav, t_list *end)
// {
// 	t_list	*node;
// 	int  count;

// 	count = 0;
// 	node = NULL;
// 	while (nav != end)
// 	{
// 		if ((nav)->TYPE == PRTOPEN)
// 			count++;
// 		if ((nav)->TYPE == PRTCLOSE)
// 			count--;
// 		if ((nav->TYPE == RDAPP || nav->TYPE == RDHER || nav->TYPE == RDIN || nav->TYPE == RDOUT) && !count)
// 			node = nav;
// 		nav = nav->next;
// 	}
// 	return (node);
// }

// t_tree	*ft_abs(t_list **parsresult, t_list *end)
// {
// 	t_tree	*node;
// 	t_list	*next;
// 	t_list	*tmp;
// 	int		i;

// 	i = -1;
// 	if ((*parsresult) == end)
// 		return (NULL);
// 	if (ft_lastop(*parsresult, end))
// 	{

// 		tmp = (*parsresult);
// 		next = ft_lastop(*parsresult, end);
// 	//	printf("and or: %d\n", next->TYPE);
// 		node = malloc(sizeof(t_tree));
// 		node->type =  next->TYPE;
// 		node->right = ft_abs(&(next->next), end);
// 		node->left = ft_abs(&tmp, next);
// 	}
// 	else if (ft_lastpipe(*parsresult, end))
// 	{
// 		tmp = (*parsresult);
// 		next = ft_lastpipe(*parsresult, end);
// 	//	printf("pipe: %d\n", next->TYPE);
// 		node = malloc(sizeof(t_tree));
// 		node->type =  next->TYPE;
// 		node->right = ft_abs(&(next->next), end);
// 		node->left = ft_abs(&tmp, next);
// 	}
// 	else if (ft_lastredr(*parsresult, end))
// 	{
// 		tmp = (*parsresult);
// 		next = ft_lastredr(*parsresult, end);
// 	//	printf("red: %d\n", next->TYPE);
// 		node = malloc(sizeof(t_tree));
// 		node->type =  next->TYPE;
// 		node->right = ft_abs(&(next->next), end);
// 		node->left = ft_abs(&tmp, next);
// 	}
// 	else
// 	{
// 		if ((*parsresult)->TYPE == PRTCLOSE || (*parsresult)->TYPE == PRTOPEN)
// 			node = ft_abs(&((*parsresult)->next), end);
// 		else
// 		{
// 			node = malloc(sizeof(t_tree));
// 			node->element = malloc(ft_size(*parsresult, end) * sizeof(char *));
// 			node->type = (*parsresult)->TYPE;
// 			while ((*parsresult) != end && ((*parsresult)->TYPE == WORD || (*parsresult)->TYPE == VARIABLE
// 				|| (*parsresult)->TYPE == WILD || (*parsresult)->TYPE == DQ || (*parsresult)->TYPE == SQ))
// 			{
// 				node->element[++i] = (*parsresult)->splited;
// 				(*parsresult) = (*parsresult)->next;
// 			}
// 			node->element[++i] = NULL;
// 			node->left = NULL;
// 			node->right = NULL;
// 		}
// 		// next = (*parsresult)->next;
// 		// node = malloc(sizeof(t_tree));
// 		// node->right = ft_abs(&next, NULL);
// 		// node->left = ft_abs(&tmp, NULL);
// 	}
// 	// if (((*parsresult)->TYPE == OR || (*parsresult)->TYPE == AND) && !ft_prioriity(&(*parsresult), pcount))
// 	// 	{
// 	// 		printf("and or: %d\n", (*parsresult)->TYPE);
// 	// 		next = (*parsresult)->next;
// 	// 		node = malloc(sizeof(t_tree));
// 	// 		node->type = (*parsresult)->TYPE;
// 	// 		node->left = ft_abs(&tmp, (*parsresult));
// 	// 		node->right = ft_abs(&next, NULL);		
// 	// 	}
// 	return (node);
// }



// // t_tree	*ft_abs(t_list **parsresult, t_list *end)
// // {
// // 	int		pcount;
// // 	t_tree	*head;
// // 	t_tree	*node;
// // 	t_list	*next;
// // 	t_list	*tmp;
// // 	t_list	*tmpalpha;
// // 	int		i;

// // 	i = 0;
// // 	head = NULL;
// // 	pcount = 0;
// // 	tmp = (*parsresult);
// // 	while ((*parsresult) != end)
// // 	{
// // 		printf ("ok\n");
// // 		if ((*parsresult)->TYPE == PRTOPEN)
// // 			pcount++;
// // 		if ((*parsresult)->TYPE == PRTCLOSE)
// // 			pcount--;
// // 		if (((*parsresult)->TYPE == OR || (*parsresult)->TYPE == AND) && !ft_prioriity(&(*parsresult), pcount))
// // 		{
// // 			printf("and or: %d\n", (*parsresult)->TYPE);
// // 			next = (*parsresult)->next;
// // 			node = malloc(sizeof(t_tree));
// // 			node->type = (*parsresult)->TYPE;
// // 			node->left = ft_abs(&tmp, (*parsresult));
		
// // 			node->right = ft_abs(&next, NULL);
						
// // 				break;
// // 		}
// // 		if ((*parsresult)->TYPE == PIPE && check_next(*parsresult, 0) && !ft_prioriity(&(*parsresult), pcount))
// // 		{
// // 			printf("pipe: %d\n", (*parsresult)->TYPE);
// // 			next = (*parsresult)->next;
// // 			node = malloc(sizeof(t_tree));
// // 			node->type = (*parsresult)->TYPE;
// // 			node->left = ft_abs(&tmp, (*parsresult));
// // 			node->right = ft_abs(&next, NULL);
	
// // 				break;
// // 		}
// // 		if (((*parsresult)->TYPE == RDIN || (*parsresult)->TYPE == RDOUT 
// // 			|| (*parsresult)->TYPE == RDHER || (*parsresult)->TYPE == RDAPP) 
// // 			&& (check_next(*parsresult, 1) && !ft_prioriity(&(*parsresult), pcount)))
// // 		{
// // 			printf("redir %d\n", (*parsresult)->TYPE);
// // 			next = (*parsresult)->next;
// // 			node = malloc(sizeof(t_tree));
// // 			node->type = (*parsresult)->TYPE;
// // 			node->left = ft_abs(&tmp, (*parsresult));
// // 			node->right = ft_abs(&next, NULL);
				
// // 				break;
// // 		}
		
// // 		// if ((*parsresult)->TYPE == WORD && state == 1)
// // 		// {

// // 		// }
// // 		(*parsresult) = (*parsresult)->next;
// // 	}
// // 	printf("no\n");
// // 	return (head);
// // }

// // t_tree	*ft_abs(t_list *parsresult, t_list *end)
// // {
// // 	int		pcount;
// // 	t_tree	*node;
// // 	t_list	*next;
// // 	t_list	*tmp;

// // 	pcount = 0;
// // 	tmp = parsresult;
// // 	if (parsresult == end)
// // 		return (NULL);
// // 	if (parsresult->TYPE == PRTOPEN)
// // 		pcount++;
// // 	if (parsresult->TYPE == PRTCLOSE)
// // 		pcount--;
// // 	if ((parsresult->TYPE == OR || parsresult->TYPE == AND) && !ft_prioriity(parsresult, pcount))
// // 	{
// // 		printf("and or: %d\n", parsresult->TYPE);
// // 		next = parsresult->next;
// // 		node = malloc(sizeof(t_tree));
// // 		node->type = parsresult->TYPE;
// // 		node->left = ft_abs(tmp, parsresult);
// // 		node->right = ft_abs(next, NULL);
// // 	}
// // 	if (parsresult->TYPE == PIPE && check_next(parsresult, 0) && !ft_prioriity(parsresult, pcount))
// // 	{
// // 		printf("pipe: %d\n", parsresult->TYPE);
// // 		next = parsresult->next;
// // 		node = malloc(sizeof(t_tree));
// // 		node->type = parsresult->TYPE;
// // 		node->right = ft_abs(next, NULL);
// // 		node->left = ft_abs(tmp, parsresult);
// // 	}
// // 	if ((parsresult->TYPE == RDIN || parsresult->TYPE == RDOUT 
// // 		|| parsresult->TYPE == RDHER || parsresult->TYPE == RDAPP) 
// // 		&& (check_next(parsresult, 1) && !ft_prioriity(parsresult, pcount)))
// // 	{
// // 		printf("redir %d\n", parsresult->TYPE);
// // 		next = parsresult->next;
// // 		node = malloc(sizeof(t_tree));
// // 		node->type = parsresult->TYPE;
// // 		node->right = ft_abs(next, NULL);
// // 		node->left = ft_abs(tmp, parsresult);
// // 	}
// // 	if ((parsresult)->TYPE == WORD)
// // 	{
// // 		next = parsresult->next;
// // 		node = malloc(sizeof(t_tree));
// // 		node->right = ft_abs(next, NULL);
// // 		write (1, "klma\n", 5);
// // 		// node->left = ft_abs(&tmp, (*parsresult));
// // 		// node->right = ft_abs(&next, NULL);
// // 	}
// // 	// (*parsresult) = (*parsresult)->next;
// // 	// if ((*parsresult)->TYPE == WORD && state == 1)
// // 	// {
// // 	// }
// // 	// }
// // 	return (node);
// // }