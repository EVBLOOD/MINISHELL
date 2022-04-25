/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyser_.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:02:24 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/25 01:04:08 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

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

void	redirectioncond(t_list *lst, int *okey, int x)
{
	if (lst->TYPE == RDIN)
		if (x == -1 || (x != WILD && x != WORD && x != SQ
		&& x != DQ))
			*okey = 1;
	if (lst->TYPE == RDOUT)
		if (x == -1 || (x != WILD && x != WORD && x != SQ
			&& x != DQ))
			*okey = 1;
	if (lst->TYPE == RDHER)
	{
		lst->herdocexp = 0;
		if (x == -1 || (x != WILD && x != WORD && x != SQ
			&& x != DQ))
			*okey = 1;
		else
			ft_herdoccreating(&lst);
	}
	if (lst->TYPE == RDAPP)
		if (x == -1 || (x != WILD && x != WORD && x != SQ
			&& x != DQ))
			*okey = 1;
}
