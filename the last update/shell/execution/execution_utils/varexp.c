/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varexp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 03:38:03 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/05 17:01:23 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

// int	countspacesofvar(char *var)
// {
// 	int	i;
// 	int	count;
// 	char	*str;

// 	// str  = ft_strtrim(var, " \t\n\v\f\r");
// 	str = var;
// 	i = -1;
// 	count = 0;
// 	while (str[++i])
// 	{
// 		if (ft_strchr(str[i], " \t\n\v\f\r"))
// 		{
// 			count++;
// 			while (str[++i] && ft_strchr(str[i], " \t\n\v\f\r"));
// 			if (!str[i])
// 				break;
// 			i--;
// 		}
// 	}
// 	free(str);
// 	return (count);
// }

// char	**ft_splitvar(char *splited)
// {
// 	int		i;
// 	int		j;
// 	int		x;
// 	char	**ret;

// 	i = -1;
// 	x = -1;
// 	j = 0;
// 	ret = malloc(sizeof(char *) * (countspacesofvar(splited) + 1));
// 	while (splited[++i])
// 	{
// 		if (ft_strchr(splited[i], " \t\n\v\f\r") || !splited[i + 1])
// 		{
// 			if (!splited[i + 1])
// 				(j++, i++);
// 			ret[++x] = ft_substr(splited, i - j, j);
// 			j = 0;
// 			while (splited[++i] && ft_strchr(splited[i], " \t\n\v\f\r"));
// 			if (!splited[i])
// 				break;
// 		}
// 		j++;
// 	}
// 	ret[++x] = NULL;
// 	x = 0;
// 	return (ret);
// }

int	countspacesofvar(char *var)
{
	int	i;
	int	count;
	char	*str;

	str = var;
	i = -1;
	count = 0;
	while (str[++i])
	{
		if (ft_strchr(str[i], " \t\n\v\f\r"))
		{
			count++;
			while (str[++i] && ft_strchr(str[i], " \t\n\v\f\r"));
			if (!str[i])
				break;
			i--;
		}
		if (!str[i + 1])
			count++;
	}
	return (count);
}

char	**ft_splitvar(char *splited)
{
	char	**ret;
	int		i;
	int		nbr;
	int		dbl_i;

	i = 0;
	nbr = 0;
	dbl_i = 0;
	ret = malloc(sizeof(char *) * (countspacesofvar(splited) * 2));
	while (splited[i])
	{
		if (ft_strchr(splited[i], " \t\n\v\f\r"))
		{
			if (nbr > 0)
			{
				ret[dbl_i] = ft_substr(splited, (i - 1) - nbr, nbr);
				dbl_i++;
			}
			ret[dbl_i] = ft_strdup(" ");
			dbl_i++;
			while (splited[i] && ft_strchr(splited[i], " \t\n\v\f\r"))
			{
				i++;
			}
			if (!splited[i])
				break;
			i--;
			nbr = -1;
		}
		if (!splited[i + 1])
		{
			(nbr++, i++);
			ret[dbl_i] = ft_substr(splited, i - nbr, nbr);
			(dbl_i++, i--);
		}
		nbr++;
		i++;
	}
	ret[dbl_i] = NULL;
	return (ret);
}

char	**ft_expandvariables(t_list *list, char **env)
{
	int		i;
	char	**val;
	int		found;
	char	*var;

	i = -1;
	found = 0;
	while (env[++i])
	{
		var = &list->splited[1];
		if (!ft_strncmp(env[i], var, ft_strlen(var)) && env[i][ft_strlen(var)] == '=')
		{
			found = 1;
			break;
		}
	}
	free(list->splited);
	if (!found)
		list->splited = ft_strdup("");
	else
		list->splited = ft_strdup(&env[i][ft_strlen(var) + 1]);
	return (ft_splitvar(list->splited));
}