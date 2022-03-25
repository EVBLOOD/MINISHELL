/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 22:51:01 by sakllam           #+#    #+#             */
/*   Updated: 2022/03/16 16:17:33 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_cd(char *dest)
{
	if (ft_strlen(dest) == 0)
	{
		chdir ("~");
		return (0);
	}
	if (chdir (dest))
	{
		write (1, "cd: ", 5);
		write (1, dest, ft_strlen(dest));
		write(1, ": No such file or directory\n", 28);
		return (1);
	}
	return (0);
}