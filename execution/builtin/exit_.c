/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 22:42:03 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/28 23:44:34 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

int	ft_exit(char **command)
{
	write(0, "exit\n", 6);
	if (!command[0])
		exit (g_exec.returnvalue);
	check_error_exit(command);
	return (1);
}

int	ft_checkexitspaces(char *cmd)
{
	int			i;
	int			nbfound;

	i = 0;
	nbfound = 1;
	while (cmd[i] && !ft_isspace(cmd[i]))
		i++;
	if (cmd[i] == '-' || cmd[i] == '+')
		i++;
	while (isnum(cmd[i]))
	{
		nbfound = 0;
		i++;
	}
	while (cmd[i] && !ft_isspace(cmd[i]))
		i++;
	if (cmd[i] || nbfound)
		return (1);
	return (0);
}
