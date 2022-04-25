/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 23:58:40 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/23 15:27:26 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	ft_isspace(char x)
{
	if (x == '\t' || x ==  '\n' || x == '\v'
		|| x == '\f' || x ==   '\r' || x == ' ')
		return (0);
	return (1);
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

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int check_type_two(char c)
{
	if (c == ')')
		return (PRTCLOSE);
	else if (c == '(')
		return (PRTOPEN);
	else if (c == '\'')
		return (SQ);
	else if (c == '\"')
		return (DQ);
	else if (c == '*')
		return (WILD);
	else if (c == '$')
		return (VARIABLE);
	return (-1);
}

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

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	counter = 0;
	node->splited = malloc(sizeof(char) * (i + 1));
	node->sqp = 1;
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
		node->TYPE = WORD;
		node->next = NULL;
		ft_lstadd_back(head, node);
		*i = 0;
	}
}

void	ft_navigatewords(char **line, int *i)
{
	while (**line && !ft_strchr(**line, "&|><*()\"\'$") && ft_isspace(**line))
	{
		(*i)++;
		(*line)++;
	}
}

void	ft_notavar(char **line, t_list **head)
{
	int	x;

	x = 0;
	ft_whiterun(line);
	while (**line && !ft_strchr(**line, "&|><*()\"\'") && ft_isspace(**line))
	{
		x++;
		(*line)++;
	}
	ft_addwords(line, &x, head);
}

void	ft_addsnglordbl(char **line, int *i, t_list **head)
{
	t_list	*node;

	if (*i > 0)
	{
		node = ft_setword(*line - *i, *i);
		node->TYPE = check_type_one(*(*line - 1), *i);
		node->next = NULL;
		ft_lstadd_back(head, node);
		if (node->TYPE == RDHER || node->TYPE == RDIN || node->TYPE == RDOUT || node->TYPE == RDAPP)
			ft_notavar(line, head);
		*i = 0;
	}
}

int	ft_qouting(char **line, t_list **node, char qoute)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	free((*node)->splited); // NB: I can't get it
	while ((*line)[i] && (*line)[i] != qoute)
		i++;
	(*node)->splited = malloc(i + 2);
	if (!(*node)->splited)
		return (0);
	if (!(*node)->splited)
		return (2);
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
	if (**line != qoute)
		return (1);
	return (0);
}

void	ft_navigatedoubles(char **line, int *i)
{
	while (**line && ft_strchr(**line, "&|><") && *i < 2)
	{
		(*i)++;
		(*line)++;
		if (*(*line - 1) != **line)
			break;
	}
}

void	ft_variable(char **line, t_list **head)
{
	t_list	*node;
	int		i;

	i = 1;
	if (**line && ft_strchr(**line, "$"))
	{
		(*line)++;
		if (ft_isdigit(**line))
		{
			(*line)++;
			node = ft_setword(*line - 2, 2);
			node->TYPE = VARIABLE;
			ft_lstadd_back(head, node);
			return ;
		}
		while (**line && !ft_strchr(**line, "&|><*()\"\'$") && !ft_varvalidating(**line) && ft_isspace(**line))
		{
			(*line)++;
			i++;
		}
		node = ft_setword(*line - i, i);
		node->TYPE = VARIABLE;
		if (i == 1)
			node->TYPE = WORD;
		ft_lstadd_back(head, node);
	}
}

void	ft_snglonce(char **line, t_list **head)
{
	t_list	*node;

	if (**line && ft_strchr(**line, "*()\"\'"))
	{
		node = ft_setword(*line, 1);
		node->TYPE = check_type_two(**line);
		if (node->TYPE == SQ)
			ft_qouting(line, &node, 39);
		else if (node->TYPE == DQ)
			ft_qouting(line, &node, 34);
		ft_lstadd_back(head, node);
		(*line)++;
	}
}

void	ft_dealingwithspaces(char **line, int *spaces, t_list **head)
{
	t_list	*node;

	if (*spaces > 0)
	{
		node = malloc(sizeof(t_list));
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