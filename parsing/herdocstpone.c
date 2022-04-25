/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdocstpone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:08:11 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/25 01:09:48 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

char *create_filename(char *file)
{
    char	*tmp;

	tmp = ft_strdup(file);
	file = tmp;
	while (!access(file, F_OK))
	{
		tmp = file;
		file = ft_strjoin(file, "1");
	}
	return (file);
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

char    *ft_herdoc(char **name)
{
    char	*file;
    char	*line;
    int		fd;
	char	*limiter;

    limiter = ft_strdup(*name);
	file = create_filename(*name);
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    while (1)
    {
        line = readline (">> ");
        if (!line || !ft_strcmp(line, limiter))
            break;
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
		free(line);
    }
	if (line)
		free(line);
    close(fd);
    return (file);
}

char	*ft_deldq_sq(char **str)
{
	char	*ret;
	char	*dor;
	int		i;

	dor = *str;
	if (ft_strlen(dor) == 1 || dor[ft_strlen(dor) - 1] != dor[0])
		return (NULL);
	ret = ft_malloc(ft_strlen(dor) - 1);
	if (!ret)
		return (NULL);
	i = 1;
	while (dor[i] != dor[0])
	{
		ret[i - 1] = dor[i];
		i++;
	}
	ret[i - 1] = '\0';
	return (ret);
}

int	ft_herdocexptype(t_list **lst, t_list *tmp, char **join)
{
	if ((*lst)->TYPE == SQ || (*lst)->TYPE == DQ)
	{
		(*join) = ft_deldq_sq(&((*lst)->splited));
		if (!(*join))
			return (1);
		tmp->herdocexp = 1;
	}
	if ((*lst)->TYPE == WILD || (*lst)->TYPE == WORD)
		(*join) = (*lst)->splited;
	(*lst)->sqp = 0;
	return (0);
}