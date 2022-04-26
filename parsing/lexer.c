/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 00:49:22 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/26 04:24:49 by foulare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	ft_isspace(char x)
{
	if (x == '\t' || x == '\n' || x == '\v'
		|| x == '\f' || x == '\r' || x == ' ')
		return (0);
	return (1);
}

int	check_type_one(char c, int i)
{
	if (c == '|' && i == 1)
		return (PIPE);
	else if (c == '|' && i == 2)
		return (OR);
	if (c == '&' && i == 1)
		return (-1);
	else if (c == '&' && i == 2)
		return (AND);
	if (c == '<' && i == 1)
		return (RDIN);
	else if (c == '<' && i == 2)
		return (RDHER);
	if (c == '>' && i == 1)
		return (RDOUT);
	else if (c == '>' && i == 2)
		return (RDAPP);
	return (-1);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	check_type_two(char c)
{
	if (c == ')')
		return (PRTCLOSE);
	else if (c == '(')
		return (PRTOPEN);
	else if (c == '\'')
		return (SQ);
	else if (c == '\"')
		return (DQ);
	else if (c == '*')
		return (WILD);
	else if (c == '$')
		return (VARIABLE);
	return (-1);
}
