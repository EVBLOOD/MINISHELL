/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:22:58 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/18 03:30:42 by sakllam          ###   ########.fr       */
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
		return (ft_nocommand(command[0]));
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
		return (ft_nocommand(command[0]));
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

	id = fork();
	if (id == 0)
	{
		command = ft_dealwithlist(tree->elements, env, 0);
		path = ft_isacmd(command[0], env);
		if (!path)
			return ((void)ft_nocommand(command[0]));
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

	id = fork();
	if (id == 0)
	{
		command = ft_dealwithlist(tree->elements, env, 0);
		path = ft_isacmd(command[0], env);
		if (!path)
			return ((void)ft_nocommand(command[0]));
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

	args->oldpipe = args->newpipe;
	args->newpipe = malloc(sizeof(int) * 2);
	pipe(args->newpipe);
	id = fork();
	if (id == 0)
	{
		command = ft_dealwithlist(tree->elements, env, 0);
		path = ft_isacmd(command[0], env);
		if (!path)
			return ((void)ft_nocommand(command[0]));
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

// void	ft_execpipes(t_execute *args, char **env, t_tree *tree, t_executenop arg)
// {
// 	// printf("%d\n", arg.root->type);
// 	// printf("parent: %p, root: %p",  arg.parrent, arg.root);
// 	if (arg.pos == 'l')
// 	{
// 		ft_firstpartpipe(args, env, tree, arg);
// 		// puts("start");
// 	}
// 	else if (!(arg.pos == 'r' && arg.parrent == arg.root))
// 	{
// 		ft_lastpartpipe(args, env, tree, arg);
// 		// puts("end");
// 	}
// 	else
// 	{
// 		ft_mdlpipecmds(args, env, tree, arg);
// 		// puts("mdl");
// 	}
// }

void	ft_execpipes(t_execute *args, char **env, t_tree *tree, t_executenop arg)
{
	if (arg.pos == 'l')
		ft_firstpartpipe(args, env, tree, arg);
	else if (arg.pos == 'r' && arg.parrent == arg.root)
		ft_lastpartpipe(args, env, tree, arg);
	else
		ft_mdlpipecmds(args, env, tree, arg);
}

int	ft_executeappend(t_tree *tree, char **env)
{
	pid_t	id;
	char	**command;
	char	*path;
	int		fd;

	id = fork();
	if (id == 0)
	{
		command = ft_dealwithlist(tree->elements, env, 0);
		path = ft_isacmd(command[1], env);
		fd = open(command[0], O_WRONLY | O_APPEND | O_CREAT, 0644);
		dup2(fd, 1);
		close (fd);
		if (!path)
			return (ft_nocommand(command[1]));
		if (execve(path, &command[1], env) < 0)
		{
			perror("minishell:");
			exit(1);
		}
	}
	return (ft_getreturn(id));
}

int	ft_executeherdoc(t_tree *tree, char **env)
{
	pid_t	id;
	char	**command;
	char	*path;
	int		fd;

	id = fork();
	if (id == 0)
	{
		command = ft_dealwithlist(tree->elements, env, 0);
		path = ft_isacmd(command[1], env);
		fd = open(command[0], O_RDWR); // change values
		dup2(fd, 1);
		close (fd);
		if (!path)
			return (ft_nocommand(command[1]));
		if (execve(path, &command[1], env) < 0)
		{
			perror("minishell:");
			exit(1);
		}
	}
	return (ft_getreturn(id));
}

int	ft_nocommand(char *line)
{
	write(2, line, ft_strlen(line));
	write(2, ": command not found\n", 20);
	return (127);
}

int	ft_executein(t_tree *tree, char **env)
{
	pid_t	id;
	char	**command;
	char	*path;
	int		fd;

	id = fork();
	if (id == 0)
	{
		command = ft_dealwithlist(tree->elements, env, 0);
		path = ft_isacmd(command[1], env);
		fd = open(command[0], O_RDONLY);
		dup2(fd, 0);
		close (fd);
		if (!path)
			return (ft_nocommand(command[1]));
		if (execve(path, &command[1], env) < 0)
		{
			perror("minishell:");
			exit(1);
		}
	}
	return (ft_getreturn(id));
}

int	ft_executeout(t_tree *tree, char **env)
{
	pid_t	id;
	char	**command;
	char	*path;
	int		fd;

	id = fork();
	if (id == 0)
	{
		command = ft_dealwithlist(tree->elements, env, 0);
		path = ft_isacmd(command[1], env);
		fd = open(command[0], O_RDWR | O_CREAT | O_TRUNC, 0644);;
		dup2(fd, 1);
		close (fd);
		if (!path)
			return (ft_nocommand(command[1]));
		if (execve(path, &command[1], env) < 0)
		{
			perror("minishell:");
			exit(1);
		}
	}
	return (ft_getreturn(id));
}

int	ft_executereds(t_tree *tree, char **env, t_executenop arg)
{
	int	ret;
	char **command;

	command = ft_dealwithlist(tree->elements, env, 0);
	if (command[1] == NULL)
	{
		if (arg.parrent->type == RDAPP)
			ret = open(command[0], O_RDWR | O_CREAT | O_APPEND, 0644);
		if (arg.parrent->type == RDOUT)
			ret = open(command[0], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (arg.parrent->type == RDIN)
			ret = open(command[0], O_RDWR);
		if (arg.parrent->type == RDHER)
			ret = open(command[0], O_RDWR);
		free (command);// and more
		if (ret > 0)
		{
			close (ret);
			return (0);
		}
		else
			return (1);
	}
	else
	{
		if (arg.parrent->type == RDHER)
			ret = ft_executeherdoc(tree, env);
		if (arg.parrent->type == RDIN)
			ret = ft_executein(tree, env);
		if (arg.parrent->type == RDOUT)
			ret = ft_executeout(tree, env);
		if (arg.parrent->type == RDAPP)
			ret = ft_executeappend(tree, env);
	}
	return (ret);
}

int	ft_execution(char **env, t_tree *tree, t_executenop arg, t_execute *args)
{
	int i;

	i = 0;
	if (tree->type == OR || tree->type == AND)
		arg.root = tree;
	if (tree->type != LIST)
		arg.parrent = tree;
	if (tree->type == OR)
	{
		i = 1;
		args->thisisreturn = i;
	}
	if (tree->type == PIPE && arg.root->type != PIPE)
		arg.root = tree;
	if (tree->type == PIPE && tree->left->type != PIPE)
	{
		args->newpipe = malloc(sizeof(int) * 2);
		pipe(args->newpipe);
		args->oldpipe = NULL;
	}
	if (tree->left)
	{
		arg.pos = 'l';
		i = ft_execution(env, tree->left, arg, args);
		args->thisisreturn = i;
	}
	if (tree->type == AND && i)
			return (i);
	else if (tree->type == OR && !i)
		return (i);
		// it and | or => new root
	if (tree->right)
	{
		arg.pos = 'r';
		i = ft_execution(env, tree->right, arg, args);
		args->thisisreturn = i;
	}
	if (tree->type != PIPE && tree->type != AND && tree->type != OR && tree->type != RDIN && tree->type != RDOUT && tree->type != RDAPP && tree->type != RDHER)
	{
		if (arg.pos != 'p')
		{
			// if (arg.parrent->type == AND)
			// 	return (ft_simplecmd(env, tree));
			// else if (arg.parrent->type == OR)
			// 	return (ft_simplecmd(env, tree));
			if (arg.parrent->type == PIPE)
				ft_execpipes(args, env, tree, arg);
			// else if (arg.parrent->type == LIST)
			// 	return (ft_simplecmd(env, tree));
			else if (!isredirections(arg.parrent->type))
				return (ft_executereds(tree, env, arg));
			else
				return (ft_simplecmd(env, tree));

		}
		else
			return (ft_simplecmd(env, tree));
		// {
		// 	if  if (tree->type == RDAPP || tree->type == RDOUT || tree->type == RDHER || tree->type == RDAPP)
		// 		return (ft_executereds(tree, env));
		// }
		// else if (arg.parrent->type == RDAPP || arg.parrent->type == RDHER
		// 		|| arg.parrent->type || arg.parrent->type == RDOUT)
		// else

	}
	return (i);
}