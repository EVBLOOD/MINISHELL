/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 06:06:53 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/15 20:12:49 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

t_tree	*ft_parsing(char *line)
{
	t_list	*list;
	t_list	*listv;
	t_list	*tmplist;
	t_tree	*tree;
	char	*tmpline;

	tmpline = ft_strtrim(line, " \t\n\v\f\r");
	free(line);
	if (ft_strlen(tmpline) == 0)
	{
		free(tmpline);
		return (NULL);
	}
	list = ft_lexicalanalysis(tmpline);
	if (!list || ft_syntaxanalysis(list))
	{
		free(line);
		return (NULL);
	}
	listv = ft_redirectionsset(list);
	// while (listv)
	// {
	// 	puts(listv->splited);
	// 	listv = listv->next;
	// }
	// exit (1);
	// puts("start");
	tree = ft_abs(&listv, NULL);
	// puts("end");
	// exit(5);
	return (tree);
}