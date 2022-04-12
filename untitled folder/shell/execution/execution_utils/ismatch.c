/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ismatch.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 02:35:17 by saad              #+#    #+#             */
/*   Updated: 2022/04/02 12:29:54 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../mini_shell.h"

int ft_findthefirst(char *name, char *tomatch) //to test "saad ad"
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (name[i])
    {
        while (name[j + i] && tomatch[j] == name[j + i])
        {
            if (!tomatch[j + 1])
                return (i);
            j++;
        }
        j = 0;
        i++;
    }
    return (-1);
}

int ft_findattheend(char *name, char *tomatch)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (name[i])
    {
        while (name[j + i] && tomatch[j] == name[j + i])
        {
            if (!tomatch[j + 1] && !name[j + i + 1])
                return (i);
            j++;
        }
        j = 0;
        i++;
    }
	if (name[i] == tomatch[0])
		return (i);
    return (-1);
}

int ft_findatfirst(char *name, char *tomatch)
{
    int i;
    int j;
    int end;

    i = 0;
    j = 0;
    end = ft_strlen(tomatch);
    while (name[i] && end > i)
    {
        while (name[j + i] && tomatch[j] == name[j + i] && end > i + j)
        {
            if (!tomatch[j + 1])
                return (i);
            j++;
        }
        j = 0;
        i++;
    }
    return (-1);
}

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
    // printf("name:%s|reg:%s|\n", &name[j], &reg[i]);
    if (reg[0] == '*')
    {
        i = 1;
        while (reg[i] && reg[i] != '*')
            i++;
        if (reg[i])
		{

        	tomatch = ft_substr(reg, 1, i - 1);
            j = ft_findthefirst(name, tomatch);
		}
        else
		{
			tomatch = ft_substr(reg, 1, i);
            j = ft_findattheend(name, tomatch);
		}
        free(tomatch);
    }
    else
    {
        while (reg[i] && reg[i] != '*')
            i++;
        tomatch = ft_substr(reg, 0, i);
        if (reg[i] == '*')
            j = ft_findatfirst(name, tomatch);
        else
        {
            j = ft_findattheend(name, tomatch);
            i++;
        }
    }
    if (j == -1)
        return (0);
    x = ft_ismatch(&name[j], &reg[i]);
    return (x);
}
 