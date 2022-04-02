/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 06:06:53 by sakllam           #+#    #+#             */
/*   Updated: 2022/03/25 15:35:58 by sakllam          ###   ########.fr       */
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
	if (ft_strlen(tmpline) == 0)
	{
		free(line);
		free(tmpline);
		return (NULL);
	}
	list = ft_lexicalanalysis(line);
	tmplist = list;
	while (tmplist)
	{
		// if (tmplist->TYPE != SPACES)
		// 	printf("word: %s : type: %d\n", tmplist->splited, tmplist->TYPE);
		// else
		// 	printf("spaces: %d\n", tmplist->nb);
		tmplist = tmplist->next;
	}
	if (!list || ft_syntaxanalysis(list))
		return (NULL);
	listv = ft_redirectionsset(list);
	tree = ft_abs(&listv, NULL);
	return (tree);
}