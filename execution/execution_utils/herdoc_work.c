/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_work.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 04:56:17 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/26 04:56:20 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

char	*herexchange(char *var, char **env)
{
	int		i;
	int		found;
	char	*tmp;

	i = -1;
	found = 0;
	if (!ft_strcmp(var, "?"))
	{
		tmp = ft_strdup(ft_itoa(g_exec.returnvalue));
		return (tmp);
	}
	while (env[++i])
	{
		if (!ft_strncmp(env[i], var, ft_strlen(var))
			&& env[i][ft_strlen(var)] == '=')
		{
			found = 1;
			break ;
		}
	}
	if (!found)
		tmp = ft_strdup("");
	else
		tmp = ft_strdup(&env[i][ft_strlen(var) + 1]);
	return (tmp);
}

void	ft_readandread(int fd, int ret, char *c, char *var)
{
	int	i;

	i = 0;
	while (ret > 0 && !ft_varvalidating(*c))
	{
		var[i] = *c;
		ret = read(fd, c, 1);
		i++;
	}
	var[i] = '\0';
}

void	getvar(int her, int fd, char **env, char *c)
{
	char	*value;
	int		ret;
	char	var[1000000];

	var[0] = '\0';
	ret = read(fd, c, 1);
	if (ft_isdigit(*c) || *c == '?')
	{
		var[0] = *c;
		var[1] = '\0';
	}
	else
		ft_readandread(fd, ret, c, var);
	value = herexchange(var, env);
	if (!var[0])
		write (her, "$", 1);
	else
		write (her, value, ft_strlen(value));
}

char	*herdoc(int fd, char **env, char *name)
{
	char	*newname;
	int		her;
	int		ret;
	char	c;

	newname = create_filename(name);
	her = open(newname, O_CREAT | O_WRONLY | O_TRUNC, 00644);
	if (her < 0)
		return (NULL);
	ret = read(fd, &c, 1);
	while (ret > 0)
	{
		while (c == '$')
			getvar(her, fd, env, &c);
		write (her, &c, 1);
		ret = read(fd, &c, 1);
	}
	close (her);
	return (newname);
}
