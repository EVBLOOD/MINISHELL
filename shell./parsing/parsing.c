/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 06:06:53 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/04 17:04:08 by sakllam          ###   ########.fr       */
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
	free(tmpline);
	list = ft_lexicalanalysis(line);
	if (!list || ft_syntaxanalysis(list))
	{
		free(line);
		return (NULL);
	}
	listv = ft_redirectionsset(list);
	tree = ft_abs(&listv, NULL);
	return (tree);
}