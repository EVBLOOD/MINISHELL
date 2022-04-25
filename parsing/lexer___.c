/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer___.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 00:56:44 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/25 00:57:41 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	ft_isdigitvariable(char **line, t_list **head)
{
	t_list	*node;
	if (ft_isdigit(**line) || **line == '?')
	{
		(*line)++;
		node = ft_setword(*line - 2, 2);
		if (!node)
			return (1);
		node->TYPE = VARIABLE;
		ft_lstadd_back(head, node);
		return (1);
	}
	return (0);
}

void	ft_variable(char **line, t_list **head)
{
	t_list	*node;
	int		i;

	i = 1;
	if (**line && ft_strchr(**line, "$"))
	{
		(*line)++;
		if (ft_isdigitvariable(line, head))
			return ;
		while (**line && !ft_strchr(**line, "&|><*()\"\'$")
			&& !ft_varvalidating(**line) && ft_isspace(**line))
		{
			(*line)++;
			i++;
		}
		node = ft_setword(*line - i, i);
		if (!node)
			return ;
		node->TYPE = VARIABLE;
		if (i == 1)
			node->TYPE = WORD;
		ft_lstadd_back(head, node);
	}
}

void	ft_snglonce(char **line, t_list **head)
{
	t_list	*node;
	int		x;

	x = 0;
	if (**line && ft_strchr(**line, "*()\"\'"))
	{
		node = ft_setword(*line, 1);
		if (!node)
			return ;
		node->TYPE = check_type_two(**line);
		if (node->TYPE == SQ)
			x = ft_qouting(line, &node, 39);
		else if (node->TYPE == DQ)
			x = ft_qouting(line, &node, 34);
		(*line)++;
		if (x)
			return ;
		ft_lstadd_back(head, node);
	}
}

void	ft_dealingwithspaces(char **line, int *spaces, t_list **head)
{
	t_list	*node;

	if (*spaces > 0)
	{
		node = ft_malloc(sizeof(t_list));
		if (!node)
			return ;
		node->nb = *spaces;
		node->TYPE = SPACES;
		node->sqp = 1;
		node->next = NULL;
		ft_lstadd_back(head, node);
		*spaces = 0;
	}
}

t_list	*ft_lexicalanalysis(char *line)
{
	t_list	*head;
	t_list	*node;
	int		i;
	int		spaces;

	head = NULL;
	spaces = 0;
	ft_whiterun(&line);
	i = 0;
	while (*line)
	{
		spaces = ft_whiterun(&line);
		ft_dealingwithspaces(&line, &spaces, &head);
		ft_navigatewords(&line, &i);
		ft_addwords(&line, &i, &head);
		spaces = ft_whiterun(&line);
		ft_dealingwithspaces(&line, &spaces, &head);
		ft_navigatedoubles(&line, &i);
		ft_addsnglordbl(&line, &i, &head);
		spaces = ft_whiterun(&line);
		ft_dealingwithspaces(&line, &spaces, &head);
		ft_snglonce(&line, &head);
		spaces = ft_whiterun(&line);
		ft_dealingwithspaces(&line, &spaces, &head);
		ft_variable(&line, &head);
	}
	return (head);
}