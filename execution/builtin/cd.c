/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:55:05 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/26 03:26:29 by foulare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

char	**ft_doingcdpwd(char **env, char *oldone, char *tmp, char *var)
{
	int		i;
	int		j;
	char	**de;

	i = 0;
	j = 0;
	while (var[i])
	{
		oldone[i] = var[i];
		i++;
	}
	while (tmp[j])
	{
		oldone[i] = tmp[j];
		i++;
		j++;
	}
	de = ft_malloc(sizeof(char *) * 2);
	if (!de)
		return (NULL);
	de[0] = oldone;
	de[1] = NULL;
	ft_export(de, &env);
	return (de);
}

int	oldpwd(char **env)
{
	char	*oldone;
	char	*var;
	char	*tmp;
	char	**de;

	tmp = ft_getenv(env, "PWD=");
	var = "OLDPWD=";
	if (!tmp)
		return (1);
	oldone = ft_malloc(ft_strlen(tmp) + 8);
	if (!oldone)
		return (1);
	de = ft_doingcdpwd(env, oldone, tmp, var);
	if (!de)
		return (1);
	return (0);
}

int	newpwd(char **env)
{
	char	*newone;
	char	*var;
	char	tmp[PATH_MAX];
	char	**de;

	newone = ft_malloc(PATH_MAX + 5);
	var = "PWD=";
	if (!newone)
		return (1);
	if (!getcwd(tmp, PATH_MAX) && errno == ENOENT)
	{
		perror("minishell: cd: error retrieving current directory: "
			"getcwd: cannot access parent directories");
		return (1);
	}
	de = ft_doingcdpwd(env, newone, tmp, var);
	if (!de)
		return (1);
	return (0);
}

int	cding(char **env)
{
	if (oldpwd(env))
		return (1);
	if (newpwd(env))
		return (1);
	return (0);
}

int	ft_cd(char *dest, char **env)
{
	char	*path;

	if (!dest)
	{
		path = ft_getenv(env, "HOME=");
		if (!path)
		{
			write(2, "HOME not set\n", 13);
			return (1);
		}
		if (chdir(path) == -1 && errno == ENOENT)
		{
			perror("minishell");
			return (1);
		}
		return (cding(env));
	}
	if (chdir (dest) == -1 && errno == ENOENT)
	{
		write (1, "cd: ", 5);
		write (1, dest, ft_strlen(dest));
		write(1, ": No such file or directory\n", 28);
		return (1);
	}
	return (cding(env));
}
