/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clone_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:57:43 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/25 23:27:31 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

int	ft_envsize(char **elements)
{
	int	i;

	i = 0;
	if (!elements)
		return (1);
	while (elements[i])
		i++;
	return (i + 1);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*p;
	
	if (!s)
		return (NULL);
	i = 0;
	p = (char *) ft_malloc(ft_strlen(s) + 1);
	if (!p)
		return (NULL);
	while (s[i])
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strdupb(const char *s)
{
	int		i;
	char	*p;
	
	if (!s)
		return (NULL);
	i = 0;
	p = (char *) malloc(ft_strlen(s) + 1);
	if (!p)
		return (NULL);
	while (s[i])
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int				i;
	unsigned char	*st1;
	unsigned char	*st2;
	
	i = 0;
	st1 = (unsigned char *) s1;
	st2 = (unsigned char *) s2;
	while ((st1[i] || st2[i]) && (unsigned int) i < n)
	{
		if (st1[i] != st2[i])
			return (st1[i] - st2[i]);
		i++;
	}
	return (0);
}

char	**ft_addtoenv(char **env, char *element)
{
	char **newenv;
	int	i;

	i = 0;
	newenv = malloc(sizeof(char *) * (ft_envsize(env) + 1));
	while (env[i])
	{
		newenv[i] = ft_strdup(env[i]);
		i++;
	}
	newenv[i] = ft_strdup(element);
	newenv[i + 1] = NULL;
	i = 0;
	while (env[i])
	{
		free (env[i]);
		i++;
	}
	free(env);
	return (newenv);
}
