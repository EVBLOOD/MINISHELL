/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ismatch.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saad <saad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 02:35:17 by saad              #+#    #+#             */
/*   Updated: 2022/03/29 03:49:30 by saad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}


char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*p;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s + start) < len)
		p = (char *) malloc((ft_strlen(s + start) + 1) * sizeof(char));
	else
		p = (char *) malloc(((int) len + 1) * sizeof(char));
	if (!p)
		return (NULL);
	while (i < (int) len && s[i + start] && !(start >= ft_strlen(s)))
	{
		p[i] = s[i + start];
		i++;
	}
	p[i] = '\0';
	return (p);
}

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
    printf("name:%s|reg:%s|\n", &name[j], &reg[i]);
    if (reg[0] == '*')
    {
        i = 1;
        while (reg[i] && reg[i] != '*')
            i++;
        tomatch = ft_substr(reg, 1, i);
        if (reg[i])
            j = ft_findthefirst(name, tomatch);
        else
            j = ft_findattheend(name, tomatch);
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


int main()
{
    int i;

    i = ft_ismatch("Desktopd", "*D*");
    printf("the inswer: %d\n", i);
}