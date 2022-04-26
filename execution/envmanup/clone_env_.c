/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clone_env_.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:59:51 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/25 02:01:07 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	s;
	int	res;

	i = 0;
	res = i;
	s = 1;
	while (nptr[i] == ' ' || nptr[i] == '\n' || nptr[i] == '\f'
		|| nptr[i] == '\t' || nptr[i] == '\v' || nptr[i] == '\r')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			s = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9' && nptr[i])
	{
		res *= 10;
		res += nptr[i] - '0';
		i++;
	}
	return (res * s);
}

int	ft_counting(long int n)
{
	int	i;

	i = 0;
	if (n < 0)
		n = n * -1;
	if (n > 9)
		i = ft_counting(n / 10);
	i++;
	return (i);
}

void	ft_writing(char *p, long int n, int *i)
{
	if (n < 0)
		n = n * -1;
	if (n <= 9)
	{
		p[*i] = '0' + n;
		(*i)++;
	}
	else
	{
		ft_writing(p, n / 10, i);
		ft_writing(p, n % 10, i);
	}
}

char	*ft_itoa(int n)
{
	char	*p;
	int		count;

	count = ft_counting(n);
	if (n < 0)
		count += 1;
	p = (char *) ft_malloc((count + 1) * sizeof(char));
	if (!p)
		return (NULL);
	count = 0;
	if (n < 0)
	{
		count = 1;
		p[0] = '-';
		ft_writing(p, n, &count);
	}
	else
		ft_writing(p, n, &count);
	p[count] = '\0';
	return (p);
}

char	*ft_itoab(int n)
{
	char	*p;
	int		count;

	count = ft_counting(n);
	if (n < 0)
		count += 1;
	p = (char *) malloc((count + 1) * sizeof(char));
	if (!p)
		return (NULL);
	count = 0;
	if (n < 0)
	{
		count = 1;
		p[0] = '-';
		ft_writing(p, n, &count);
	}
	else
		ft_writing(p, n, &count);
	p[count] = '\0';
	return (p);
}
