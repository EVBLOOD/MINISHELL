/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:22:58 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/09 00:11:09 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

// int	ft_getstatus(pid_t pid)
// {
// 	int	status;

// 	waitpid(pid, &status, 0);
// 	return (status);
// }

// void	ft_argset(t_tree *tree, t_execute args)
// {
// 	if (tree->type != LIST)
// 		args.parrent = tree;
// }

// int	ft_andorreturn (t_tree *tree, int *i)
// {
// 	if (tree->left)
// 		i = ft_execution(env, tree->left, 'l', args);
// 	else if (tree->right)
// 		i = ft_execution(env, tree->right, 'r', args);
// }

// int	ft_notpfunction(t_execute args, char position, t_tree *tree)
// {
// 	if (args.parrent->type == AND)
// 				return (ft_ANDfuction(position, tree, env));
// 	else if (args.parrent->type == OR)
// 			return (ft_ORfunction(position, tree, env));
// 	else if (args.parrent->type == PIPE)
// 		return (ft_PIPEfunction(position, tree, env, 0, pip));
// 	else if (args.parrent->type == RDAPP || args.parrent->type == RDHER
// 		|| args.parrent->type || args.parrent->type == RDOUT)
// 		return (ft_RDRfunction(position, tree, env, args.parrent->type, args.pipe[0]));
// }

int	ft_getreturn(pid_t id)
{
	int	ret;

	waitpid(id, &ret, 0);
	return (ret);
}

int	ft_simplecmd(char **env, t_tree *tree)
{
	pid_t	id;
	char	**command;
	char	*path;

	command = ft_dealwithlist(tree->elements, env, 0);
	path = ft_isacmd(command[0], env);
	id = fork();
	if (id == 0)
	{
		if (execve(path, command, env) < 0)
		{
			perror("minishell:");
			exit(1);
		}
	}
	return (ft_getreturn(id));
}

pid_t	midel_first_partpipe(int *wr_fd, t_tree *tree, char **env)
{
	char	*path;
	pid_t	id;
	char	**command;

	// tree->elements = check_wild(tree->elements);
	command = ft_dealwithlist(tree->elements, env, 0);
	path = ft_isacmd(command[0], env);
	pipe(wr_fd);
	id = fork();
	if (path)
	{
		if (id == 0)
		{
			close(wr_fd[0]);
			dup2(wr_fd[1], 1);
			if (execve(path, command, env) < 0)
				exit (1);
		}
	}
	else
		printf("minishell: %s:Command not found\n", command[0]);
	return (id);
}

void	main_pipe(int *wr_fd)
{
	close(wr_fd[1]);
	dup2(wr_fd[0], 0);
}

int	ft_execpipes(t_execute args, char **env, t_tree *tree, char position)
{
	int	ret;

	if (args.parrent == args.root && position == 'r')
	{
		ret = ft_simplecmd(env, tree);
		close(args.pipe[0]);
		dup2(args.input, 0);
		dup2(args.output, 1);
		// puts(tree->elements[1]->splited);
		// printf("%c\n", position);
		// puts("out");
	}
	else
	{
		if (position == 'l')
		{
			args.input = dup(0);
			args.output = dup(1);
		}
		ret = midel_first_partpipe(args.pipe, tree, env);
		// dup2(args.output, 1);
		// puts(tree->elements[0]->splited);
		// printf("%c\n", position);
		// puts("in");
		// main_pipe(args.pipe);
	}
	return (ret);
}



int	ft_execution(char **env, t_tree *tree, char position, t_execute args)
{
	int i;

	i = 0;
	if (tree->type != LIST)
		args.parrent = tree;
	if (tree->type == OR)
		i = 1;
	if (tree->left)
		i = ft_execution(env, tree->left, 'l', args);
	if (tree->type == PIPE)
		main_pipe(args.pipe);
	if (tree->type == AND && i)
			return (i);
	else if (tree->type == OR && !i)
		return (i);
		// it and | or => new root
	if (tree->right)
		i = ft_execution(env, tree->right, 'r', args);
	if (tree->type != PIPE && tree->type != AND && tree->type != OR)
	{
		if (position != 'p')
		{
			if (args.parrent->type == AND)
				return (ft_simplecmd(env, tree));
			else if (args.parrent->type == OR)
				return (ft_simplecmd(env, tree));
			else if (args.parrent->type == PIPE)
				return (ft_execpipes(args, env, tree, position));
			else if (args.parrent->type == LIST)
				return (ft_simplecmd(env, tree));
		}
		else
			return (ft_simplecmd(env, tree));
		// else if (args.parrent->type == RDAPP || args.parrent->type == RDHER
		// 		|| args.parrent->type || args.parrent->type == RDOUT)
		// else

	}
	return (i);

}