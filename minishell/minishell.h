/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:11:09 by sakllam           #+#    #+#             */
/*   Updated: 2022/03/01 15:17:25 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISELL_H
#define MINISELL_H
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#define PIPE		0
#define DQOPEN		1
#define DQCLOSE		2
#define SQOPEN		3
#define SQCLOSE		4
#define WORD		5
#define RDIN		6
#define RDOUT		7
#define RDHER		8
#define RDAPP		9
#define VARIABLE	10
#define AND			11
#define OR			12
#define PRTOPEN		13
#define PRTCLOSE	14
#define WILD		15

typedef struct s_list
{
	char			*splited;
	int				TYPE;
	struct s_list	*next;
}	t_list;


// typedef struct s_commands
// {
// 	char				**cmd;
// 	char				*pathcmd;
// 	int					echo;
// 	int					echo;
// 	int					cd;
// 	int					pwd;
// 	int					export;
// 	int					unset;
// 	int					env;
// 	int					exit;
// 	int					redirections;
// 	int					dquote;
// 	int					squote;
// 	struct s_commands	*next;
// }	t_commands;

// typedef struct s_commands1
// {
// 	char				**cmd;
// 	char				*pathcmd;
// 	int					the_first;
// 	struct s_commands1	*next;
// }	t_commands1;

// typedef struct s_all_data
// {
// 	int	fd_file1;
// 	int	fd_file2;
// 	int	fork_respo;
// 	int	whileforks_respo;
// 	int	never_goin;
// 	int	pipe_respo;
// 	int	pipe_fds[2];
// 	int	count;
//}	t_all_data;
t_list	*ft_parsing(char *line);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
#endif