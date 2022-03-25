#include "../minishell.h"



int check_builtins(char **cmd, t_env **env)
{
	if (!cmd[0][0])
		return(-1);
	if (!ft_strncmp(cmd[0], "echo", ft_strlen(cmd[0])))
		return(ft_echo(&cmd[1]));
	if (!ft_strncmp(cmd[0], "env", ft_strlen(cmd[0])))
		return(ft_env(env));
	if (!ft_strncmp(cmd[0], "pwd", ft_strlen(cmd[0])))
		return(ft_pwd());
	if (!ft_strncmp(cmd[0], "cd", ft_strlen(cmd[0])))
	{
		if (ft_cd(cmd[1]))
			return (-1);
	}
	if (!ft_strncmp(cmd[0], "unset", ft_strlen(cmd[0])))
		return(ft_unset(env, cmd[0]));
	if (!ft_strncmp(cmd[0], "exit", ft_strlen(cmd[0])))
		ft_exit();
	// if (!ft_strncmp(cmd[0], "exit", ft_strlen(cmd[0])))
	// 	return
	return (1);
}