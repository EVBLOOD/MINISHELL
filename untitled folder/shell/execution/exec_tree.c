/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:22:58 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/12 09:15:09 by sakllam          ###   ########.fr       */
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
// 		args->parrent = tree;
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
// 	if (args->parrent->type == AND)
// 				return (ft_ANDfuction(position, tree, env));
// 	else if (args->parrent->type == OR)
// 			return (ft_ORfunction(position, tree, env));
// 	else if (args->parrent->type == PIPE)
// 		return (ft_PIPEfunction(position, tree, env, 0, pip));
// 	else if (args->parrent->type == RDAPP || args->parrent->type == RDHER
// 		|| args->parrent->type || args->parrent->type == RDOUT)
// 		return (ft_RDRfunction(position, tree, env, args->parrent->type, args->pipe[0]));
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
	if (!path)
		return (printf("NO SUCH A CMD\n"));
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
	if (!path)
		return (printf("NO SUCH A CMD\n"));
	pipe(wr_fd);
	id = fork();
	if (id == 0)
	{
		close(wr_fd[0]);
		dup2(wr_fd[1], 1);
		close(wr_fd[1]);
		if (execve(path, command, env) < 0)
			exit (1);
	}
	// close(wr_fd[0]);
	close(wr_fd[1]);
	return (id);
}

void	main_pipe(t_tree *tree)
{
	int	fds[2];
	
	pipe(fds);
	// // close(wr_fd[1]);
	// dup2(wr_fd[0], 0);
	// close(wr_fd[0]);
}

// int	ft_execpipes(t_execute args, char **env, t_tree *tree, char position)
// {
// 	int	ret;

// 	if (args->parrent == args->root && position == 'r')
// 	{
// 		// dup2(args->output, 1);
// 		// close (args->output);
// 		// ret = ft_simplecmd(env, tree);
// 		// while (waitpid(-1, 0, 0) > 0);
// 		// dup2(args->input, 0);
// 		// close(args->input);
// 		puts("out");
// 		puts(tree->elements[1]->splited);
// 		printf("%c\n", position);
// 	}
// 	else
// 	{
// 		// if (position == 'l')
// 			// args->input = dup(0);
// 		// ret = midel_first_partpipe(args->pipe, tree, env);
// 		// dup2(args->output, 1);
// 		// dup2(args->input, 0);
// 		// puts(tree->elements[0]->splited);
// 		puts("in");
// 		puts(tree->elements[1]->splited);
// 		printf("%c\n", position);
// 		// main_pipe(args->pipe);
// 	}
// 	return (ret);
// }

void	ft_firstpartpipe(t_execute *args, char **env, t_tree *tree, t_executenop arg)
{
	char	**command;
	char	*path;
	pid_t	id;

	command = ft_dealwithlist(tree->elements, env, 0);
	path = ft_isacmd(command[0], env);
	if (!path)
	{
		printf("%s: command not found\n", command[0]);
		return ;
	}
	id = fork();
	if (id == 0)
	{
		close(args->newpipe[0]);
		dup2(args->newpipe[1], 1);
		close(args->newpipe[1]);
		if (execve(path, command, env) < 0)
			exit (1);
	}
	close(args->newpipe[1]);
}

void	ft_lastpartpipe(t_execute *args, char **env, t_tree *tree, t_executenop arg)
{
	char	**command;
	char	*path;
	pid_t	id;
	int		ret;

	command = ft_dealwithlist(tree->elements, env, 0);
	path = ft_isacmd(command[0], env);
	if (!path)
	{
		printf("%s: command not found\n", command[0]);
		return ;
	}
	id = fork();
	if (id == 0)
	{
		dup2(args->newpipe[0], 0);
		close(args->newpipe[0]);
		if (execve(path, command, env) < 0)
			exit (1);
	}
	close(args->newpipe[0]);
	waitpid(id, &ret, 0);
	args->piperet = ret;
	while (waitpid(-1, 0, 0) >= 0);
	free(args->newpipe);
}

void	ft_mdlpipecmds(t_execute *args, char **env, t_tree *tree, t_executenop arg)
{
	char	**command;
	char	*path;
	pid_t	id;

	command = ft_dealwithlist(tree->elements, env, 0);
	path = ft_isacmd(command[0], env);
	if (!path)
	{
		printf("%s: command not found\n", command[0]);
		return ;
	}
	args->oldpipe = args->newpipe;
	args->newpipe = malloc(sizeof(int) * 2);
	pipe(args->newpipe);
	id = fork();
	if (id == 0)
	{
		dup2(args->oldpipe[0], 0);
		close(args->oldpipe[0]);
		close(args->newpipe[0]);
		dup2(args->newpipe[1], 1);
		close(args->newpipe[1]);
		if (execve(path, command, env) < 0)
			exit (1);
	}
	close(args->oldpipe[0]);
	close(args->newpipe[1]);
	free(args->oldpipe);
}

void	ft_execpipes(t_execute *args, char **env, t_tree *tree, t_executenop arg)
{
	if (arg.pos == 'l')
		ft_firstpartpipe(args, env, tree, arg);
	else if (arg.pos == 'r' && arg.parrent == arg.root)
		ft_lastpartpipe(args, env, tree, arg);
	else
		ft_mdlpipecmds(args, env, tree, arg);
}

// int	ft_execpipes(t_execute *args, char **env, t_tree *tree, t_executenop arg)
// {
// 	int	ret;
// 	char	*path;
// 	pid_t	id;
// 	char	**command;

// 	if (arg.pos == 'l')
// 	{
// 		command = ft_dealwithlist(tree->elements, env, 0);
// 		path = ft_isacmd(command[0], env);
// 		if (!path)
// 			return (printf("%s: command not found\n", command[0]));
// 		id = fork();
// 		if (id == 0)
// 		{
// 			close(args->newpipe[0]);
// 			dup2(args->newpipe[1], 1);
// 			close(args->newpipe[1]);

// 			if (execve(path, command, env) < 0)
// 				exit (1);
// 		}
// 		close(args->newpipe[1]);
// 	}
// 	else if (arg.pos == 'r' && arg.parrent == arg.root)
// 	{
// 		command = ft_dealwithlist(tree->elements, env, 0);
// 		path = ft_isacmd(command[0], env);
// 		if (!path)
// 			return (printf("%s: command not found\n", command[0]));
// 		id = fork();
// 		if (id == 0)
// 		{
// 			dup2(args->newpipe[0], 0);
// 			close(args->newpipe[0]);

// 			if (execve(path, command, env) < 0)
// 				exit (1);
// 		}
// 		close(args->newpipe[0]);
// 		while (waitpid(-1, 0, 0) >= 0);
// 		free(args->newpipe);
// 		// waitpid(id, 0, 0);
// 	}
// 	else
// 	{
// 		command = ft_dealwithlist(tree->elements, env, 0);
// 		path = ft_isacmd(command[0], env);
// 		if (!path)
// 			return (printf("%s: command not found\n", command[0]));
// 		args->oldpipe = args->newpipe;
// 		args->newpipe = malloc(sizeof(int) * 2);
// 		pipe(args->newpipe);
// 		id = fork();
// 		if (id == 0)
// 		{
// 			dup2(args->oldpipe[0], 0);
// 			close(args->oldpipe[0]);

// 			close(args->newpipe[0]);
// 			dup2(args->newpipe[1], 1);
// 			close(args->newpipe[1]);

// 			if (execve(path, command, env) < 0)
// 				exit (1);
// 		}
// 		close(args->oldpipe[0]);
// 		close(args->newpipe[1]);
// 		free(args->oldpipe);
// 	}
// 	return (ret);
// }


int	ft_execution(char **env, t_tree *tree, t_executenop arg, t_execute *args)
{
	int i;

	i = 0;
	if (tree->type != LIST)
		arg.parrent = tree;
	if (tree->type == OR)
		i = 1;
	if (tree->type == PIPE && tree->left->type != PIPE)
	{
		args->newpipe = malloc(sizeof(int) * 2);
		puts("pipe");
		printf("new: %p, old: %p\n", args->newpipe, args->oldpipe);
		pipe(args->newpipe);
		args->oldpipe = NULL;
	}
	if (tree->left)
	{
		arg.pos = 'l';
		i = ft_execution(env, tree->left, arg, args);
	}
	// if (tree->type == PIPE)
	// {
	// 	// dup2(args->output, 1);
	// 	// close(args->output);
	// 	// main_pipe(args->pipe);
	// 	puts("pipe");
	// 	printf("%c\n", position);
	// }
	if (tree->type == AND && i)
			return (i);
	else if (tree->type == OR && !i)
		return (i);
		// it and | or => new root
	if (tree->right)
	{
		arg.pos = 'r';
		i = ft_execution(env, tree->right, arg, args);
	}
	if (tree->type != PIPE && tree->type != AND && tree->type != OR)
	{
		if (arg.pos != 'p')
		{
			if (arg.parrent->type == AND)
				return (ft_simplecmd(env, tree));
			else if (arg.parrent->type == OR)
				return (ft_simplecmd(env, tree));
			else if (arg.parrent->type == PIPE)
				ft_execpipes(args, env, tree, arg);
			else if (arg.parrent->type == LIST)
				return (ft_simplecmd(env, tree));
		}
		else
			return (ft_simplecmd(env, tree));
		// else if (arg.parrent->type == RDAPP || arg.parrent->type == RDHER
		// 		|| arg.parrent->type || arg.parrent->type == RDOUT)
		// else

	}
	return (i);

}