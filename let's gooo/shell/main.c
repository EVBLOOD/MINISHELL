/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 23:58:50 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/22 08:57:07 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char *table[] = {
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
"WILD",
"SPACES",
"LIST",
"RDARG"
};


void handle(int sig, siginfo_t *info, void *c)
{
	sigset_t mask;

	if (sig == SIGINT)
		write(1, "\n$> ", 4);
}

void ft_signal()
{
	struct sigaction sa;
	sa.sa_sigaction = &handle;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

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
	printf("%s : %s\n\n", table[tree->type], str);
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
	t_execute	args;
	char		*sr_cap;
	char		**newenv;
	char		**joqined;
	t_executenop	arg;
	int  io[2];
	

	ft_signal();
	newenv = ft_cloneenv(env);
	save_io(io);
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
		if (line[0] != '\n')
		{
			add_history(line);
			tree = ft_parsing(line);
			arg.root = tree;
			arg.pos = 'p';
			args.modepipe = 0;
		//	affich(tree,  "root", 0);
			if (tree)
				run(tree, env);
				// ft_treeexecution(env, tree, 'p', arg);
				// ft_execution(newenv, tree, arg, &args);
		}
		reset_io(io);
	}
}

void	save_io(int io[2])
{
	io[0] = dup(STDIN_FILENO);
	io[1] = dup(STDOUT_FILENO);
	if (io[0] == -1 || io[1] == -1)
		perror(NULL);
}

void	reset_io(int io[2])
{
	if (dup2(io[0], STDIN_FILENO) == -1 || dup2(io[1], STDOUT_FILENO) == -1)
		perror(NULL);
}
