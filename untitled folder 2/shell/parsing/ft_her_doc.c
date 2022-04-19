/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_her_doc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 03:37:06 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/19 01:24:28 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"
   
char *create_filename(char *file)
{
    char	*tmp;

	while (!access(file, F_OK))
	{
		tmp = file;
		file = ft_strjoin(file, "1");
		free(tmp);
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

char    *ft_herdoc(char *limiter, char *name)
{
    char *file;
    char *line;
    int fd;

    file = create_filename(name);
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    while (1)
    {
        line = readline (">> ");
        if (!line || !ft_strcmp(line, limiter))
            break;
        write(fd, line, ft_strlen(line));
    }
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
	ret = malloc(ft_strlen(dor) - 1);
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

int	ft_herdoccreating(t_list **lst)
{
	char	*x;
	char	*lem;
	char	*join;
	t_list	*tmp;

	lem = ft_strdup("");
	tmp = *lst;
	*lst = (*lst)->next;
	while (*lst && ((*lst)->TYPE == WILD || (*lst)->TYPE == WORD || (*lst)->TYPE == SQ
			|| (*lst)->TYPE == DQ))
	{
		if ((*lst)->TYPE == SQ || (*lst)->TYPE == DQ)
		{
			join = ft_deldq_sq(&((*lst)->splited));
			if (!join)
				return (0);
			tmp->herdocexp = 0;
		}
		if ((*lst)->TYPE == WILD || (*lst)->TYPE == WORD)
			join = (*lst)->splited;
		(*lst)->sqp = 0;
		x = lem;
		lem = ft_strjoin(lem, join);
		if ((*lst)->TYPE == SQ || (*lst)->TYPE == DQ)
			free(join);
		free(x);
		*lst = (*lst)->next;
	}
	free(tmp->splited);
	tmp->splited = ft_herdoc(lem, lem);
	*lst = tmp;
	return (1);
}