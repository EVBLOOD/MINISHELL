/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 11:44:51 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/23 21:09:11 by foulare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

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
    int len;

    i = -1;
    len = ft_strlen(var);
    while (env[++i])
        if (!ft_strncmp(env[i], var, len) && env[i][len] == '=')
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

int	ft_unset(char ***env, char **cmd)
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
		return (0);
	}
    while (cmd[++i])
	{
        index = vars_exists(cmd[i], *env);
        if (index > -1)
            *env = delete_vars(index, *env);
	}
    return (0);
}
