/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 13:55:00 by sakllam           #+#    #+#             */
/*   Updated: 2022/03/27 22:56:43 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

int	countspacesofvar(char *var)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (var[++i])
	{
		if (ft_strchr(var[i], " \t\n\v\f\r"))
		{
			count++;
			while (var[++i] && ft_strchr(var[i], " \t\n\v\f\r"));
			if (!var[i])
				break;
			i--;
		}
	}
	return (count);
}

int	ft_expandvariables(t_list *list, char **env)
{
	int		i;
	int		count;
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
		list->splited = ft_strdup(&env[i][6]);
	i = -1;
	count = 0;
	var = list->splited;
	list->splited = ft_strtrim(list->splited, " \t\n\v\f\r");
	free(var);
	return (countspacesofvar(list->splited));
}

void	ft_expandvariablesdq(char **var, char **env)
{
	int	i;
	int	found;

	i = -1;
	found = 0;
	while (env[++i])
		if (!ft_strncmp(env[i], *var, ft_strlen(*var)) && env[i][ft_strlen(*var)] == '=')
		{
			found = 1;
			break;
		}
	free(*var);
	if (!found)
		*var = ft_strdup("");
	else
		*var = ft_strdup(&env[i][6]);
}

void	ft_expand_sq(t_list *list)
{
	int		i;
	char	*str;

	str = malloc(ft_strlen(list->splited) - 1);
	i = 0;
	while (list->splited[++i] != 39)
		str[i - 1] = list->splited[i];
	str[i - 1] = '\0';
	free(list->splited);
	list->splited = str;
}

// ft_variabledq(c)

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*p;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s + start) < len)
		p = (char *) malloc((ft_strlen(s + start) + 1) * sizeof(char));
	else
		p = (char *) malloc(((int) len + 1) * sizeof(char));
	if (!p)
		return (NULL);
	while (i < (int) len && s[i + start] && !(start >= ft_strlen(s)))
	{
		p[i] = s[i + start];
		i++;
	}
	p[i] = '\0';
	return (p);
}

int	ft_expand_dqcount(t_list *list, char **env)
{
	int		i;
	int		j;
	int		count;
	char	*var;

	i = -1;
	count = 0;
	while (list->splited[++i])
	{
		if (ft_strchr(list->splited[i], "$"))
		{
			j = 2;
			if (ft_isdigit(list->splited[i + 1]))
				var = ft_substr(list->splited, i + 1, 1);
			else
			{
				j = 1;
				while (list->splited[i + j] && !ft_varvalidating(list->splited[i + j]))
					j++;
				var = ft_substr(list->splited, i + 1, j - 1);
			}
			ft_expandvariablesdq(&var, env);
			if (j == 1)
				count += 1;
			else
				count += ft_strlen(var);
			free(var);
			i += j - 1;
		}
		else
			count++;
	}
	return (count - 1);
}

void	ft_expand_dq(t_list *list, char **env)
{
	char	*var;
	char	*result;
	int		i;
	int		j;
	int		index;

	result = malloc(ft_expand_dqcount(list, env));
	i = 0;
	index = -1;
	while (list->splited[++i])
	{
		if (ft_strchr(list->splited[i], "$"))
		{
			j = 2;
			if (ft_isdigit(list->splited[i + 1]))
				var = ft_substr(list->splited, i + 1, 1);
			else
			{
				j = 1;
				while (list->splited[i + j] && !ft_varvalidating(list->splited[i + j]))
					j++;
				var = ft_substr(list->splited, i + 1, j - 1);
			}
			ft_expandvariablesdq(&var, env);
			i += j - 1;
			if (j == 1)
				result[++index] = list->splited[i];
			else
			{
				j = -1;
				while (var[++j])
					result[++index] = var[j];
			}
			free(var);
		}
		else
			result[++index] = list->splited[i];
	}
	result[index] = '\0';
	free(list->splited);
	list->splited = result;
}

int	ft_spacevar(t_list *element)
{
	char	*str;

	if (element->TYPE != VARIABLE)
		return (1);
	str = ft_strtrim(element->splited, " \t\n\v\f\r");
	if (!ft_strlen(str))
	{
		free(str);
		return (0);
	}
	return (1);
}

int	ft_countwildexpantion(void)
{
	char	**files;
	int		i;

	i = 0;
	files = ft_simplewild();
	while (files[i])
	{
		free(files[i]);
		i++;
	}
	free(files);
	return (i);
}

// void	ft_expandsimplewild(void)
// {
// 	char	**files;

// 	files = ft_simplewild();
// 	return (files);
// }

char	**ft_splitvar(char *splited)
{
	int		i;
	int		j;
	int		x;
	char	**ret;

	i = -1;
	x = -1;
	j = 0;
	ret = malloc(sizeof(char *) * (countspacesofvar(splited) + 1));
	while (splited[++i])
	{
		if (ft_strchr(splited[i], " \t\n\v\f\r"))
		{
			ret[++x] = ft_substr(splited, x - j, j);
			while (splited[++i] && ft_strchr(splited[i], " \t\n\v\f\r"));
			if (!splited[i])
				break;
			j = 0;
		}
		j++;
	}
	ret[++x] = NULL;
	return (ret);
}


char	**ft_dealwithlist(t_list **list, char **env, int red)
{
	int		i;
	int		x;
	int		count;
	char	*str;
	char	**args;
	char	**files;

	i = -1;
	count = 1;
	
	while (list[++i])
	{
		// printf("%d\n", list[i]->TYPE);
		if (list[i]->TYPE == VARIABLE)
			count += ft_expandvariables(list[i], env);
		if (list[i]->TYPE == WILD)
		{
			count += ft_countwildexpantion();
			while (list[i] && list[i]->TYPE == WILD)
				i++;
			i--;
		}
		if (list[i]->TYPE == DQ)
			ft_expand_dq(list[i], env);
		if (list[i]->TYPE == SQ)
			ft_expand_sq(list[i]);
		if (list[i]->TYPE == SPACES || !ft_spacevar(list[i]))
		{
			while (list[++i] && !ft_spacevar(list[i]));
			i--;
			count++;
			if (red)
				break;
		}
	}
	args = malloc(sizeof(char *) * (count + 1));
	i = -1;
	count = -1;
	str = ft_strdup("");
	while (list[++i])
	{
		if (list[i]->TYPE != VARIABLE && list[i]->TYPE != WILD && list[i]->TYPE != SPACES && ft_spacevar(list[i]))
			str = ft_strjoin(str, list[i]->splited);
		if (list[i]->TYPE == WILD)
		{
			x = -1;
			files = ft_simplewild();
			while (files[++x])
				args[++count] = files[x];
			while (list[i] && list[i]->TYPE == WILD)
				i++;
			if (!list[i])
				break ;
			i--;
		}
		if (list[i]->TYPE == VARIABLE)
		{
			x = -1;
			files = ft_splitvar(list[i]->splited);
			while (files[++i])
			{
				args[++count] = ft_strjoin(str, files[++i]);
				str = 
			}
		}
		if ((i || !list[i + 1]) && (list[i]->TYPE == SPACES || !list[i + 1]
			|| (*str && !ft_spacevar(list[i]))))
		{
			args[++count] = str;
			str = ft_strdup("");
			if (red)
				break;
		}
	}
	free(str);	
	args[++count] = NULL;
	return (args);
}
