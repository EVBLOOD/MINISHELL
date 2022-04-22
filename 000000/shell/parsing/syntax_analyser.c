/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 00:00:36 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/20 10:26:52 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_checksforqoutes(char *str, int qoute)
{
	int	i;

	i = ft_strlen(str);
	if (str[i - 1] == qoute && i > 1)
		return (1);
	return (0);
}

int	ft_getnext(t_list *corrent)
{
	if (corrent->next)
	{
		if (corrent->next->TYPE != SPACES)
			return (corrent->next->TYPE);
		else
		{
			if (corrent->next->next)
				return (corrent->next->next->TYPE);
		}
	}
	return (-1);
}

void	ft_errormsg(char *str)
{
	write (2, "bash: syntax error near unexpected token ", 41);
	write (2, str, ft_strlen(str));
	write (2, "\n", 1);
}

int	ft_firstcheck(t_list *lst, int *start)
{
	if (*start)
	{
		if (lst->TYPE == PRTCLOSE || lst->TYPE == OR
			|| lst->TYPE == AND || lst->TYPE == PIPE)
		{
			ft_errormsg(lst->splited);
			return (1);
		}
		*start = 0;
	}
	return (0);
}

int	near_pipe_and_or(t_list *lst)
{
	int	x;

	if ((lst->TYPE == PIPE || lst->TYPE == AND
		|| lst->TYPE == OR))
	{
		x = ft_getnext(lst);
		if (x == -1 || x == PIPE || x == AND
			|| x == OR || x == PRTCLOSE)
		{
			ft_errormsg(lst->splited);
			return (1);
		}
	}
	return (0);
}

int	near_openparnth(t_list *lst, int *prth)
{
	int	x;

	if (lst->TYPE == PRTOPEN)
	{
		(*prth)++;
		x = ft_getnext(lst);
		if (x == -1 || x == PIPE || x == AND
			|| x == OR || x == PRTCLOSE)
		{
			ft_errormsg(lst->splited);
			return (1);
		}
	}
	return (0);
}

int	near_closedparnth(t_list *lst, int *prth)
{
	int	x;

	if (lst->TYPE == PRTCLOSE)
	{
		(*prth)--;
		x = ft_getnext(lst);
		if (x == WORD || x == PRTOPEN || x == SQ
			|| x == DQ || x == WILD || x  == VARIABLE)
			return (1);
	}
	return (0);
}

int	ft_wildcard(t_list *lst)
{
	int	x;

	if (lst->TYPE == WILD)
	{
		x = ft_getnext(lst);
		if (x == PRTOPEN)
		{
			ft_errormsg(lst->splited);
			return (1);
		}
	}
	return (0);
}

int	ft_redirections(t_list *lst)
{
	int	x;
	int	okey;

	x = ft_getnext(lst);
	okey = 0;
	if (lst->TYPE == RDIN)
		if (x == -1 || (x != WILD && x != WORD && x != SQ
			&& x != DQ))
			okey = 1;
	if (lst->TYPE == RDOUT)
		if (x == -1 || (x != WILD && x != WORD && x != SQ
			&& x != DQ))
			okey = 1;
	if (lst->TYPE == RDHER)
	{
		if (x == -1 || (x != WILD && x != WORD && x != SQ
			&& x != DQ))
			okey = 1;
		else
			ft_herdoccreating(&lst);
	}
	if (lst->TYPE == RDAPP)
		if (x == -1 || (x != WILD && x != WORD && x != SQ
			&& x != DQ))
			okey = 1;
	if (okey)
	{
		ft_errormsg(lst->splited);
		return (1);
	}
	return (0);
}

int	ft_quotes(t_list *lst)
{
	int	x;
	int	okey;

	x = ft_getnext(lst);
	okey = 0;
	if (lst->TYPE == DQ)
	{
		if (!ft_checksforqoutes(lst->splited, 34))
			okey = 1;
		if (x == PRTOPEN)
			okey = 2;
	}
	if (lst->TYPE == SQ)
	{
		if (!ft_checksforqoutes(lst->splited, 39) || x == PRTOPEN)
			okey = 1;
		if (x == PRTOPEN)
			okey = 2;
	}
	if (okey)
	{
		if (okey == 1)
			write(2, "bash: no closing quotes\n", 24);
		else
			ft_errormsg(lst->splited);
		return (1);
	}
	return (0);
}

int	ft_word(t_list *lst)
{
	int	x;

	if (lst->TYPE == WORD)
	{
		x = ft_getnext(lst);
		if (x == PRTOPEN)
		{
			ft_errormsg(lst->splited);
			return (1);
		}
	}
	return (0);
}

int	ft_syntaxanalysis(t_list *parsresult)
{
	int	prth;
	int	start;
	t_list	*tmp;

	start = 1;
	prth = 0;
	while (parsresult)
	{
		if (ft_word(parsresult))
			return (1);
		if (ft_firstcheck(parsresult, &start))
			return (1);
		if (near_pipe_and_or(parsresult))
			return (1);
		if (near_openparnth(parsresult, &prth))
			return (1);
		if (near_closedparnth(parsresult, &prth))
			return (1);
		if (ft_wildcard(parsresult))
			return (1);
		if (ft_redirections(parsresult))
			return (1);
		if (ft_quotes(parsresult))
			return (1);
		parsresult = parsresult->next;
	}
	if (prth)
	{
		write(2, "bash: no closing parentheses\n", 29);
		return (1);
	}
	return (0);
}