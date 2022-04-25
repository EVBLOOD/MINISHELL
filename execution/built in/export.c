/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:57:02 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/25 22:38:46 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

void free_built(char **str)
{
    int i;

    i = -1;
    while (str[++i])
        free(str[i]);
    free(str);
}

char    **dupplic(char **env)
{
    char **str;
    int len;
    int i;

    len = -1;

    while (env[++len]);
    str = ft_malloc(sizeof(char **) * len + 1);
    if (!str)
        return (0);
    i = -1;
    while (env[++i])
        str[i] = ft_strdup(env[i]);
    str[i] = NULL;
    return (str);
}

void display(char **env)
{
    char **str;
    int     i;
    int     y;
    char *temp;

    str = dupplic(env);
    i = -1;
    while (str[++i])
    {
        y = i + 1;
        while (str[y])
        {
            if (ft_strcmp(str[i], str[y]) > 0)
            {
                temp = str[y];
                str[y] = str[i];
                str[i] = temp;
            }
            y++;
        }
    }
    i = -1;
    while (str[++i])
        printf ("declare -x: %s\n", str[i]);
}

char **vars_notexist(char *var, char ***env)
{
	int 	i;
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

int vars_exist(char *var, char **env, int index)
{
	int i;

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
		if (!ft_isalpha(name[i]) && 
			!ft_isdigit(name[i]) && name[i] != '_')
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
	int 	i;
	char	*tmp;

	i = 0;
	if (!cmd[i])
		display(*env);
	while (cmd[i])
	{
		equal = verifyname(cmd[i]);
		if (equal != -1)
		{
			line = vars_exist(cmd[i], *env, equal);
			if (line != -1)
			{
				tmp = (*env)[line];
				(*env)[line] = ft_strdupb(cmd[i]);
				free(tmp);
			}
			else
				*env = vars_notexist(cmd[i], env);
		}
		else
			desplayerror(cmd[i]);
		i++;
	}
	return (0);
}