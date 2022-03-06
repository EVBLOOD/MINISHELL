/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 18:45:09 by sakllam           #+#    #+#             */
/*   Updated: 2022/03/06 21:00:01 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char	**ft_get_executable_foulders(char **en)
{
	int		i;
	char	**result;
	char	*adrs;

	i = -1;
	while (en[++i])
	{
		if (!ft_strncmp(en[i], "PATH=", 5))
			break ;
	}
	if (ft_strncmp(en[i], "PATH=", 5))
		return (NULL);
	adrs = &en[i][5];
	result = ft_split(adrs, ':');
	return (result);
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
}

char *ft_alphajoin(char *line, char *path)
{
	int		i;
	int		j;
	int		x;
	char	*ret;

	i = -1;
	j = -1;
	x = ft_strlen(line) + ft_strlen(path) + 1;
	ret = malloc(sizeof(char) * (x + 1));
	while (path[++i])
		ret[i] = path[i];
	path[i] = '/';
	i++;
	while (line[++j])
		ret[i + j] = line[j];
	ret[i + j] = '\0';
	return (ret);
}

int	ft_thereisaslach(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '/')
			return (1);
	}
	return (0);
}

int	ft_compare(char *paths, char *line)
{
	char	*cmdpath;

	cmdpath = ft_alphajoin(line, paths);
	if (access(cmdpath, F_OK))
		return (1);
	if (access(cmdpath, X_OK))
		return (2);;
	return (0);
}

char	*ft_searchinenv(t_tree *element, char *env)
{
	char	*line;
	char	**paths;
	int		i;
	int		j;

	if (element->type == DQ || element->type == SQ)
		line = ft_joininone(element->element);
	else
		line = element->element[0];
	if (ft_thereisaslach(line))
	{
		if (ft_compare(paths[i], line))
		{
			if (ft_compare(paths[i], line) == 1)
			{
				write (1, "no such a file\n", 16);
				return (NULL);
			}
			else
			{
				write (1, "permesion den\n", 15);
				return (NULL);
			}
		}
	}
	paths = ft_get_executable_foulders(env);
	if (!paths)
		return (NULL);
	i = 0;
	j = 0;
	while (paths[i])
	{
		if (!ft_compare(paths[i], line))
			break;
		i++;
	}
	if (!paths[i])
	{
		write (1, "cannot find that cmd \n", 24);
		return (NULL);
	}
	return (ft_alphajoin(line, paths[i]));
}

int	ft_simple(pid_t frk, t_tree element, char **env)
{
	char *cmdpath;

	cmdpath = ft_searchinenv(&element, env);
	if (!ft_searchinenv(&element, env))
	{
		write(1, "No such a command\n", 19);
		return (127);
	}
	// frk = fork();
	// if (frk == 0)
	// {
	// 	execv();
	// }
}

int	ft_pipe()
{
	
}

int	ft_and()
{
	
}

int	ft_or()
{
	
}

int	ft_findandexecutered()
{
	
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

char	**ft_get_var(char **en, char *var)
{
	int		i;
	char	**result;

	ft_varname(var);
	i = -1;
	while (en[++i])
	{
		if (!ft_strncmp(en[i], var, ft_strlen(var)))
			break ;
	}
	if (ft_strncmp(en[i], var, ft_strlen(var)))
		return (NULL);
	result = &en[i][ft_strlen(var)];
	return (result);
}

int	ft_execution(t_tree *tree, int n)
{
	int i = 0;
	if (!tree)
		return(-1);
	while(i++ < n)
		printf("------- ");
	n++;
	if ()
	if (tree->left)
		affich(tree->left, "left", n);
	if (tree->right)
		affich(tree->right, "rigth", n);
	return (tree->type);
}

int	ft_echo(char *line, int flag)
{
	int	i;

	i = -1;
	write (1, line, ft_strlen(line));
	if (flag)
		write (1, "\n", 1);
	return (0);
}

int	ft_pwd(void)
{
	char	*pwd;

	pwd = malloc(1000000);
	getcwd(pwd, sizeof(pwd));
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
}