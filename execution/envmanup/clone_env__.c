/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clone_env__.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 02:02:12 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/26 02:29:34 by foulare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

void	ft_shlvlnorm(int nb, char *response, char *char_nb)
{
	int	i;

	i = 0;
	while (char_nb[i])
	{
		response[nb] = char_nb[i];
		nb++;
		i++;
	}
	response[nb] = '\0';
}

void	ft_addshlvl(char **env, int x)
{
	int		i;
	int		nb;
	char	*char_nb;
	char	*response;

	i = -1;
	while ((*env)[++i])
		if ((*env)[i] == '=')
			break ;
	i++;
	nb = ft_atoi(&(*env)[i]) + x;
	char_nb = ft_itoab(nb);
	response = malloc(ft_strlen(char_nb) + i + 1);
	nb = -1;
	while (++nb < i)
		response[nb] = (*env)[nb];
	ft_shlvlnorm(nb, response, char_nb);
	free((*env));
	free(char_nb);
	(*env) = response;
}

void	ft_shlvl(char ***env, int x)
{
	int	i;
	int	found;

	i = -1;
	found = 0;
	while ((*env)[++i])
	{
		if (!ft_strncmp((*env)[i], "SHLVL=", 6))
		{
			found = 1;
			break ;
		}
	}
	if (!found)
		*env = ft_addtoenv((*env), "SHLVL=1");
	else
		ft_addshlvl(&((*env)[i]), x);
}

char	**ft_cloneenv(char **env)
{
	char	**newenv;
	int		i;
	int		len;

	i = 0;
	len = ft_envsize(env);
	newenv = malloc(sizeof(char *) * len);
	while (env && env[i])
	{
		newenv[i] = ft_strdupb(env[i]);
		i++;
	}
	newenv[i] = NULL;
	ft_shlvl(&newenv, 1);
	return (newenv);
}
