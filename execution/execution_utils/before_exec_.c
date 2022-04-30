/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_exec_.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saad <saad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:32:52 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/30 18:27:11 by saad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

char	**ft_convertfromlisttochar(t_befexec *list)
{
	int		i;
	char	**cnv;

	i = ft_ofclengh(list);
	cnv = ft_malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (list)
	{
		cnv[i] = list->ofcvalue;
		i++;
		list = list->next;
	}
	cnv[i] = NULL;
	return (cnv);
}

char	*ft_replaceandjoin(char **str, char *tojoin)
{
	*str = ft_strjoin(*str, tojoin);
	return (*str);
}

void	ft_wildmergin(char **str, t_befexec **head)
{
	char	**names;
	int		i;

	names = ft_wildcard_(*str);
	i = 0;
	while (names[i])
	{
		ft_ofcadd_back(head, ft_createnode(names[i]));
		i++;
	}
}

int	ft_countstars(char *str, int wild)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '*')
			count++;
		i++;
	}
	return (count + wild);
}

void	ft_varmerging(t_list *list, char **str, int *wild, t_befexec **head)
{
	int	i;

	i = 0;
	while (list->expanded[i])
	{
		if (list->expanded[i][0] == ' ' && ft_strlen(*str) > 0)
		{
			if (ft_countstars("", *wild) > 0)
				ft_wildmergin(str, head);
			else
				ft_ofcadd_back(head, ft_createnode(*str));
			*str = ft_strdup("");
			*wild = 0;
		}
		if (list->expanded[i][0] != ' ')
			*str = ft_replaceandjoin(str, list->expanded[i]);
		i++;
	}
}
