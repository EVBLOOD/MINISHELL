/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:11:09 by sakllam           #+#    #+#             */
/*   Updated: 2022/03/19 23:52:28 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "readline/readline.h"
#include "readline/history.h"
#include <curses.h>
#include <term.h>

#define PIPE		0
#define DQ			1
#define SQ			2
#define WORD		3
#define RDIN		4
#define RDOUT		5
#define RDHER		6
#define RDAPP		7
#define VARIABLE	8
#define AND			9
#define OR			10
#define PRTOPEN		11
#define PRTCLOSE	12
#define WILD		13

typedef	struct s_cmd
{
	char	*path;
	char	*all;
}	t_cmd;

typedef struct s_env
{
	char 			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_her
{
	char 			*value;
	struct s_her	*next;
}	t_her;

typedef struct s_list
{
	char			*splited;
	int				infront_space;
	int				TYPE;
	struct s_list	*next;
}	t_list;

typedef struct s_tree
{
	char			**element;
	t_list			**elements;
	int				type;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

t_list	*ft_lexicalanalysis(char *line);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
int		ft_syntaxanalysis(t_list *parsresult);
int		ft_strlen(const char *s);
t_tree	*ft_abs(t_list **parsresult, t_list *end);
// int		ft_execution(t_tree *tree, int n);
// int	ft_execution(t_env *env, t_tree *tree);
int	ft_execution(t_env *env, t_tree *tree, char position, t_tree *parrent, int pipe);
// int	ft_execution(t_env *env, t_tree *tree, char position, t_tree *parrent, int *x);
char	**ft_split(char const *s, char c);
int		ft_varvalidating(int c);
char	*ft_strdup(const char *s);
t_env	*ft_getenv(t_env **env, char *val);
t_env	*ft_cloneenv(char **env);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_clone2(t_env *env);
int		ft_isalpha(int c);
char	*ft_scanvar(char **line, t_env *env);
void	ft_lstadd_fronther(t_her **lst, t_her *new);
void	ft_lstadd_backher(t_her **lst, t_her *new);
t_her	*ft_lstlasther(t_her *lst);
char **ft_clone2(t_env *env);
void	ft_exit(void);
char	*ft_isacmd(char *cmd, t_env *env);
int	ft_isalpha(int c);
int	ft_env(t_env **env);
int	ft_isdigit(int c);
char	**ft_clone2(t_env *env);
int	ft_echo(char **line);
int 	check_builtins(char **cmd, t_env **env);
void	ft_lstadd_backenv(t_env **lst, t_env *new);
int		ft_pwd(void);
void	ft_exit(void);
int	ft_cd(char *dest);
int	ft_unset(t_env **env, char *str);
// void check_var(t_env **env, char **value);
void check_var(t_env **env, char **value);
int	ft_export(t_env **env, char *value);
// int	ft_varvalidating(int c);
#endif
