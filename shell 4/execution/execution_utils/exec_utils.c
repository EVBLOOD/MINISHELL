#include "../../mini_shell.h"
int	ft_getreturn(void)
{
	int	ret;

	waitpid(-1, &ret, 0);
	return (ret);
}

char	*ft_getenv(char **env, char *val)
{
	int		i;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PATH=", ft_strlen(val)))
			return (env[i]);
	}
	return (NULL);
}

pid_t	simple_cmd(char *path, char **cmd, char **env)
{
	pid_t	id;
	id = fork();
	if (id == 0)
	{
		if (execve(path, cmd, env) < 0)
		{
			perror("minishell:");
			exit(1);
		}
	}
	return (id);
}

char	*ft_isacmd(char *cmd, char **env)
{
	char	*node;
	char	**splited;
	char	*path;

	node = ft_getenv(env, "PATH=");
	puts(node);
	if (!node)
		return (NULL);
	splited = ft_split(&(node[4]), ':');	
	if (!splited)
		return (NULL);
	path = ft_searchandconcat(splited, cmd);
	free(splited);
	if (!path)
		return (NULL);
	return (path);
}