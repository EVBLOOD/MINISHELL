#include "main.h"


char **delete_vars(int index, char **env)
{
    char **ret;
    int i;

    i = -1;
    while (env[++i]);
    ret = malloc(sizeof(char *) * (i));
    if (!ret)
        return (0);
    i = -1;
    while (++i < index)
        ret[i] = strdup(env[i]);
    while (env[++i])
        ret[i - 1] = strdup(env[i]);
    ret[i - 1] = NULL;
    //free env;
    return (ret);
}

int vars_exists(char *var, char **env)
{
    int i;

    i = -1;
    while (env[++i])
        if (!ft_strncmp(env[i], var, ft_strlen(var)))
            return (i);
    return (-1);
}

int check_errors(char **str)
{
	int i;
	int y;

	i = -1;
	while (str[++i])
	{
		y = -1;
		if (!ft_isalpha(str[i][0]))
			return (i);
		while (str[i][++y])
			if (!ft_isalnum(str[i][y]) && str[i][y] != '=')
				return (i);
	}
	return(-1);
}

char **ft_unset(char **env, char **cmd)
{
    int i;
    int index;
    int err;

    i = -1;
    err = check_errors(cmd);
	if (err > -1)
	{
		write (1, "minishell: export: ", 19);
		write (1, cmd[err], ft_strlen(cmd[err]));
		write(1, ": not a valid identifier\n", 25);
		return (env);
	}
    while (cmd[++i])
	{
        index = vars_exists(cmd[i], env);
        if (index > -1)
            env = delete_vars(index, env);
	}
    return (env);
}