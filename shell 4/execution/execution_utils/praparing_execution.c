/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   praparing_execution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 19:44:28 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/02 19:52:58 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

void	ft_replaceall(t_list **list, char **env, int red)
{
	int		i;
	char	*str;

	i = 0;
	while (list[i])
	{
		if (list[i]->TYPE == VARIABLE)
		{
			list[i]->expanded = ft_expandvariables(*list, env);
			if (!(list[0]->expanded) && red)
				break;
		}
		if (list[i]->TYPE == SQ)
		{
			str = ft_expand_sq(list[i]);
			free(list[i]->splited);
			list[i]->splited = str;
		}
		if (list[i]->TYPE == DQ)
		{
			str = ft_expand_dq(list[i], env);
			free(list[i]->splited);
			list[i]->splited = str;	
		}
		if (list[i]->TYPE == SPACES && red)
			break;
		i++;
	}
}



char	**ft_dealwithlist(t_list **list, char **env, int red)
{
	char		**converted;
	t_befexec	*ret;
	int			i;

	ft_replaceall(list, env, red);
	ret = ft_expandingwildcard(list, env, red);
	converted = ft_convertfromlisttochar(ret);
	i = 0;
	puts("-----------------------------------");
	while (converted[i])
	{
		puts(converted[i]);
		i++;
	}
	puts("-----------------------------------");
	exit();
	return (converted);
}