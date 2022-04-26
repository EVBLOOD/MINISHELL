/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 04:44:29 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/26 04:52:23 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

char	**vars_notexist(char *var, char ***env)
{
	int		i;
	char	**tmp;

	i = 0;
	while ((*env)[i])
		i++;
	tmp = malloc(sizeof(char *) * (i + 2));
	if (!tmp)
		return (NULL);
	i = 0;
	while ((*env)[i])
	{
		tmp[i] = ft_strdupb((*env)[i]);
		free((*env)[i]);
		i++;
	}
	free (*env);
	tmp[i] = ft_strdupb(var);
	tmp[i + 1] = NULL;
	return (tmp);
}

int	vars_exist(char *var, char **env, int index)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, index))
			return (i);
		i++;
	}
	return (-1);
}

int	verifyname(char *name)
{
	int	i;

	if (name[0] != '_' && !ft_isalpha(name[0]))
		return (-1);
	i = 1;
	while (name[i] && name[i] != '=')
	{
		if (!ft_isalpha(name[i])
			&& !ft_isdigit(name[i]) && name[i] != '_')
			return (-1);
		i++;
	}
	if (name[i] != '=')
		return (-2);
	return (i);
}

int	desplayerror(char *cmd)
{
	write (2, "minishell: export: ", 19);
	write (2, cmd, ft_strlen(cmd));
	write(2, ": not a valid identifier\n", 25);
	return (1);
}

int	ft_export(char **cmd, char ***env)
{
	int		equal;
	int		line;
	int		i;

	i = 0;
	if (!cmd[i])
		display(*env);
	while (cmd[i])
	{
		equal = verifyname(cmd[i]);
		if (equal != -1)
		{
			line = vars_exist(cmd[i], *env, equal);
			ft_cleanexport(line, env, cmd[i]);
		}
		else
			desplayerror(cmd[i]);
		i++;
	}
	return (0);
}
