/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 22:53:25 by sakllam           #+#    #+#             */
/*   Updated: 2022/03/16 16:30:08 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_varvalidatin(int c)
{
	if (!ft_isalpha(c) && !ft_isdigit(c) && c != '_')
		return (0);
	return (1);
}

int	ft_checkvarexp(char *str)
{
	int	ec;
	int	i;

	ec = 1;
	if (str[0] != '_' && !ft_isalpha(str[0]))
		return (-1);
	i = 0;
	while (str[++i])
	{
		if (!ft_varvalidatin(str[i]))
			return (-1);
		if (ec && str[i] == '=')
			return (0);
	}
	return (1);
}

char	*ft_part_one(char *value)
{
	char	*ret;
	int		i;
	int		j;

	i = -1;
	while (value[++i] && value[i] != '=');
	if (value[i] != '=')
		i++;
	ret = malloc(i + 1);
	j = -1;
	while (++j < i)
		ret[j] = value[j];
	if (value[i] != '=')
		ret[j++] = '=';
	ret[j] = '\0';
	return (ret);
}

int	ft_withe_qual(char *value, t_env **env)
{
	char	*spl;
	t_env	*ret;

	spl = ft_part_one(value);
	ret = ft_getenv(env, spl);
	if (ret)
	{
		free(ret->value);
		ret->value = ft_strdup(value);
		if (!ret->value)
			return (1);
	}
	else
	{
		ret = malloc(sizeof(t_env));
		if (!ret)
			return(1);
		ret->value = ft_strdup(value);
		if (!ret->value)
			return (1);
		ft_lstadd_backenv(env, ret);
	}
	free(spl);
	return (0);
}


int	ft_without_equal(char *value, t_env **env)
{
	char	*spl;
	t_env	*ret;

	spl = ft_part_one(value);
	ret = ft_getenv(env, spl);
	if (!ret)
	{
		ret = malloc(sizeof(t_env));
		if (!ret)
			return(1);
		ret->value = ft_strdup(spl);
		if (!ret->value)
			return (1);
		ft_lstadd_backenv(env, ret);
	}
	free(spl);
	return (0);
}



int	ft_export(t_env **env, char *value)
{
	if (ft_checkvarexp(value) == -1)
	{
		write (1, "export: `", 9);
		write (1, value, ft_strlen(value));
		write (1, "': not a valid identifier\n", 26);
		return (1);
	}
	else if (!ft_checkvarexp(value))
	{
		if (ft_withe_qual(value, env))
			return (1);
	}
	else
	{
		if (ft_without_equal(value, env))
			return (1);
	}
	return (0);
}