/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 22:48:56 by sakllam           #+#    #+#             */
/*   Updated: 2022/03/17 00:41:13 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int ft_checkflag(char *str)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	if (str[i] == '-')
	{
		while (str[++i])
		{
			if (str[i] != 'n')
			{
				ret = 1;
				break;
			}
		}
	}
	else
		ret = 1;
	return (ret);
}

int	ft_echo(char **line)
{
	int	i;
	int flag;
	flag = 0;

	while(line[flag] && (!ft_strncmp(line[flag], "-n", ft_strlen(line[flag])) || !ft_checkflag(line[flag])))
		flag++;
	i = flag;
	while(line && line[i])
	{
		if (i != flag)
			write(1, " ", 1);
		write (1, line[i], ft_strlen(line[i]));
		i++;
	}
	if (!flag)
		write (1, "\n", 1);
	return (0);
}
