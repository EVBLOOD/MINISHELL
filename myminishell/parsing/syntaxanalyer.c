/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxanalyer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:27:10 by sakllam           #+#    #+#             */
/*   Updated: 2022/03/12 21:28:56 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_checksforqoutes(char *str, int qoute)
{
	int	i;

	i = ft_strlen(str);
	if (str[i - 1] == qoute)
		return (1);
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
		if (start)
		{
			if (parsresult->TYPE == PRTCLOSE || parsresult->TYPE == OR
				|| parsresult->TYPE == AND || parsresult->TYPE == PIPE)
				return (1);
			start = 0;
		}
		if ((parsresult->TYPE == PIPE || parsresult->TYPE == AND
			|| parsresult->TYPE == OR))
		{
			if (!parsresult->next || parsresult->next->TYPE == PIPE 
				|| parsresult->next->TYPE == AND || parsresult->next->TYPE == OR
				|| parsresult->next->TYPE == PRTCLOSE)
				return (1);
		}
		if (parsresult->TYPE == PRTOPEN)
		{
			prth++;
			if (!parsresult->next || parsresult->next->TYPE == PIPE 
				|| parsresult->next->TYPE == AND || parsresult->next->TYPE == OR
				|| parsresult->next->TYPE == PRTCLOSE)
				return (1);
		}
		if (parsresult->TYPE == PRTCLOSE)
		{
			prth--;
			if (parsresult->next && (parsresult->next->TYPE == WORD 
				|| parsresult->next->TYPE == PRTOPEN || parsresult->next->TYPE == SQ 
				|| parsresult->next->TYPE == DQ  || parsresult->next->TYPE == WILD
				|| parsresult->next->TYPE  == VARIABLE))
				return (1);
		}
		if (parsresult->TYPE == VARIABLE)
		{
			if (ft_strlen(parsresult->splited) == 1)
				return (1);
		}
		if (parsresult->TYPE == WILD)
		{
			if (parsresult->next && parsresult->next->TYPE == PRTOPEN)
				return (1);
		}
		if (parsresult->TYPE == RDIN)
		{
			if (!parsresult->next || (parsresult->next->TYPE != WILD 
				&& parsresult->next->TYPE != WORD && parsresult->next->TYPE != SQ
				&& parsresult->next->TYPE != DQ))
				return (1);
		}
		if (parsresult->TYPE == RDOUT)
		{
			if (!parsresult->next || (parsresult->next->TYPE != WILD 
				&& parsresult->next->TYPE != WORD && parsresult->next->TYPE != SQ
				&& parsresult->next->TYPE != DQ))
				return (1);
		}
		if (parsresult->TYPE == RDHER)
		{
			if (!parsresult->next || (parsresult->next->TYPE != WILD 
				&& parsresult->next->TYPE != WORD && parsresult->next->TYPE != SQ
				&& parsresult->next->TYPE != DQ))
				return (1);
		}
		if (parsresult->TYPE == RDAPP)
		{
			if (!parsresult->next || (parsresult->next->TYPE != WILD 
				&& parsresult->next->TYPE != WORD && parsresult->next->TYPE != SQ
				&& parsresult->next->TYPE != DQ))
				return (1);
		}
		if (parsresult->TYPE == DQ)
		{
			if (!ft_checksforqoutes(parsresult->splited, 34))
				return (1);
		}
		if (parsresult->TYPE == SQ)
		{
			if (!ft_checksforqoutes(parsresult->splited, 39))
				return (1);
		}
		parsresult = parsresult->next;
	}
	if (prth)
		return (1);
	return (0);
}