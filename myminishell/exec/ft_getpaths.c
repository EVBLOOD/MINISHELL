/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpaths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 01:57:28 by sakllam           #+#    #+#             */
/*   Updated: 2022/03/15 20:07:47 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



int	ft_thereisaslach(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '/')
			return (1);
	}
	return (0);
}

int	ft_checkexistence(char *line)
{
	if (access(line, X_OK))
		return (2);
	if (access(line, F_OK))
		return (1);
	return (0);
}

int	ft_isfile(char *line)
{
	if (ft_checkexistence(line))
	{
		write (1, line, ft_strlen(line));
		if (ft_checkexistence(line) == 1)
		{
			write (1, ": No such file or directory\n", 28);
			return (1);
		}
		else
		{
			write (1, ": Permission denied\n", 20);
			return (1);
		}
	}
	return (0);
}

char *ft_alphajoin(char *line, char *path)
{
	int		i;
	int		j;
	int		x;
	char	*ret;

	ret = (char *)malloc(sizeof(char) * (ft_strlen(line) + ft_strlen(path) + 2));
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


	// i = -1;
	// j = -1;
	// x = ft_strlen(line) + ft_strlen(path) + 1;
	// ret = malloc(sizeof(char) * (x + 1));
	// if (!ret)
	// 	return (NULL);
	// while (path[++i])
	// 	ret[i] = path[i];
	// path[i] = '/';
	// i++;
	// while (line[++j])
	// 	ret[i + j] = line[j];
	// ret[i + j] = '\0';
	return (ret);
}

char	*ft_match(char *splited, char *cmd)
{
	char	*path;

	path = ft_alphajoin(cmd, splited);
	// printf("%s\n", path);
	if (!ft_checkexistence(path))
		return (path);
	free(path);
	return (NULL);
}

char	*ft_searchandconcat(char **splited, char *cmd)
{
	int		i;
	char	*path;

	i = -1;
	// int	j = 0;
	// while (splited[j])
	// 	printf("%s\n", splited[j++]);
	while (splited[++i])
	{
		path = ft_match(splited[i], cmd);
		if (path)
			break;
	}
	return (path);
}

char	*ft_isacmd(char *cmd, t_env *env)
{
	t_env	*node;
	char	**splited;
	char	*path;

	node = ft_getenv(&env, "PATH=");
	if (!node)
		return (NULL);
	splited = ft_split(&(node->value[4]), ':');	
	if (!splited)
		return (NULL);
	path = ft_searchandconcat(splited, cmd);
	free(splited);
	if (!path)
		return (NULL);
	return (path);
}

char	*ft_jccprtone(t_tree *element)
{
	int		i;
	int		x;
	int		y;
	char	*line;

	i = -1;
	x = 0;
	while (element->element[++i])
		x += ft_strlen(element->element[i]);
	line = malloc(x + i + 1);
	if (!line)
		return (NULL);
	i = -1;
	y = -1;
	while (element->element[++i])
	{
		x = -1;
		while (element->element[++i][++x])
			line[++y] = element->element[i][x];
		line[y] = ' ';
	}
	line[y] = '\0';
	return (line);
}

char	*ft_joinandconcat(t_tree *element)
{
	char	*line;

	if (element->type == DQ || element->type == SQ)
		line = ft_jccprtone(element);
	else
		line = ft_strdup(element->element[0]);
	return (line);
}

char	*ft_searchinenv(t_tree *element, t_env *env)
{
	char	*line;
	char	*path;

	line = ft_joinandconcat(element);
	if (!line)
		return (line);
	if (ft_thereisaslach(line))
	{
		if (ft_isfile(line))
			return (NULL);
		return (line);
	}
	path = ft_isacmd(line, env);
	free(line);
	if (!path)
	{
		write(1, line, ft_strlen(line));
		write(1, ": command not found\n", 20);
	}
	return (path);
}