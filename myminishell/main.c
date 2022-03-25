/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:12:44 by sakllam           #+#    #+#             */
/*   Updated: 2022/03/20 11:05:23 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>


void handle(int sig, siginfo_t *info, void *c)
{
	if (sig == SIGINT)
		write(1, "\n$> ", 4);
}

int ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int len(char **str)
{
	int i = 0;
	while (str[i])
		i++;
	return(i);
}

void ft_signal()
{
	struct sigaction sa;
	
	sa.sa_sigaction = &handle;
	sa.sa_flags = SA_RESTART;
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &sa, NULL);
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
	if (tree->type == WORD || tree->type == VARIABLE)
		while(tree->element[++i])
			printf ("value: %s len: %d\n", tree->element[i], len(tree->element));
//	puts("hello");
	printf("%d : %s\n\n", tree->type, str);
	if (tree->left)
		affich(tree->left, "left", n);
	if (tree->right)
		affich(tree->right, "rigth", n);
	return (tree->type);
}

char *types[] =  {
"PIPE",
"DQ",
"SQ",
"WORD",
"RDIN",
"RDOUT",
"RDHER",
"RDAPP",
"VARIABLE",
"AND",
"OR",
"PRTOPEN",
"PRTCLOSE",
"WILD"
};


void disp(t_tree *tree, int ident) {
	if (!tree) return ;
	for (int i = 0; i < ident; i++) printf("\t");
	printf("%s", types[tree->type]);
	if (tree->type == WORD) {
		printf(": ");
		for (int i = 0; tree->element[i]; i++) {
			printf(" %s  ", tree->element[i]);
		}
	}
	printf("\n");
	disp(tree->right, ident + 1);
	disp(tree->left, ident + 1);
}


int main(int ac, char **av, char **env)
{
	char	*line;
	t_env	*envn;
	char *sr_cap;
	t_list	*parsresult;
	t_tree	*tree;
	int		ret;

	ft_signal();
	envn = ft_cloneenv(env);
	while (1)
	{
			// printf("");
		// rl_prompt = ft_strdup("$> ");
		rl_catch_signals = 0;
		line = readline("$> ");
		if (!line)
		{
			sr_cap = tgetstr("sr", NULL);
			tputs(sr_cap, 0,  ft_putchar);
			printf("$> exithhhhh\n");
			exit(0);
		}
		if(line[0] != '\0')
		{
			add_history(line);
			// char **lind = {"saad $PATH:",NULL};
			// printf("%s", ft_scanvar(lind, envn));
			parsresult = ft_lexicalanalysis(line);
			if (ft_syntaxanalysis(parsresult))
				write (1, "sh: syntax error near unexpected token\n", 39);
			else
			{
				tree = ft_abs(&parsresult, NULL);
				ft_execution(envn, tree, 'p', tree, 0);
			}
			 	 affich(tree, "root", 0);
				// disp(tree, 0);
			// //	ret = ft_execution(tree, ret);
			// 	// while (parsresult)
			// 	// {
			// 	// 	printf("%d:{%s}\n", parsresult->TYPE, parsresult->splited);
			// 	// 	parsresult = parsresult->next;
			// 	// }
			// }
		}
	}
	
}