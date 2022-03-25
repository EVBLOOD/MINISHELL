/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_variable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 04:15:48 by sakllam           #+#    #+#             */
/*   Updated: 2022/03/16 23:36:24 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getthevalue(t_env *node)
{
	int		i;
	char	*value;

	i = -1;
	while (node->value[++i] && node->value[i] != '=');
	value = ft_strdup(&(node->value[++i]));
	puts(value);
	return (value);
}

char	*ft_getvariable(t_env **env, char *var)
{
	t_env	*node;
	char	*value;

	node = ft_getenv(env, &var[1]);
	if (!node)
		value = ft_strdup("");
	else
		value = ft_getthevalue(node);
	return (value);
}


void check_var(t_env **env, char **value)
{
	int i;
	int j;
	int p;

	i = 0;
	p = 0;
	while (value[i])
	{
		j = 0;
		p = 0;
		while(value[i][j])
		{
			if (value[i][j] == '$')
			{
				p = 1;
				break;
			}
			j++;
		}
		if (p)
		{
			char *str = value[i];
			value[i] = ft_getvariable(env, &value[i][j]);
			// value[i] = str;
			free(str);
			puts(value[i + 1]);
		break;
		}
		i++;
	}
	puts(value[i + 1]);
}