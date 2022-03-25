/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 18:45:09 by sakllam           #+#    #+#             */
/*   Updated: 2022/03/16 18:36:14 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


t_env	*ft_getenv(t_env **env, char *val)
{
	t_env	*envtmp;

	envtmp = *env;
	while (envtmp)
	{
		if (!ft_strncmp(envtmp->value, val, ft_strlen(val)))
			return (envtmp);
		envtmp = envtmp->next;
	}
	return (envtmp);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	s;
	int	res;

	i = 0;
	res = i;
	s = 1;
	while (nptr[i] == ' ' || nptr[i] == '\n' || nptr[i] == '\f'
		|| nptr[i] == '\t' || nptr[i] == '\v' || nptr[i] == '\r')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			s = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9' && nptr[i])
	{
		res *= 10;
		res += nptr[i] - '0';
		i++;
	}
	return (res * s);
}

static int	ft_counting(long int n)
{
	int	i;

	i = 0;
	if (n < 0)
		n = n * -1;
	if (n > 9)
		i = ft_counting(n / 10);
	i++;
	return (i);
}

static void	ft_writing(char *p, long int n, int *i)
{
	if (n < 0)
		n = n * -1;
	if (n <= 9)
	{
		p[*i] = '0' + n;
		(*i)++;
	}
	else
	{
		ft_writing(p, n / 10, i);
		ft_writing(p, n % 10, i);
	}
}

char	*ft_itoa(int n)
{
	char	*p;
	int		count;

	count = ft_counting(n);
	if (n < 0)
		count += 1;
	p = (char *) malloc((count + 1) * sizeof(char));
	if (!p)
		return (NULL);
	count = 0;
	if (n < 0)
	{
		count = 1;
		p[0] = '-';
		ft_writing(p, n, &count);
	}
	else
		ft_writing(p, n, &count);
	p[count] = '\0';
	return (p);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int				i;
	unsigned char	*st1;
	unsigned char	*st2;

	i = 0;
	st1 = (unsigned char *) s1;
	st2 = (unsigned char *) s2;
	while ((st1[i] || st2[i]))
	{
		if (st1[i] != st2[i])
			return (st1[i] - st2[i]);
		i++;
	}
	return (0);
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

int	ft_countnb(char **line)
{
	int	i;
	int	j;
	int	x;

	i = 1;
	x = 0;
	while (line[i] && (line[i][0] != 39 || line[i][0] != 34))
	{
		j = 0;
		while (line[i][j])
			j++;
		x += j;
		i++;
	}
	return (x + i - 1);
}

char	*lineinone(char **line)
{
	char	*ret;
	int		i;
	int		j;
	int		x;

	ret = malloc (sizeof(char) * ft_countnb(line));
	i = 0;
	x = 0;
	j = 0;
	while (line[i] && (line[i][0] != 39 || line[i][0] != 34))
	{
		j = 0;
		while (line[i][j])
		{
			ret[x] = line[i][j];
			j++;
			x++;
		}
		x++;
		i++;
		if (line[i] && (line[i][0] != 39 || line[i][0] != 34))
			ret[x] = ' ';
	}
	ret[x] = '\0';
	return (ret);
}

// int	ft_simple(pid_t frk, t_tree element, t_env *env)
// {
// 	char *cmdpath;

// 	cmdpath = ft_searchinenv(&element, env);
// 	if (!ft_searchinenv(&element, env))
// 	{
// 		write(1, "No such a command\n", 18);
// 		return (127);
// 	}
// 	// frk = fork();
// 	// if (frk == 0)
// 	// {
// 	// 	execv();
// 	// }
// 	return (0);
// }

int	ft_pipe()
{

	return (0);
}

int	ft_and()
{
	return (0);
}

int	ft_or()
{
	return (0);
}

int	ft_findandexecutered()
{
	return (0);
}


void	ft_varname(char *varname)
{
	int i;
	int j;

	i  = 0;
	j = 1;
	while (1)
	{
		varname[i] = varname[j];
		if (!varname[i])
			break;
		j++;
		i++;
	}
	varname[i] = '=';
}

char	*ft_get_var(t_env **env, char *var)
{
	int		i;
	char	*result;

	ft_varname(var);
	i = -1;
	while (*env)
	{
		if (!ft_strncmp((*env)->value, var, ft_strlen(var)))
			break ;
		*env = (*env)->next;
	}
	if (ft_strncmp((*env)->value, var, ft_strlen(var)))
		return (NULL);
	result = &(*env)->value[ft_strlen(var)];
	return (result);
}

// int	ft_execution(t_tree *tree, int n)
// {
// 	int i = 0;
// 	if (!tree)
// 		return(-1);
// 	while(i++ < n)
// 		printf("------- ");
// 	n++;
// 	// if ()
// 	if (tree->left)
// 		affich(tree->left, "left", n);
// 	if (tree->right)
// 		affich(tree->right, "rigth", n);
// 	return (tree->type);
// }

// int	ft_therespace(char *value)
// {
// 	int	i;

// 	i = -1;
// 	while (value[++i])
// 	{
// 		if (value[i] == ' ')
// 			return (-1);
// 	}
// 	return (0);
// }

char	*ft_partone(char *value)
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

// t_env	*ft_apply(t_env **env, char *srch)
// {
// 	int i;

// 	i = -1;
// 	while (*env)
// 	{
// 		if (!ft_strncmp((*env)->value, srch, ft_strlen(srch)))
// 			return (*env);
// 		*env = (*env)->next;
// 	}
// 	return (NULL);
// }

char	*ft_plus(char *s1, char *s2)
{
	char *str;
	int	i;
	int	j;

	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while(s1[++i])
		str[i] = s1[i];
	while (s2[++j])
		str[i + j] = s1[i];
	str[i + j] = 0;
	return (str);
}

int	ft_shlvl(t_env **env, int type)
{
	t_env	*shlvl;
	char	*value;
	int		ret;
	int		i;
	
	shlvl = ft_getenv(env, "SHLVL=");
	ret = ft_atoi(&(shlvl->value[6]));
	if (type)
		ret++;
	else
		ret--;
	value = ft_itoa(ret);
	free(shlvl->value);
	shlvl->value = ft_plus("SHLVL=", value);
	free(value);
	return (0);
}


// char	*ft_addslach(char **location)
// {
// 	char	*ret;
// 	int		i;

// 	i = 0;
// 	ret = malloc (ft_strlen(*location) + 2);
// 	while (location[i])
// 	{
// 		ret[i] = location[i];
// 		i++;
// 	}
// 	ret[i] = '/';
// 	ret[i + 1] = '\0';
// 	free(*location);
// 	return (ret);
// }

// char	*ft_removepart(char **location)
// {
// 	int		i;
// 	int		j;
// 	char	*path;

// 	i = -1;
// 	while (++i >= 0)
// 	{
// 		if (location[i] == '/')
// 			break;
// 	}
// 	path = malloc(i + 1);
// 	path[i + 1] = '\0';
// 	while (i >= 0)
// 	{
// 		path[i] = location[i];
// 		i--;
// 	}
// 	free (*location);
// 	return (path);
// }

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	int		i;
// 	int		k;
// 	int		count;
// 	char	*p;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	i = ft_strlen(s1);
// 	k = ft_strlen(s2);
// 	count = i + k + 1;
// 	p = (char *) malloc(count * sizeof(char));
// 	if (!p)
// 		return (NULL);
// 	i = 0;
// 	k = i;
// 	while (s1[k])
// 		p[i++] = s1[k++];
// 	k = 0;
// 	while (s2[k])
// 		p[i++] = s2[k++];
// 	p[i] = '\0';
// 	return (p);
// }