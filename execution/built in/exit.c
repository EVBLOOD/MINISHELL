/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:54:21 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/25 15:54:53 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

int isnum(char c)
{
	return (c >= '0' && c <= '9');
}

long long	ft_atoi_long(const char *str)
{
	int					i;
	long long			result;
	int					n;

	i = 0;
	n = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		n *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * n);
}

int check_error_exit(char **command)
{
	int i;

	i = -1;
	while (command[0][++i])
	{
		if ((command[0][0] == '-' || command[0][0] == '+'))
			i++;
		if (!isnum(command[0][i]) || ft_atoi_long(command[0]) > 9223372036854775807 
			|| ft_atoi_long(command[0]) < (-922337203685477580 - 1))
		{
			write (1, "bash: exit: ", 12);
			write (1, command[0], ft_strlen(command[0]));
			write (1, ": numeric argument required\n", 28);
			exit (255);
		}
	}
	if (command[1])
	{
		write(1, "bash: exit: too many arguments\n", 31);
		return (0);
	}
	return (1);
}

int	ft_exit(char **command)
{
	write(0, "exit\n", 6);
	if (!command[0])
		exit (g_exec.returnvalue);
	if (!check_error_exit(command))
		return (0);
	exit (ft_atoi_long(command[0]));
	return (1);
}
