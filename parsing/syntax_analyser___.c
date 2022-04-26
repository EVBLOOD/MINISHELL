/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyser___.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:07:02 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/26 00:26:38 by foulare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	ft_syntaxanalysis(t_list *parsresult)
{
	int	prth;
	int	start;

	start = 1;
	prth = 0;
	while (parsresult)
	{
		if (ft_syntaxcond(parsresult, &start, &prth))
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
