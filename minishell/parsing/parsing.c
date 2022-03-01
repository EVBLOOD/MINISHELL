/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:12:27 by sakllam           #+#    #+#             */
/*   Updated: 2022/02/22 14:12:27 by sakllam          ###   ########.fr       */
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

int check_char(char c, char *adr)
{
	if (c == adr[1])
		return (2);
	return (1);
	return (0);
}

int check_type_one(char c, int i)
{
	if (c == '|' && i == 1)
		return (PIPE);
	else if (c == '|' && i == 2)
		return (OR);
	if (c == '&' && i == 1)
		return (-1);
	else if (c == '&' && i == 2)
		return (AND);
	if (c == '<' && i == 1)
		return (RDIN);
	else if (c == '<' && i == 2)
		return (RDHER);
	if (c == '>' && i == 1)
		return (RDOUT);
	else if (c == '>' && i == 2)
		return (RDAPP);
	return (-1);
}

int check_type_two(char c, int nsquote, int ndquote)
{
	if (c == ')')
		return (PRTCLOSE);
	if (c == '(')
		return (PRTOPEN);
	if (c == '\'' && !(nsquote % 2))
		return (SQCLOSE);
	else if (c == '\'' && (nsquote % 2))
		return (SQOPEN);
	if (c == '\"' && !(ndquote % 2))
		return (DQCLOSE);
	else if (c == '\"' && (ndquote % 2))
		return (DQOPEN);
	if (c == '*')
		return (WILD);
	if (c == '$')
		return (VARIABLE);
	return (-1);
}


// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	int		i;
// 	char	*p;

// 	i = 0;
// 	if (!s)
// 		return (NULL);
// 	if (ft_strlen(s + start) < len)
// 		p = (char *) malloc((ft_strlen(s + start) + 1) * sizeof(char));
// 	else
// 		p = (char *) malloc(((int) len + 1) * sizeof(char));
// 	if (!p)
// 		return (NULL);
// 	while (i < (int) len && s[i + start] && !(start >= ft_strlen(s)))
// 	{
// 		p[i] = s[i + start];
// 		i++;
// 	}
// 	p[i] = '\0';
// 	return (p);
// }

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

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	counter = 0;
	node->splited = malloc(sizeof(char) * i);
	while (i > counter)
	{
		node->splited[counter] = line[counter];
		counter++;
	}
	node->splited[counter] = '\0';
	node->TYPE = WORD;
	node->next = NULL;
	return (node);
}

t_list	*ft_parsing(char *line)
{
	int	i;
	int	letr_count;
	int		nsquote;
	int		ndquote;
	t_list	*head;
	t_list	*node;

	letr_count = 0;
	ndquote = 0;
	nsquote = 0;
	i = 0;
	head = NULL;
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	while (*line)
	{
		i = 0;
		while (*line && (*line == ' ' || *line == '\t'))
			line++;
		while (*line && !ft_strchr(*line, "&|><*()\"\'$"))
		{
			i++;
			line++;
			if (*line == ' ' && !(nsquote % 2) && !(ndquote % 2))
				break;
		}
		if (i > 0)
		{
			node = ft_setword(line - i, i);
			node->TYPE = WORD;
			ft_lstadd_back(&head, node);
			i = 0;
		}
		while (*line && (*line == ' ' || *line == '\t'))
			line++;
		while (*line && ft_strchr(*line, "&|><") && i < 2)
		{
			i++;
			line++;
			if (*(line - 1) != *(line))
				break;
		}
		if (i > 0)
		{
			node = ft_setword(line - i, i);
			node->TYPE = check_type_one(*(line - 1), i);
			ft_lstadd_back(&head, node);
			i = 0;
		}
		while (*line && (*line == ' ' || *line == '\t'))
			line++;
		if (*line && ft_strchr(*line, "*()\"\'$"))
		{
			if (*line == '\'')
				nsquote++;
			if (*line == '\"')
				ndquote++;
			node = ft_setword(line, 1);
			node->TYPE = check_type_two(*line, nsquote, ndquote);
			ft_lstadd_back(&head, node);
			line++;
			
		}
	}
	while (head)
	{
		printf("%d : %s\n", head->TYPE, head->splited);
		head = head->next;
	}
	return (head);
}