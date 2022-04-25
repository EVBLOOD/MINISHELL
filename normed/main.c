/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 02:38:11 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/25 16:11:39 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

t_globale	g_exec;

void handle(int sig)
{
	if (sig == SIGINT)
	{
		if(g_exec.isexecuting)
			return ;
		write(1, "\n", 1);
        rl_replace_line("", 0);
		rl_on_new_line();
        rl_redisplay();
		g_exec.returnvalue = 1;
	}
}

void ft_signal(void)
{
	if (signal(SIGINT, handle) == SIG_ERR || \
	signal(SIGQUIT, SIG_IGN) == SIG_ERR || \
	signal(SIGTSTP, SIG_IGN) == SIG_ERR)
	{
		write(2, "sig error\n", 10);
		exit (1);
	}
}

void	ft_thegreatbash(char *line, t_tree *tree, char ***newenv)
{
	add_history(line);
	tree = ft_parsing(line);
	g_exec.isexecuting = 1;
	if (tree)
		run(tree, *newenv);
	cleartrush();
}

void	start(char ***newenv, int *io, char **env)
{
	*newenv = ft_cloneenv(env);
	ft_signal();
	save_io(io);
	g_exec.trush = NULL;
	g_exec.returnvalue = 0;
}

int	main(int argc, char *argv[], char *env[])
{
	char	*line;
	t_tree	*tree;
	char	**newenv;
	int		io[2];

	start(&newenv, io, env);
	while (1)
	{
		rl_catch_signals = 0;
		g_exec.isexecuting = 0;
		line = readline("$> ");
		if (!line)
			itsnull(newenv);
		if (line[0] != '\0')
			ft_thegreatbash(line, tree, &newenv);
		else
			g_exec.returnvalue = 0;
		reset_io(io);
		free(line);
	}
	free(newenv);
	return (0);
}
