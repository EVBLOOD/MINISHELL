/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 22:53:25 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/23 21:07:50 by foulare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

#include "../../mini_shell.h"

int vars_equal(char *var)
{
        int i;

        i = -1;
        while (var[++i])
                if (var[i] == '=')
                        return (i);
        return (0);
}

char **vars_notexist(char *var, char **env)
{
        int     i;
        char    **temp;

    i = -1;
    while (env[++i]);
        temp = env;
        env = malloc(sizeof(char *) * (i + 2));
        if (!env)
                return (0);
        i = -1;
        while (temp[++i])
                env[i] = ft_strdup(temp[i]);
        env[i++] = ft_strdup(var);
        env[i] = NULL;
        //free temp;
        return (env);
}

void displayall(char **env)
{
        int i;

        i = -1;
        while (env[++i])
                printf ("declare -x %s\n", env[i]);
}

int vars_exist(char *var, char **env, int index)
{
        int i;

        i = -1;
        while (env[++i])
        {
                if (!ft_strncmp(env[i], var, index) && env[i][index] == '=')
                {
                        free(env[i]);
                        env[i] = ft_strdup(var);
                        return (1);
                }
        }
        return (0);
}

int check_error(char **str)
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

int     ft_export(char **cmd, char ***env)
{
        int err;
        int i;

        if (cmd[1] == NULL)
                displayall(*env);
        else
        {
                err = check_error(&cmd[1]);
                if (err > -1)
                {
                        write (1, "minishell: export: ", 19);
                        write (1, cmd[err], ft_strlen(cmd[err]));
                        write(1, ": not a valid identifier\n", 25);
                        return (1);
                }
                i = 0;
                while (cmd[++i])
                {
                        err = vars_equal(cmd[i]);
                        if (err)
                        {
                                err = vars_exist(cmd[i], *env, err);
                                if (!err)
                                        *env = vars_notexist(cmd[i], *env);
                        }
                }
        }
        return (0);
}
