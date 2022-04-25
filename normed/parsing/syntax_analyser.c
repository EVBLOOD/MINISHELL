/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:00:44 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/25 01:02:01 by sakllam          ###   ########.fr       */
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