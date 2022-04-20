/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 23:36:27 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/20 09:10:14 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
#define MINI_SHELL_H
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
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
#define SPACES		14
#define LIST		15
#define RDARG		16

typedef struct s_list
{
	char			*splited;
	char			**expanded;
	int				nb;
	int				TYPE;
	int				fd;
	int				herdocexp;
	int				sqp;
	struct s_list	*next;
}	t_list;

typedef struct s_tree
{
	t_list			**elements;
	char			**args;
	int				type;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

typedef struct s_befexec
{
	char 				*ofcvalue;
	struct s_befexec	*next;
}	t_befexec;

typedef struct s_execute
{
	int		*newpipe;
	int		*oldpipe;
	int		modepipe;
	int		piperet;
	int		thisisreturn;
}	t_execute;


typedef struct s_executenop
{
	t_tree	*parrent;
	t_tree	*root;
	char	pos;
}	t_executenop;


// typedef	struct s_cmd
// {
// 	char	*path;
// 	char	*all;
// }	t_cmd;

t_list	*ft_lexicalanalysis(char *line);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		ft_syntaxanalysis(t_list *parsresult);
int		ft_strlen(const char *s);
t_tree	*ft_parsing(char *line);
t_tree	*ft_abs(t_list **parsresult, t_list *end);
char	**ft_cloneenv(char **env);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_SHLVL(char **env, int i);
char	*ft_strdup(const char *s);
char	*ft_strchr(int c, char *s);
int		ft_strlen(const char *s);
int		ft_isdigit(int c);
int	 	ft_isalpha(int c);
int		ft_varvalidating(int c);
char	**ft_dealwithlist(t_list **list, char **env, int i);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
// int		ft_execution(char **env, t_tree *tree, char position, t_execute *args);
// int	ft_getreturn(void);
int	ft_getreturn(pid_t id);
char	*ft_getenv(char **env, char *val);
pid_t	simple_cmd(char *path, char **cmd, char **env);
char	*ft_searchandconcat(char **splited, char *cmd);
char	*ft_isacmd(char *cmd, char **env);
int ft_lstlen(t_list *list);
// t_list **check_wild(t_list **command);
int getlen(t_list **str);
void free_list(t_list *list);
int execcmd(t_tree *tree, char **env);
void ft_freelist(t_list **element);
void ft_free(char **element);
void disp(t_list **list);
int	ft_RDRfunction(char position, t_tree *tree, char **env, int Ptype, int fd);
int	ft_PIPEfunction(char position, t_tree *tree, char **env, int lastpipe, int pip[2]);
t_list	*ft_redirectionsset(t_list *lst);
char	**ft_simplewild(void);
int ft_ismatch(char *name, char *reg);
char	**ft_expandvariables(t_list *list, char **env);
char	*ft_expand_dq(t_list *list, char **env);
void	ft_ofcadd_back(t_befexec **lst, t_befexec *new);
int		ft_ofclengh(t_befexec *lst);
char	**ft_wildcard_(char *pattern);
int	ft_execution(char **env, t_tree *tree, t_executenop arg, t_execute *args);
void	ft_lstadd_front(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
int	isredirections(int type);
int	ft_nocommand(char *line);
// void	ft_herdoccreating(t_list *lst);
int	ft_herdoccreating(t_list **lst);
int	ft_strcmp(const char *s1, const char *s2);
int	ft_treeexecution(char **env, t_tree *tree, char position, t_executenop arg);
int	ft_executereds(t_tree *tree, char **env, t_executenop arg);
int	ft_redirectionscheck(t_tree *tree, char	**env);
void	ft_executeredspipe(t_tree *tree, char **env, t_executenop arg);
#endif