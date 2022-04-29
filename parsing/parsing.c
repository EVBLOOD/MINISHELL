/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 00:59:02 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/28 22:06:17 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

t_tree	*ft_parsing(char *line)
{
	t_list	*list;
	t_list	*listv;
	t_tree	*tree;
	char	*tmpline;

	tmpline = ft_strtrim(line, " \t\n\v\f\r");
	if (ft_strlen(tmpline) == 0)
		return (NULL);
	list = ft_lexicalanalysis(tmpline);
	if (!list || ft_syntaxanalysis(list))
		return (NULL);
	listv = ft_redirectionsset(list);
	tree = ft_abs(&listv, NULL);
	return (tree);
}
