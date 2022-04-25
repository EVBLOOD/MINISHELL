/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:41:53 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/25 01:43:19 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

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

char	*ft_isacmd(char *cmd, char **env)
{
	char	*node;
	char	**splited;
	char	*path;

	node = ft_getenv(env, "PATH=");
	if (!node)
		return (NULL);
	splited = ft_split(&(node[4]), ':');	
	if (!splited)
		return (NULL);
	path = ft_searchandconcat(splited, cmd);
	if (!path)
		return (NULL);
	return (path);
}

int	ft_checkexistence(char *line)
{
	if (access(line, X_OK))
		return (2);
	if (access(line, F_OK))
		return (1);
	return (0);
}

char *ft_alphajoin(char *line, char *path)
{
	int		i;
	int		j;
	int		x;
	char	*ret;

	ret = (char *)ft_malloc(sizeof(char) * (ft_strlen(line) + ft_strlen(path) + 2));
	if (!ret)
		return (NULL);
	i = -1;
	while (path[++i])
		ret[i] = path[i];
	ret[i++] = '/';
	j = -1;
	while (line[++j])
		ret[i++] = line[j];
	ret[i] = '\0';
	return (ret);
}
