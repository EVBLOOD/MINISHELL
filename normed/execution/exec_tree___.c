/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree___.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 02:25:39 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/25 02:34:55 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	ittowait(int right_pid)
{
	int	status;

	waitpid(right_pid, &status, 0);
	g_exec.returnvalue = ft_statushundling(status);
	wait(NULL);
}

int	rightpipefunction(t_tree *tree, char **env, int *pfd)
{
	int	right_pid;

	right_pid = fork();
	if (right_pid == -1)
	{
		g_exec.returnvalue = 1;
		exit(1);
	}
	else if (right_pid == 0)
	{
		close(STDIN_FILENO);
		close(pfd[OUT]);
		dup2(pfd[IN], STDIN_FILENO);
		close(pfd[IN]);
		run(tree->right, env);
		exit(0);
	}
	close(pfd[0]);
	close(pfd[1]);
	ittowait(right_pid);
	return (g_exec.returnvalue);
}

void	ft_apndredirections(t_tree *tree, char **env)
{
	char	**filename;
	int		fd;

	filename = ft_dealwithlist(ft_copycolly(tree->redirections), env);
	if (!filename[0] || filename[1])
	{
		write(2, "bash : ambiguous redirect\n", 26);
		g_exec.returnvalue = 1;
		return ;
	}
	fd = open(filename[0], O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd < 0)
	{
		g_exec.returnvalue = 1;
		perror("bash:");
		return ;
	}
	close(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	run(tree->left, env);
	run(tree->right, env);
}

int	ft_openherdoc(t_tree *tree, char **env)
{
	int	fd;
	char	*name;

	fd = open(tree->elements[0]->splited, O_RDONLY);
	if (!tree->elements[0]->herdocexp)
	{
		name = herdoc(fd, env, tree->elements[0]->splited);
		close (fd);
		fd = open(name, O_RDONLY);
		unlink(name);
	}
	return (fd);
}

void	redirectionherdoc(t_tree *tree, char **env)
{
	char	**filename;
	int		fd;

	fd = ft_openherdoc(tree, env);
	if (fd < 0)
	{
		g_exec.returnvalue = 1;
		return ;
	}
	close(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (tree->left)
		run(tree->left, env);
	if (tree->right)
		run(tree->right, env);
	unlink(tree->elements[0]->splited);
}