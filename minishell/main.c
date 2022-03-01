/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:12:44 by sakllam           #+#    #+#             */
/*   Updated: 2022/02/28 14:19:02 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{

	char	*line;
	t_list	*parsresult;
	while (1)
	{
		line = readline("$> ");
		add_history(line);
		parsresult = ft_parsing(line);
	}
	
}