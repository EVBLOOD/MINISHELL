/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 00:40:31 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/25 00:40:34 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

int	ft_nbfiles(void)
{
	struct dirent	*ret;
	DIR				*dir;
	int				i;

	i = 1;
	dir = opendir(".");
	if (!dir)
		return (0);
	while((ret = readdir(dir)) != NULL)
	{
		if ((ret->d_type == DT_DIR || ret->d_type == DT_REG) && ret->d_name[0] != '.')
			i++;
	}
	closedir(dir);
	return (i);
}

int		ft_doublesize(char **names)
{
	int	i;

	i = 0;
	while (names[i])
		i++;
	return (i);
}

char	**ft_returngiven(char **names, char	*rgx)
{
	if (!ft_doublesize(names))
	{
		names = ft_malloc(sizeof(char *) * 2);
		names[0] = rgx;
		names[1] = NULL;
	}
	return (names);
}

char	**ft_simplewild(void)
{
	struct dirent	*ret;
	DIR				*dir;
	int				i;
	char			**names;

	i = -1;
	names = ft_malloc(sizeof(char *) * ft_nbfiles());
	dir = opendir(".");
	if (!dir)
		return(NULL);
	while((ret = readdir(dir)) != NULL)
		if ((ret->d_type == DT_DIR || ret->d_type == DT_REG) && ret->d_name[0] != '.')
			names[++i] = ft_strdup(ret->d_name);
	names[++i] = NULL;
	closedir(dir);
	return (names);
}

int	ft_nbfilestwo(char *pattren)
{
	struct dirent	*ret;
	DIR				*dir;
	int				i;

	i = 1;
	dir = opendir(".");
	if (!dir)
		return (0);
	while((ret = readdir(dir)) != NULL)
	{
		if ((ret->d_type == DT_DIR || ret->d_type == DT_REG) && ret->d_name[0] != '.' && ft_ismatch(ret->d_name, pattren))
			i++;
	}
	closedir(dir);
	return (i);
}

char	**ft_wildrgex(char *pattern)
{
	struct dirent	*ret;
	DIR				*dir;
	int				i;
	char			**names;

	i = -1;
	names = ft_malloc(sizeof(char *) * ft_nbfilestwo(pattern));
	dir = opendir(".");
	if (!dir)
		return(NULL);
	while((ret = readdir(dir)) != NULL)
		if ((ret->d_type == DT_DIR || ret->d_type == DT_REG) && ret->d_name[0] != '.' && ft_ismatch(ret->d_name, pattern))
			names[++i] = ft_strdup(ret->d_name);
	names[++i] = NULL;
	closedir(dir);
	return (names);
}


char	**ft_wildcard_(char *pattern)
{
	char	**names;

	if (ft_strlen(pattern) == 1)
	{
		names = ft_simplewild();
		names = ft_returngiven(names, pattern);
	}
	else
	{
		names = ft_wildrgex(pattern);
		names = ft_returngiven(names, pattern);
	}
	return (names);
}
