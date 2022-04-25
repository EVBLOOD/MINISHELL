/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ismatch_.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:48:36 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/25 01:48:52 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

int ft_ismatch(char *name, char *reg)
{
    int     i;
    int     j;
    char    *tomatch;
    int     x;

    i = 0;
    j = 0;
    if (!reg[0])
        return (1);
    if (reg[0] == '*')
		j = ft_partonecond(&i, reg, name);
    else
		j = ft_parttwo(&i, reg, name);
    if (j == -1)
        return (0);
    x = ft_ismatch(&name[j], &reg[i]);
    return (x);
}
