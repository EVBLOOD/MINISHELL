/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clone_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 11:43:30 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/05 15:00:04 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

int	ft_envsize(char **elements)
{
	int	i;

	i = 0;
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

	i = -1;
	newenv = malloc(sizeof(char *) * (ft_envsize(env) + 1));
	while (env[++i])
		newenv[i] = ft_strdup(env[i]);
	newenv[++i] = ft_strdup(element);
	newenv[++i] = NULL;
	i = -1;
	while (env[++i])
		free (env[i]);
	free(env);
	return (newenv);
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

void	ft_addshlvl(char **env, int x)
{
	int		i;
	int		nb;
	char	*char_nb;
	char	*response;

	i = -1;
	while ((*env)[++i])
		if ((*env)[i] == '=')
			break;
	i++;
	nb = ft_atoi(&(*env)[i]) + x;
	char_nb = ft_itoa(nb);
	response = malloc(ft_strlen(char_nb) + i + 1);
	nb = -1;
	while (++nb < i)
		response[nb] = (*env)[nb];
	i = 0;
	while (char_nb[i])
	{
		response[nb] = char_nb[i];
		(nb++, i++);
	}
	response[nb] = '\0';
	free((*env));
	(*env) = response;
}

void	ft_SHLVL(char **env, int x)
{
	int	i;
	int	found;

	i = -1;
	found = 0;
	while (env[++i])
		if (!ft_strncmp(env[i], "SHLVL=", 6))
		{
			found = 1;
			break;
		}
	if (!found)
		env = ft_addtoenv(env, "SHLVL=1");
	else
		ft_addshlvl(&env[i], x);
}

char	**ft_cloneenv(char **env)
{
	char	**newenv;
	int		i;

	i = 0;
	newenv = malloc(sizeof(char *) * ft_envsize(env));
	while (env[i])
	{
		newenv[i] = ft_strdup(env[i]);
		i++;
	}
	newenv[i] = NULL;
	ft_SHLVL(newenv, 1);
	return (newenv);
}