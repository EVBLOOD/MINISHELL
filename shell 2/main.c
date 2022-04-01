/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 23:58:50 by sakllam           #+#    #+#             */
/*   Updated: 2022/03/28 13:52:48 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}
int affich(t_tree *tree, char *str, int n)
{
	int i = 0;
	if (!tree)
		return(-1);
	while(i++ < n)
		printf("------- ");
	n++;
	i = -1;
	printf("%d : %s\n\n", tree->type, str);
	if (tree->type == LIST)
	{

		while(tree->elements[++i])
		{
			if (tree->elements[i]->TYPE != SPACES)
				printf ("value: %s\n", tree->elements[i]->splited);
			else
				printf ("spaces: %d\n", tree->elements[i]->nb);
		}
	}
	if (tree->left)
		affich(tree->left, "left", n);
	if (tree->right)
		affich(tree->right, "rigth", n);
	return (tree->type);
}

int	main(int argc, char *argv[], char *env[])
{
	char	*line;
	t_tree	*tree;
	t_execute args;
	char *sr_cap;
	char	**newenv;
	char	**joined;
	//signals
	newenv = ft_cloneenv(env);
	while (1)
	{
		rl_catch_signals = 0;
		line = readline("$> ");
		if (!line)
		{
			ft_SHLVL(newenv, -1);
			sr_cap = tgetstr("sr", NULL);
			tputs(sr_cap, 0,  ft_putchar);
			printf("$> exit\n");
			exit (0);
		}
		if (line)
		{
			add_history(line);
			tree = ft_parsing(line);
		// affich(tree, "root", 0);
			ft_execution(newenv, tree, 'p', args);
		}
		// if (tree)
		// {
		// if(tree->elements)
		// 	{
		// 		joined = ft_dealwithlist(tree->elements, newenv);
		// 		int i;
		// 		i = 0;
		// 		while (joined[i])
		// 		{
		// 			printf("|%s| \n", joined[i]);
		// 			i++;
		// 		}
		// 	}
		// }
	}
}