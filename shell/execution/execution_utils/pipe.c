#include "../../mini_shell.h"


void	main_pipe(int *wr_fd)
{
	close(wr_fd[1]);
	dup2(wr_fd[0], 0);
}

int execpipe(t_tree *tree, char **env, int pip[2])
{
	int		ret;
	char	*path;
	pid_t	pid;
	char	**command;
	char	*buf;

	ret = 1;
	tree->elements = check_wild(tree->elements);
	command = ft_dealwithlist(tree->elements, env);
	path = ft_isacmd(command[0], env);
	if (path)
	{
		pid = fork();
		if (pid == 0)
		{
			main_pipe(pip);
			if (execve(path, command, env) < 0)
			{
				perror("minishell:");
				exit(1);
			}
		}
	}
	else
		printf("minishell: %s:Command not found\n", command[0]);
	return (ret);
}

pid_t	midel_first_partpipe(int *wr_fd, t_tree *tree, char **env)
{
	char	*path;
	pid_t	id;
	char	**command;

	tree->elements = check_wild(tree->elements);
	command = ft_dealwithlist(tree->elements, env);
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

int	ft_PIPEfunction(char position, t_tree *tree, char **env, int lastpipe, int pip[2])
{
	pid_t	ret;
	char	**envc;

	if (position == 'l')
	{
		ret = midel_first_partpipe(pip, tree, env);
	}
	else
	{
		execpipe(tree, env, pip);
	}
	return (ret);
}

