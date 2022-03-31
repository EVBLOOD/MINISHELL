/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 22:51:01 by sakllam           #+#    #+#             */
/*   Updated: 2022/03/16 16:17:33 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "main.h"

char *ft_concat(char *s1, char *s2)
{
	char *ret;
	int i;
	int y;

	ret = malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));
	if (!ret)
		return (0);
	i = -1;
	y = -1;
	while (s1[++i])
		ret[i] = s1[i];
	while (s2[++y])
		ret[i + y] = s2[y];
	ret[i + y] = 0;
	return (ret);
}

int	ft_cd(char *dest)
{
	char *user;
	char *path;

	if (!dest)
	{
		user = getenv("USER");
		path = ft_concat("/Users/", user);
		if (chdir(path))
			perror("minishell");
		free(path);
		return (0);
	}
	if (chdir (dest))
	{
		write (1, "cd: ", 5);
		write (1, dest, strlen(dest));
		write(1, ": No such file or directory\n", 28);
		return (1);
	}
	return (0);
}