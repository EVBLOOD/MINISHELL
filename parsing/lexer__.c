/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer__.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saad <saad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 00:54:47 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/30 18:19:49 by saad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	ft_navigatewords(char **line, int *i)
{
	while (**line && !ft_strchr(**line, "&|><*()\"\'$")
		&& ft_isspace(**line))
	{
		(*i)++;
		(*line)++;
	}
}

void	ft_addsnglordbl(char **line, int *i, t_list **head)
{
	t_list	*node;

	if (*i > 0)
	{
		node = ft_setword(*line - *i, *i);
		if (!node)
			return ;
		node->type = check_type_one(*(*line - 1), *i);
		node->next = NULL;
		ft_lstadd_back(head, node);
		*i = 0;
	}
}

int	ft_qouting(char **line, t_list **node, char qoute)
{
	int	i;

	i = 1;
	while ((*line)[i] && (*line)[i] != qoute)
		i++;
	(*node)->splited = ft_malloc(i + 2);
	if (!(*node)->splited)
		return (1);
	(*node)->splited[0] = qoute;
	(*line)++;
	i = 1;
	while (**line && **line != qoute)
	{
		(*node)->splited[i] = **line;
		(*line)++;
		i++;
	}
	(*node)->splited[i] = **line;
	(*node)->splited[++i] = '\0';
	return (0);
}

void	ft_navigatedoubles(char **line, int *i)
{
	while (**line && ft_strchr(**line, "&|><") && *i < 2)
	{
		(*i)++;
		(*line)++;
		if (*(*line - 1) != **line)
			break ;
	}
}
