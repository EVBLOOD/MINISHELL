/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 13:03:19 by sakllam           #+#    #+#             */
/*   Updated: 2022/03/22 17:17:06 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	ft_execv(char **cmd, t_env *env)
// {
// 	pid_t pid;
// 	char *path;
// 	int status;
// 	int ret;
// 	char **en;
// 	// check_var(&env, cmd);
// 	ret = check_builtins(cmd, &env);
// 	if(!ret)
// 		return (0);
// 	else if(ret < 0)
// 		return (256);
// 	else if(ret == 1)
// 	{
// 		path = md(cmd[0], env);
// 		en = ft_clone2(env);
// 		if (!path)
// 			return(printf("command not found\n"));
// 		pid = fork();
// 		if (!pid)
// 		{
// 			if (execve(path, cmd, en))
// 			{
// 				perror("minishell");
// 				exit(1);
// 			}
// 		}
// 		waitpid(pid, &status, 0);
// 		free(path);
// 		free(en);
// 	}
// 	 return (status);
// }


pid_t	midel_first_partpipe(int *wr_fd, char *path, char **cmd, char **env)
{
	pid_t	id;

	pipe(wr_fd);
	id = fork();
	if (id == 0)
	{
		close(wr_fd[0]);
		dup2(wr_fd[1], 1);
		if (execve(path, cmd, env) < 0)
			exit (1);
	}
	return (id);
}

void	main_pipe(int *wr_fd)
{
	close(wr_fd[1]);
	dup2(wr_fd[0], 0);
}

pid_t	simple_cmd(char *path, char **cmd, char **env)
{
	pid_t	id;

	id = fork();
	if (id == 0)
	{
		if (execve(path, cmd, env) < 0)
		{
			perror("minishell");
			exit(1);
		}
	}
	return (id);
}

int	ft_getreturn(pid_t id)
{
	int	ret;

	waitpid(id, &ret, 0);
	return (ret);
}

int	ft_RDIN(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("file");
		return (fd);
	}
	dup2(fd, 0);
	return (fd);
}

int	ft_RDOUT(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 00644);
	if (fd < 0)
	{
		perror("file");
		return (fd);
	}
	dup2(fd, 1);
	return (fd);
}

int	ft_RDAPP(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 00644);
	if (fd < 0)
	{
		perror("file");
		return (fd);
	}
	return (fd);
}

// int	ft_strcmp(const char *s1, const char *s2)
// {
// 	int				i;
// 	unsigned char	*st1;
// 	unsigned char	*st2;

// 	i = 0;
// 	st1 = (unsigned char *) s1;
// 	st2 = (unsigned char *) s2;
// 	while (st1[i] || st2[i])
// 	{
// 		if (st1[i] != st2[i])
// 			return (st1[i] - st2[i]);
// 		i++;
// 	}
// 	return (0);
// }

// t_her	*ft_RDHER(char *END)
// {
// 	t_her	*head;
// 	t_her	*node;
// 	char	*line;

// 	head = NULL;
// 	while (42)
// 	{
// 		line = readline("> ");
// 		if (!ft_strcmp(line, END))
// 			break;
// 		node = malloc(sizeof(t_her));
// 		node->value = line;
// 		node->next = NULL;
// 		ft_lstadd_backher(&head, node);
// 	}
// 	return (head);
// }

// int	ft_herdocstart(t_her *list)
// {
// 	while (list)
// 	{
// 		write(0, list->value, ft_strlen(list->value));
// 		list = list->next;
// 	}
// 	return (0);
// }

// // int	ft_redirections(t_tree *tree)
// // {
// // 	if (tree->type == RDIN)
// // 	{

// // 	}
// // 	else if (tree->type == RDOUT)
// // 	{

// // 	}
// // 	else if (tree->type == RDAPP)
// // 	{

// // 	}
// // 	else
// // 	{

// // 	}
// // }

pid_t	ft_ANDfuction(char position, t_tree *tree, char **env)
{
	pid_t	pid;
	int		ret;
	char	*path;
	char	**command;

	ret = 1;
	command = 
	path = ft_isacmd(tree->element[0], env);
	if (path)
	{
		pid = simple_cmd(path, tree->element, env);
		ret = ft_getreturn(pid);
	}
	else
		printf("Command not found\n");
	return (ret);
}

int	ft_ORfunction(char position, t_tree *tree, char **env)
{
	pid_t	pid;
	int		ret;
	char	**envc;
	char	*path;

	ret = 1;
	envc = ft_clone2(env);
	path = ft_isacmd(tree->element[0], env);
	if (path)
	{
		pid = simple_cmd(path, tree->element, envc);
		ret = ft_getreturn(pid);
	}
	else
		printf("Command not found\n");
	return (ret);
}

int	ft_PIPEfunction(char position, t_tree *tree, char **env, int lastpipe)
{
	pid_t	ret;
	char	**envc;
	char	*path;
	
	path = ft_isacmd(tree->element[0], env);;
	envc = ft_clone2(env);
	if (position == 'l')
	{
		ret = midel_first_partpipe(wr_fd, path, tree->element, envc);
	}
	else
	{
		if (lastpipe)
			ret = midel_first_partpipe(wr_fd, path, tree->element, envc);
		else
			ret = simple_cmd(path, tree->element, envc);
	}
	return (ret);
}

int	ft_RDRfunction(char position, t_tree *tree, t_env *env)
{
	if (position == 'l')
		printf("redir file:%s->l\n", tree->element[0]);
		//files or EOF to give to cmd
	else
		printf("redir cmd:%s->r\n", tree->element[0]);
		//simple cmd
	return (1);	
}

// int	ft_WORDfunction(char position, t_tree *tree, t_env *env)
// {
// 	pid_t	id;
// 	char	**chenv;
// 	// chenv = ft_clone2(env);
// 	// id = simple_cmd(char *path, tree->element, chenv);
// 	//parent is just a cmd --> NB: don't forget that you have tree->element[words]
// 	// do not forget to check if it's builed in
// 	return (5);
// }

char	*ft_removeqts(char *words)
{
	char	*ret;
	char	qoute;
	int		i;
	int		j;

	qoute = words[0];
	i = 0;
	j = -1;
	ret = malloc(ft_strlen(words) - 1);
	while (words[++i] != qoute)
		ret[++j] = words[i];
	ret[++j] = '\0';
	return (ret);
}

// int	ft_varvalidatin(int c)shell

// {
// 	if (!ft_isalpha(c) && !ft_isdigit(c) && c != '_')
// 		return (0);
// 	return (1);
// }

// int	ft_countletters(char *words, t_env *env, int i)
// {
// 	char *var;
// 	char *ret;
// 	int	j;

// 	var = malloc(i + 1);
// 	j = -1;
// 	while (i)
// 	{
// 		var[++j] = words[j];
// 		i--;
// 	}
// 	var[++j] = '\0';
// 	ret = ft_getvariable(&env, var);
// 	j = ft_strlen(ret);
// 	free(ret);
// 	free(var);
// 	return (j);
// }

// char	*ft_varresult(char *words, t_env *env, int i)
// {
// 	char *var;
// 	char *ret;
// 	int	j;

// 	var = malloc(i + 1);
// 	j = -1;
// 	while (i)
// 	{
// 		var[++j] = words[j];
// 		i--;
// 	}
// 	var[++j] = '\0';
// 	ret = ft_getvariable(&env, var);
// 	free(var);
// 	return (ret);
// }

// int	ft_countfuture(char *words, t_env *env)
// {
// 	int	i;
// 	int	j;
// 	int	count;

// 	i = 0;
// 	count = 0;
// 	while (words[i])
// 	{
// 		if (words[i] == '$')
// 		{
// 			// for $?
// 			j = 0;
// 			if (ft_isdigit(words[i + 1]))
// 			{
// 				j = 1;
// 				count += ft_countletters(&words[i], env, j);
// 			}
// 			else
// 			{
// 				while (ft_varvalidatin(words[i + 1 + j]))
// 					j++;
// 				count += ft_countletters(&words[i], env, j + 1);
// 				i = i + j + 1;
// 			}
// 		}
// 		else
// 			(count++, i++);
// 	}
// 	return (count);
// }

// char	*ft_newresult(char *words, t_env *env)
// {
// 	char	*ret;
// 	char	*rm_qoutes;
// 	char	*tmp;
// 	int		i;
// 	int		j;
// 	int		jj;

// 	rm_qoutes = ft_removeqts(words);
// 	j = ft_countfuture(words, env);
// 	ret = malloc(j + 1);
// 	i = 0;
// 	while (words[i])
// 	{
// 		if (words[i] == '$')
// 		{
// 			// for $?
// 			jj = 0;
// 			if (ft_isdigit(words[i + 1]))
// 			{
// 				jj = 1;
// 				tmp = ft_varresult(&words[i], env, jj);
// 			}
// 			else
// 			{
// 				while (ft_varvalidatin(words[i + jj + 1]))
// 					jj++;
// 				tmp = ft_varresult(&words[i], env, jj + 1);
// 				i = i + jj + 1;
// 			}
// 			jj = 0;
// 			while (tmp[jj])
// 			{ 
// 				ret[j] = tmp[jj];
// 				jj++;
// 				j++;
// 			}
// 			free(tmp);
// 		}
// 		else
// 			(ret[j] = words[i], i++, j++);
// 	}
// 	free (rm_qoutes);
// 	return (ret);
// }

// int ft_dailwithwords(char **words, t_env *env)
// {
// 	int		i;
// 	char	*stock;

// 	i = -1;
// 	while (words[++i])
// 	{
// 		if (words[i][0] == 34)
// 		{
// 			stock = words[i];
// 			words[i] = ft_newresult(words[i], env);
// 			free(stock);

// 		}
// 		else if (words[i][0] == 39)
// 		{
// 			stock = words[i];
// 			words[i] = ft_removeqts(words[i]);
// 			free(stock);
// 		}
// 		else if (words[i][0] == '$')
// 		{
// 			stock = words[i];
// 			words[i] = ft_getvariable(env, words[i]);
// 			free(stock);
// 		}
// 	}
// 	return (0);
// }

int *wr_fd;

pid_t	ft_execution(t_env *env, t_tree *tree, char position, t_tree *parrent, int pipe)
{
	int	i;
	char *path;
	pid_t pid;
	char **envc;

	i = 0;
	int ispipe = 0;
	// if (tree->type == PIPE)
	// 	main_pipe(wr_fd);
	// if (parrent && parrent->type == PIPE && tree->type == PIPE)
	// 	ispipe = 1;
	if (parrent->type == OR)
		i = 1;
	if (tree->left)
		i = ft_execution(env, tree->left, 'l', tree, ispipe);
	if (tree->type == AND && i)
			return (i);
	else if (tree->type == OR && !i)
		return (i);
	if (tree->right)
		i = ft_execution(env, tree->right, 'r', tree, ispipe);
	if (tree->type != PIPE && tree->type != AND
		&& tree->type != OR && tree->type != RDAPP && tree->type != RDHER
		&& tree->type != RDIN && tree->type != RDOUT)
	{
	 	if (parrent->type == AND)
			return (ft_ANDfuction(position, tree, env));
		else if (parrent->type == OR)
			return (ft_ORfunction(position, tree, env));
		else if (parrent->type == PIPE)
			return (ft_PIPEfunction(position, tree, env, 0));
		// else if (parrent->type == RDAPP || parrent->type == RDHER
		// 	|| parrent->type == RDIN || parrent->type == RDOUT)
		// 	return (ft_RDRfunction(position, tree, env));
		else
		{	
			path = ft_isacmd(tree->element[0] ,env);
			envc = ft_clone2(env);
			if (path)
				pid = simple_cmd(path, tree->element, envc);
			else
				printf("Command not found\n");
			return(ft_getreturn(pid));
		}

	}
	// waitpid(-1, 0, 0);
	// waitpid(-1, 0, 0);
	return (i);
}



// if (tree->typr == PIPE)
// {
// 	int pfd[2];
// 	pipe(pfd);

// 	// gauche
// 	if (fork() == 0) {

// 		// redirection de output

// 		// call ft_execution
// 		ft_execution(tree->left);
// 		exit(0);
// 	}

// 	// droit
// 	if (fork()  == 0) {

// 		// redirection input

// 		// (l'executionn ici c'est automatiquement fait dans un enfant process)
// 		ft_execute(tree->right);

// 		// garantir le exit (dans l'enfant processus)
// 		exit(0);
// 	}


// 	// close pipe
// 	close(pfd[0]);
// 	close(pfd[1]);

// 	// atander 2 fois (sans ordre)
// 	wait(NULL);
// 	wait(NULL);
// }
