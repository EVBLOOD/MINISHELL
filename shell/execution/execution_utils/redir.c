#include "../../mini_shell.h"

int execredir(t_tree *tree, char **env, int fd, int Ptype)
{
	int		ret;
	char	*path;
	pid_t	pid;
	char	**command;

	ret = 1;
	// tree->elements = check_wild(tree->elements);
	command = ft_dealwithlist(tree->elements, env, 0);
	path = ft_isacmd(command[0], env);
	if (path)
	{
		pid = fork();
		if (pid == 0)
		{
			if (Ptype == RDIN)
				dup2 (fd, 0);
			else
				dup2 (fd, 1);
			if (execve(path, command, env) < 0)
			{
				perror("minishell:");
				exit(1);
			}
		}
	}
	else
		printf("minishell: %s:Command not found\n", command[0]);
	ft_free(command);
	return (ret);
}

int	ft_RDIN(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("file");
		return (fd);
	}
	return (fd);
}

int	ft_RDOUT(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 00644);
	if (fd < 0)
	{
		perror("file");
		return (fd);
	}
	return (fd);
}

int	ft_RDAPP(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 00644);
	if (fd < 0)
	{
		perror("file");
		return (fd);
	}
	return (fd);
}

int	ft_RDRfunction(char position, t_tree *tree, char **env, int Ptype, int fd)
{
	int ret;
	char	**command;

	if (position == 'l')
	{
		command = ft_dealwithlist(tree->elements, env, 0);
		if (command[0][0] == '*')
		{
			printf("minishell: *: ambiguous redirect\n");
			return (-1);
		}
		if (Ptype == RDIN)
			return(ft_RDIN(command[0]));
		if (Ptype == RDOUT)
			return(ft_RDOUT(command[0]));
		if (Ptype == RDAPP)
			return(ft_RDAPP(command[0]));
	}
	else
	{
		ret = execredir(tree, env, fd, Ptype);
		ret = ft_getreturn();
		close(fd);
		return(ret);
	}
	return (1);
}