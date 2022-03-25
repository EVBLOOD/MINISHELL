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

#include "../../minishell.h"

int	ft_echo(char **line)
{
	int	i;
	int flag;

	flag = 0;
	puts("?");
	while(!ft_strncmp(line[flag], "-n", ft_strlen(line[flag])))
		flag++; //ici la mort
	puts("?");
	i = flag;
	// puts("?");
	while(line[i])
	{
		if (i)
			write(1, " ", 1);
		write (1, line[i], ft_strlen(line[i]));
		i++;
	}
	if (!flag)
		write (1, "\n", 1);
	return (0);
}
