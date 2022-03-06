/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:12:44 by sakllam           #+#    #+#             */
/*   Updated: 2022/03/06 15:23:08 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int affich(t_tree *tree, char *str, int n)
{
	int i = 0;
	if (!tree)
		return(-1);
	while(i++ < n)
		printf("------- ");
	n++;
	printf("%d : %s\n\n", tree->type, str);
	if (tree->left)
		affich(tree->left, "left", n);
	if (tree->right)
		affich(tree->right, "rigth", n);
	return (tree->type);
}

int main()
{
	char	*line;
	t_list	*parsresult;
	t_tree	*tree;
	int		ret;

	while (1)
	{
		line = readline("$> ");
		add_history(line);
		parsresult = ft_lexicalanalysis(line);
		if (ft_syntaxanalysis(parsresult))
			write (1, "Error syntax\n", 14);
		else
		{
			tree = ft_abs(&parsresult, NULL);
			affich(tree, "root", 0);
			ret = ft_execution(tree, ret);
			// while (parsresult)
			// {
			// 	printf("%d:{%s}\n", parsresult->TYPE, parsresult->splited);
			// 	parsresult = parsresult->next;
			// }
		}
	}
}