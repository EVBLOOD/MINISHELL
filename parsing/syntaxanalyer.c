/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxanalyer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:27:10 by sakllam           #+#    #+#             */
/*   Updated: 2022/03/04 22:34:13 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_syntaxanalysis(t_list *parsresult)
{
	int	dq;
	int	prth;
	int	sq;
	int	start;
	t_list	*tmp;

	start = 1;
	prth = 0;
	dq = 0;
	sq = 0;
	while (parsresult)
	{
		if (start)
		{
			if (parsresult->TYPE == PRTCLOSE || parsresult->TYPE == OR
				|| parsresult->TYPE == AND || parsresult->TYPE == PIPE)
				return (1);
			start = 0;
		}
		if ((!(dq % 2) && !(sq % 2)) && (parsresult->TYPE == PIPE || parsresult->TYPE == AND
			|| parsresult->TYPE == OR))
		{
			if (!parsresult->next || parsresult->next->TYPE == PIPE 
				|| parsresult->next->TYPE == AND || parsresult->next->TYPE == OR
				|| parsresult->next->TYPE == PRTCLOSE)
				return (1);
		}
		if ((!(dq % 2) && !(sq % 2)) && parsresult->TYPE == PRTOPEN)
		{
			prth++;
			if (!parsresult->next || parsresult->next->TYPE == PIPE 
				|| parsresult->next->TYPE == AND || parsresult->next->TYPE == OR
				|| parsresult->next->TYPE == PRTCLOSE)
				return (1);
		}
		if ((!(dq % 2) && !(sq % 2)) && parsresult->TYPE == PRTCLOSE)
		{
			prth--;
			if (parsresult->next && (parsresult->next->TYPE == WORD 
				|| parsresult->next->TYPE == PRTOPEN || parsresult->next->TYPE == SQ 
				|| parsresult->next->TYPE == DQ  || parsresult->next->TYPE == WILD
				|| parsresult->next->TYPE  == VARIABLE))
				return (1);
		}
		if ((!(dq % 2) && !(sq % 2)) && parsresult->TYPE == VARIABLE)
		{
			if (ft_strlen(parsresult->splited) == 1)
				return (1);
		}
		if ((!(dq % 2) && !(sq % 2)) && parsresult->TYPE == WILD)
		{
			if (parsresult->next && parsresult->next->TYPE == PRTOPEN)
				return (1);
		}
		if ((!(dq % 2) && !(sq % 2)) && parsresult->TYPE == RDIN)
		{
			if (!parsresult->next || parsresult->next->TYPE == PIPE 
				|| parsresult->next->TYPE == AND || parsresult->next->TYPE == OR
				|| parsresult->next->TYPE == PRTCLOSE || parsresult->next->TYPE == PRTOPEN)
				return (1);
		}
		if ((!(dq % 2) && !(sq % 2)) && parsresult->TYPE == RDOUT)
		{
			if (!parsresult->next || parsresult->next->TYPE == PIPE 
				|| parsresult->next->TYPE == AND || parsresult->next->TYPE == OR
				|| parsresult->next->TYPE == PRTCLOSE || parsresult->next->TYPE == PRTOPEN)
				return (1);
		}
		if ((!(dq % 2) && !(sq % 2)) && parsresult->TYPE == RDHER)
		{
			if (!parsresult->next || parsresult->next->TYPE == PIPE 
				|| parsresult->next->TYPE == AND || parsresult->next->TYPE == OR
				|| parsresult->next->TYPE == PRTCLOSE || parsresult->next->TYPE == PRTOPEN)
				return (1);
		}
		if ((!(dq % 2) && !(sq % 2)) && parsresult->TYPE == RDAPP)
		{
			if (!parsresult->next || parsresult->next->TYPE == PIPE 
				|| parsresult->next->TYPE == AND || parsresult->next->TYPE == OR
				|| parsresult->next->TYPE == PRTCLOSE || parsresult->next->TYPE == PRTOPEN)
				return (1);
		}
		if (!(sq % 2) && parsresult->TYPE == DQ)
			dq++;
		if (!(dq % 2) && parsresult->TYPE == SQ)
			sq++;
		 if ((parsresult->TYPE != SQ && parsresult->TYPE != DQ) && ((dq % 2) || (sq % 2)))
		 	parsresult->TYPE = WORD;
		parsresult = parsresult->next;
	}
	if ((dq % 2) || (sq % 2) || prth)
		return (1);
	return (0);
}