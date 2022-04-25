/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:22:58 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/22 11:55:15 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	ft_getreturn(pid_t id)
{
	int	ret;

	waitpid(id, &ret, 0);
	return (ret);
}

int	ft_statushundling(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else if (WIFSTOPPED(status))
		return (128 + WSTOPSIG(status));
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	ft_isbuiltin(char *command)
{
	if (!ft_strcmp(command, "echo"))
		return (1);
	if (!ft_strcmp(command, "env"))
		return (1);
	if (!ft_strcmp(command, "pwd"))
		return (1);
	if (!ft_strcmp(command, "cd"))
		return (1);
	if (!ft_strcmp(command, "unset"))
		return (1);
	if (!ft_strcmp(command, "exit"))
		return (1);
	if (!ft_strcmp(command, "export"))
		return (1);
	return (0);
}

int	ft_executebuiledin(char **command, char **env)
{
	if (!ft_strcmp(command[0], "echo"))
		return (ft_echo(command));
	if (!ft_strcmp(command[0], "env"))
		return (ft_env(env));
	if (!ft_strcmp(command[0], "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(command[0], "cd"))
		return (ft_cd(command[1]));
	if (!ft_strcmp(command[0], "unset"))
		return (ft_unset(&env, command));
	if (!ft_strcmp(command[0], "exit"))
		return (ft_exit(&command[1]));
	if (!ft_strcmp(command[0], "export"))
		return (ft_export(command, &env));
	return (returnvalue);
}

int	ft_simplecmd(char **env, t_tree *tree) //build in + $?
{
	pid_t	id;
	char	**command;
	char	*path;
	int		status;

	command = ft_dealwithlist(tree->elements, env, 0);
	if (ft_isbuiltin(command[0]))
		return (ft_executebuiledin(command, env));
	if (!ft_strchr(47, command[0]))
		path = ft_isacmd(command[0], env);
	else
		path =  command[0];
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
	status = ft_getreturn(id);
	returnvalue = ft_statushundling(status);
	return (ft_getreturn(id));
}


int	ft_nocommand(char *line)
{
	write(2, line, ft_strlen(line));
	write(2, ": command not found\n", 20);
	return (127);
}

int	ft_sizetablered(t_list *redirection)
{
	int	i;

	i = 0;
	while (redirection)
	{
		i++;
		redirection = redirection->next;
	}
	return (i + 1);
}

t_list	**ft_copycolly(t_list *redirection)
{
	t_list	**elm;
	int		i;

	elm = malloc(ft_sizetablered(redirection) * sizeof(t_list *));
	i = 0;
	while (redirection)
	{
		elm[i] = redirection;
		i++;
		redirection = redirection->next;
	}
	elm[i] = NULL;
	return (elm);
}

int	andfunction(t_tree *tree, char **env)
{
	run(tree->left, env);
	if (returnvalue == 0)
		return (run(tree->right, env));
	return (returnvalue); 
}

int	orfunction(t_tree *tree, char **env)
{
	int	ret;
	run(tree->left, env);
	if (returnvalue != 0)
		return (run(tree->right, env));
	return (returnvalue); 
}

void	leftpipefunction(t_tree *tree, char **env, int *pfd)
{
	int	ret;

	if (pipe(pfd) == -1)
	{
		returnvalue = 1;
		exit(1);
	}
	ret = fork();
	if (ret == -1)
	{
		returnvalue = 1;
		exit(1);
	}
	else if (ret == 0)
	{
		close(STDOUT_FILENO);
		dup2(pfd[OUT], STDOUT_FILENO);
		close(pfd[IN]);
		close(pfd[OUT]);
		run(tree->left, env);
		exit(0);
	}
}

int	rightpipefunction(t_tree *tree, char **env, int *pfd)
{
	int	right_pid;
	int	status;

	right_pid = fork();
	if (right_pid == -1)
	{
		returnvalue = 1;
		exit(1);
	}
	else if (right_pid == 0)
	{
		close(STDIN_FILENO);
		dup2(pfd[IN], STDIN_FILENO);
		close(pfd[OUT]);
		close(pfd[IN]);
		run(tree->right, env);
		exit(0);
	}
	close(pfd[0]);
	close(pfd[1]);
	if (wait(&status) == right_pid)
		returnvalue = ft_statushundling(status);
	if (wait(&status) == right_pid)
		returnvalue = ft_statushundling(status);
	return (returnvalue);
}

void	ft_apndredirections(t_tree *tree, char **env)
{
	char	**filename;
	int		fd;
	filename = ft_dealwithlist(ft_copycolly(tree->redirections), env, 1);
	if (!filename[0] || filename[1])
	{
		write(2, "bash : ambiguous redirect\n", 26);
		returnvalue = 1;
		return ;
	}
	fd = open(filename[0], O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd < 0)
	{
		returnvalue = 1;
		return ;
	}
	close(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	run(tree->left, env);
	run(tree->right, env);
}

void	redirectionherdoc(t_tree *tree, char **env) // expend
{
	char	**filename;
	int		fd;

	fd = open(tree->elements[0]->splited, O_RDONLY);
	if (fd < 0)
	{
		returnvalue = 1;
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

void	redirectionsin(t_tree *tree, char **env)
{
	char	**filename;
	int		fd;

	filename = ft_dealwithlist(ft_copycolly(tree->redirections), env, 1);
	if (!filename[0] || filename[1])
	{
		write(2, "bash : ambiguous redirect\n", 26);
		returnvalue = 1;
		return ;
	}
	fd = open(filename[0], O_RDONLY);
	if (fd < 0)
	{
		returnvalue = 1;
		return ;
	}
	close(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fd);
	run(tree->left, env);
	run(tree->right, env);
}

void	redirectionsout(t_tree *tree, char **env)
{
	char	**filename;
	int		fd;

	filename = ft_dealwithlist(ft_copycolly(tree->redirections), env, 1);
	if (!filename[0] || filename[1])
	{
		write(2, "bash : ambiguous redirect\n", 26);
		returnvalue = 1;
		return ;
	}
	fd = open(filename[0], O_RDWR | O_CREAT | O_TRUNC, 0644);;
	if (fd < 0)
	{
		returnvalue = 1;
		return ;
	}
	close(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	if (tree->left)
		run(tree->left, env);
	if (tree->right)
		run(tree->right, env);
}

int	redirectionsfunction(t_tree *tree, char **env)
{
	if (tree->type == RDAPP)
		ft_apndredirections(tree, env);
	if (tree->type == RDHER)
		redirectionherdoc(tree, env);
	if (tree->type == RDIN)
		redirectionsin(tree, env);
	if (tree->type == RDOUT)
		redirectionsout(tree, env);
	return (returnvalue);
}

int	run(t_tree *tree, char **env)
{
	int	ret;
	int	pfd[2];
	int	right_pid;
	int	status;
	int	exit_st;
	char	**filename;

	if (!tree)
		return 0;
	if (tree->type == LIST)
		return (ft_simplecmd(env, tree));
	if (tree->type == AND)
		return (andfunction(tree, env));
	if (tree->type == OR)
		return (orfunction(tree, env));
	if (tree->type == PIPE)
	{
		leftpipefunction(tree, env, pfd);
		return (rightpipefunction(tree, env, pfd));
	}
	if (!isredirections(tree->type))
		return (redirectionsfunction(tree, env));
	return (0);
}
