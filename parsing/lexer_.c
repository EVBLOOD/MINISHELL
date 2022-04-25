/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 00:52:07 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/25 00:53:28 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	ft_varvalidating(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (0);
	return (1);
}

int	ft_whiterun(char **line)
{
	int	i;

	i = 0;
	while (**line && !ft_isspace(**line))
	{
		(*line)++;
		i++;
	}
	return (i);
}

char	*ft_strchr(int c, char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *) &s[i]);
		i++;
	}
	if ((unsigned char) c == '\0' && s)
		return ((char *) &s[i]);
	return (NULL);
}

t_list	*ft_setword(char *line, int i)
{
	t_list	*node;
	int		counter;

	node = ft_malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	counter = 0;
	node->sqp = 1;
	node->splited = ft_malloc(sizeof(char) * (i + 1));
	if (!node->splited)
		return (NULL);
	while (i > counter)
	{
		node->splited[counter] = line[counter];
		counter++;
	}
	node->splited[counter] = '\0';
	node->next = NULL;
	return (node);
}

void	ft_addwords(char **line, int *i, t_list **head)
{
	t_list	*node;

	if (*i > 0)
	{
		node = ft_setword(*line - *i, *i);
		if (!node)
			return ;
		node->TYPE = WORD;
		node->next = NULL;
		ft_lstadd_back(head, node);
		*i = 0;
	}
}