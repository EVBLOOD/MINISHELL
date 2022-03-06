/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:11:09 by sakllam           #+#    #+#             */
/*   Updated: 2022/03/06 19:13:18 by sakllam          ###   ########.fr       */
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
#define DQ			1
#define SQ			3
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

typedef	struct s_cmd
{
	char	*path;
	char	*all;
}	t_cmd;


typedef struct s_list
{
	char			*splited;
	int				TYPE;
	struct s_list	*next;
}	t_list;

typedef struct s_tree
{
	char	**element;
	int		type;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

t_list	*ft_lexicalanalysis(char *line);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
int	ft_syntaxanalysis(t_list *parsresult);
int	ft_strlen(const char *s);
t_tree	*ft_abs(t_list **parsresult, t_list *end);
int	ft_execution(t_tree *tree, int n);
#endif
