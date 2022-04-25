/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 00:45:31 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/25 16:08:26 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H
# include <fcntl.h>
# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include "readline/readline.h"
# include "readline/history.h"
# include <curses.h>
# include <term.h>
# include <limits.h>
# define PIPE		0
# define DQ			1
# define SQ			2
# define WORD		3
# define RDIN		4
# define RDOUT		5
# define RDHER		6
# define RDAPP		7
# define VARIABLE	8
# define AND		9
# define OR			10
# define PRTOPEN	11
# define PRTCLOSE	12
# define WILD		13
# define SPACES		14
# define LIST		15
# define RDARG		16
# define IN			0
# define OUT		1

typedef struct s_trush
{
	void	*element;
	int		dmn;
	struct s_trush	*next;
}	t_trush;

typedef struct s_globale
{
	int		returnvalue;
	int		isexecuting;
	t_trush	*trush;
} t_globale;
extern	t_globale	g_exec;
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
	int				type;
	t_list			*redirections;// linked list of redirections
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;
typedef struct s_befexec
{
	char 				*ofcvalue;
	struct s_befexec	*next;
}	t_befexec;
int	ft_isspace(char x);
int check_type_one(char c, int i);
int	ft_isdigit(int c);
int	ft_isalpha(int c);
int check_type_two(char c);
int	ft_varvalidating(int c);
int	ft_whiterun(char **line);
char	*ft_strchr(int c, char *s);
t_list	*ft_setword(char *line, int i);
void	ft_addwords(char **line, int *i, t_list **head);
void	ft_navigatewords(char **line, int *i);
void	ft_notavar(char **line, t_list **head);
void	ft_addsnglordbl(char **line, int *i, t_list **head);
int	ft_qouting(char **line, t_list **node, char qoute);
void	ft_navigatedoubles(char **line, int *i);
int	ft_isdigitvariable(char **line, t_list **head);
void	ft_variable(char **line, t_list **head);
void	ft_snglonce(char **line, t_list **head);
void	ft_dealingwithspaces(char **line, int *spaces, t_list **head);
t_list	*ft_lexicalanalysis(char *line);
t_tree	*ft_parsing(char *line);
int	ft_strlen(const char *s);
int	ft_checksforqoutes(char *str, int qoute);
int	ft_getnext(t_list *corrent);
void	ft_errormsg(char *str);
int	ft_firstcheck(t_list *lst, int *start);
int	near_pipe_and_or(t_list *lst);
int	near_openparnth(t_list *lst, int *prth);
int	near_closedparnth(t_list *lst, int *prth);
int	ft_wildcard(t_list *lst);
void	redirectioncond(t_list *lst, int *okey, int x);
int	ft_redirections(t_list *lst);
int	ft_quoteserror(int okey, t_list *lst);
int	ft_quotes(t_list *lst);
int	ft_word(t_list *lst);
int	ft_syntaxcond(t_list *parsresult, int *start, int *prth);
int	ft_syntaxanalysis(t_list *parsresult);
char *create_filename(char *file);
int	ft_strcmp(const char *s1, const char *s2);
char    *ft_herdoc(char **name);
char	*ft_deldq_sq(char **str);
int	ft_herdocexptype(t_list **lst, t_list *tmp, char **join);
int	ft_herdoccreating(t_list **lst);
int	isredirections(int type);
int	isnextaword(t_list *lst);
t_list	*ft_createnodes(t_list *lst);
int	ft_redirectiononecon(t_list *lst);
int	ft_isthatared(t_list *lst);
t_list	*ft_creatspacenode(t_list *lst, t_list **head);
t_list	*ft_createnodesspaces(int nb, int type, char *splited);
void	ft_ohmyspace(t_list **head);
t_list	*ft_secondarg(t_list *lst, t_list **head);
t_list	*ft_redirectionone(t_list *lst, t_list **head);
t_list	*passeover(t_list *lst);
t_list	*ft_redirectiontwo(t_list *lst, t_list *end, t_list **head);
t_list	*ft_redirectionsset(t_list *lst);
int ft_lstlen(t_list *list);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
char	*ft_strtrim(char const *s1, char const *set);
t_list	*ft_lastop(t_list *nav, t_list *end);
t_list	*ft_lastpipe(t_list *nav, t_list *end);
int	ft_size(t_list *parsresult, t_list *end);
t_list	*ft_lastredr(t_list *nav, t_list *end);
t_list	*ft_firstredr(t_list *nav, t_list *end);
t_list	*ft_createredirectionnode(t_list *redirection);
t_list	*noderedirections(t_list *list, t_list *end);
t_list	**ft_nextalpha(t_list **list, t_list *end);
int	ft_checkforptr(t_list *lst, t_list *end);
t_tree	*ft_operatorsnode(t_list **parsresult, t_list *end);
t_tree	*ft_pipes(t_list **parsresult, t_list *end);
int	redirectionsnormtree(t_list *next, t_tree *node, t_list *end, t_list **parsresult);
int	ft_protrctionone(t_tree *node);
int	ft_protrctiontwo(t_tree *node);
t_tree	*redirections(t_list **parsresult, t_list *end);
int	sqpspaces(t_list **parsresult, t_list *end);
int	isitexpandable(int x);
t_tree	*words(t_list **parsresult, t_list *end);
t_tree	*wordsandstuf(t_list **parsresult, t_list *end);
t_tree	*ft_abs(t_list **parsresult, t_list *end);
char	*ft_expand_sq(t_list *list);
t_befexec	*ft_createnode(char *str);
char	*ft_replaceexpand_dq(t_list **list, char **env);
char	*ft_replaceexpand_sq(t_list **list);
void	ft_replaceall(t_list **list, char **env);
char	**ft_convertfromlisttochar(t_befexec *list);
char	*ft_replaceandjoin(char **str, char *tojoin);
void	ft_wildmergin(char **str, t_befexec **head);
int	ft_countstars(char *str, int wild);
void ft_varmerging(t_list *list, char **str, int *wild, t_befexec **head);
char	*ft_wildmerging(t_list **list, char **str, int *wild, int *i);
char	*ft_dq_sq_wrdmerging(t_list *list, char **str, int *wild);
void	ft_merginginspaces(int *wild, t_befexec **head, char **str);
t_befexec	*ft_merging(t_list **list, char **env);
char	**ft_dealwithlist(t_list **list, char **env);
t_befexec	*ft_ofclast(t_befexec *lst);
void	ft_ofcadd_front(t_befexec **lst, t_befexec *new);
void	ft_ofcadd_back(t_befexec **lst, t_befexec *new);
int	ft_ofclengh(t_befexec *lst);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_expandvariablesdq(char **var, char **env);
int varlenghcounting(t_list *list, char **env, int *i);
int	ft_expand_dqcount(t_list *list, char **env);
void	ft_outerret(t_list *list, char **env, char **var);
void	ft_returntwo(char *var, char *result, int *index);
void	returnexpvardq(t_list *list, char *result, char **env);
char	*ft_expand_dq(t_list *list, char **env);
char	*ft_getenv(char **env, char *val);
char	*ft_isacmd(char *cmd, char **env);
char *ft_alphajoin(char *line, char *path);
int	ft_checkexistence(char *line);
char	*ft_match(char *splited, char *cmd);
char	*ft_searchandconcat(char **splited, char *cmd);
char	*herexchange(char *var, char **env);
void	ft_readandread(int fd, int ret, char *c, char *var);
void	getvar(int her, int fd, char **env, char *c);
char	*herdoc(int fd, char **env, char *name);
int ft_findthefirst(char *name, char *tomatch);
int ft_findattheend(char *name, char *tomatch);
int ft_findatfirst(char *name, char *tomatch);
int	ft_partonecond(int *i, char *reg, char *name);
int	ft_parttwo(int *i, char *reg, char *name);
int ft_ismatch(char *name, char *reg);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
void	normsplitvars(char const **s, int *spaces);
void	normsplitvarstwo(int *i, int *spaces);
void	ft_spaces(char ***str, size_t *i, int *spaces, size_t *len);
char	**ft_splitchecks(char const *s, char ***table, char *cmp);
char	**ft_splitvar(char const *s, char *cmp);
void	*ft_malloc(size_t size);
char **ft_varreturn(void);
char	*ft_cmdpathfound(char **env, t_list *list, int *found, int *i);
char	**ft_expandvariables(t_list *list, char **env);
int	ft_envsize(char **elements);
char	*ft_strdup(const char *s);
char	*ft_strdupb(const char *s);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_addtoenv(char **env, char *element);
int	ft_atoi(const char *nptr);
int	ft_counting(long int n);
void	ft_writing(char *p, long int n, int *i);
char	*ft_itoa(int n);
char	*ft_itoab(int n);
void	ft_shlvlnorm(int nb, char *response, char *char_nb);
void	ft_addshlvl(char **env, int x);
void	ft_SHLVL(char ***env, int x);
char	**ft_cloneenv(char **env);
int	ft_getreturn(pid_t id);
int	ft_statushundling(int status);
int	ft_isbuiltin(char *command);
int	ft_executebuiledin(char **command, char **env);
void sig_restore(void);
int	ft_simplecmd(char **env, t_tree *tree);
int	ft_nocommand(char *line);
int	ft_sizetablered(t_list *redirection);
t_list	**ft_copycolly(t_list *redirection);
int	andfunction(t_tree *tree, char **env);
int	orfunction(t_tree *tree, char **env);
void	leftpipefunction(t_tree *tree, char **env, int *pfd);
int		rightpipefunction(t_tree *tree, char **env, int *pfd);
void	ft_apndredirections(t_tree *tree, char **env);
int	ft_openherdoc(t_tree *tree, char **env);
void	redirectionherdoc(t_tree *tree, char **env);
void	redirectionsin(t_tree *tree, char **env);
void	redirectionsout(t_tree *tree, char **env);
int	redirectionsfunction(t_tree *tree, char **env);
int	run(t_tree *tree, char **env);
t_trush	*ft_trushlast(t_trush *lst);
void	ft_trushadd_front(t_trush **lst, t_trush *new);
void	ft_trushadd_back(t_trush **lst, t_trush *new);
int	ft_trushlengh(t_trush *lst);
void	ft_addtotrush(void *ptr, t_trush **head, int nb);
void	reset_io(int io[2]);
void	save_io(int io[2]);
int ft_putchar(int c);
void	itsnull(char **newenv);
void	cleartrush(void);
void ft_signal(void);
void handle(int sig);
char *ft_concat(char *s1, char *s2);
int	ft_cd(char *dest);
int ft_checkflag(char *str);
int	ft_echo(char **line);
int	ft_env(char **env);
int isnum(char c);
long long	ft_atoi_long(const char *str);
int check_error_exit(char **command);
int	ft_exit(char **command);
int vars_equal(char *var);
char **vars_notexist(char *var, char **env);
int vars_exist(char *var, char **env, int index);
int	ft_pwd(void);
int	ft_isalnum(int c);
char **delete_vars(int index, char **env);
int vars_exists(char *var, char **env);
int check_errors(char **str);
int	ft_unset(char ***env, char **cmd);
int	ft_nbfiles(void);
int		ft_doublesize(char **names);
char	**ft_returngiven(char **names, char	*rgx);
char	**ft_simplewild(void);
int	ft_nbfilestwo(char *pattren);
char	**ft_wildrgex(char *pattern);
char	**ft_wildcard_(char *pattern);
int	ft_export(char **cmd, char ***env);
#endif
