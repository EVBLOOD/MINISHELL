#include "main.h"

// si return 255 => erreur; sinon si 0 success; sinon 1 c'est pas builtins passer a execve pour executer;
int exec_buitins(char **cmd, char **env, int status)
{
	if (!ft_strncmp(cmd[0], "echo", ft_strlen(cmd[0])))
        return(ft_echo(&cmd[1]));
	if (!ft_strncmp(cmd[0], "env", ft_strlen(cmd[0])))
        return(ft_env(env));
	if (!ft_strncmp(cmd[0], "pwd", ft_strlen(cmd[0])))
        return(ft_pwd());
	if (!ft_strncmp(cmd[0], "cd", ft_strlen(cmd[0])))
	{
        if (ft_cd(cmd[1]))
            return (255);
        else
            return (0);
    }
	if (!ft_strncmp(cmd[0], "unset", ft_strlen(cmd[0])))
	{
        env = ft_unset (env, &cmd[1]);
        if (!env)
            return (255);
        else
            return (0);
    }
	if (!ft_strncmp(cmd[0], "exit", ft_strlen(cmd[0])))
        if (ft_exit (&cmd[1], status))
            return (255);
	if (!ft_strncmp(cmd[0], "export", ft_strlen(cmd[0])))
    {
        env = ft_export (&cmd[1], env);
        if (!env)
            return (255);
        else
            return (0);
    }
	return (1);
}