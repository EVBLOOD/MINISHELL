/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saad <saad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:54:21 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/30 18:26:42 by saad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

void	exiterror(const char *command)
{
	write (1, "bash: exit: ", 12);
	write (1, command, ft_strlen(command));
	write (1, ": numeric argument required\n", 28);
	exit (255);
}

int	isnum(char c)
{
	return (c >= '0' && c <= '9');
}

long long	ft_atoibody(int i, const char *str, int sgn)
{
	long long			result;
	long long			latest;

	result = 0;
	latest = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		if (latest > result)
			exiterror(str);
		latest = result;
		i++;
	}
	return (result * sgn);
}

long long	ft_atoi_long(const char *str)
{
	int					i;
	int					n;

	i = 0;
	n = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		n *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	return (ft_atoibody(i, str, n));
}

int	check_error_exit(char **command)
{
	int			i;
	long long	exiting;

	i = 0;
	if (!command[0][i])
		exiterror(command[0]);
	if (ft_checkexitspaces(command[0]))
		exiterror(command[0]);
	exiting = ft_atoi_long(command[0]);
	if (command[1])
	{
		write(1, "bash: exit: too many arguments\n", 31);
		return (1);
	}
	else
		exit(exiting);
	return (1);
}
