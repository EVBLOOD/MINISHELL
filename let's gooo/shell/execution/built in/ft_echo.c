/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 22:48:56 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/22 11:31:03 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

int ft_checkflag(char *str)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	if (str[0] != '-')
		return (1);
	while (str[++i])
	{
		if (str[i] != 'n')
		{
			ret = 1;
			break;
		}
	}
	return (ret);
}

int	ft_echo(char **line)
{
	int	i;
	int flag;
	flag = 1;

	while(line[flag] && !ft_checkflag(line[flag]))
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
