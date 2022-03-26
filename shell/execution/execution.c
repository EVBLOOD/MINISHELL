/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:27:09 by sakllam           #+#    #+#             */
/*   Updated: 2022/03/26 17:21:41 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"


// void disp(t_list **list)
// {
// 	int i;
// 	i = 0;
// 	while (list[i])
// 	{
// 		if(list[i]->TYPE != SPACES)
// 			puts(list[i]->splited);
// 		i++;
// 	}
// 	puts("____________________");
// }




int	ft_ANDfuction(char position, t_tree *tree, char **env)
{
	int		ret;
	char	*path;
	char	**command;

	ret = 1;

	tree->elements = (tree->elements);
	command = ft_dealwithlist(tree->elements, env);
	path = ft_isacmd(command[0], env);
	if (path)
	{
		simple_cmd(path, command, env);
		ret = ft_getreturn();
	}
	else
		printf("minishell: %s:Command not found\n", command[0]);
	return (ret);
}



int execcmd(t_tree *tree, char **env)
{
	int		ret;
	char	*path;
	char	**command;

	ret = 1;
	tree->elements = check_wild(tree->elements);
	command = ft_dealwithlist(tree->elements, env);
	path = ft_isacmd(command[0], env);
	if (path)
	{
		simple_cmd(path, command, env);
		ret = ft_getreturn();
	}
	else
		printf("minishell: %s:Command not found\n", command[0]);
	ft_free(command);
	return (ret);
}

int	ft_ORfunction(char position, t_tree *tree, char **env)
{
	int		ret;
	char	*path;
	char	**command;

	ret = 1;
	tree->elements = (tree->elements);
	command = ft_dealwithlist(tree->elements, env);
	path = ft_isacmd(command[0], env);
	if (path)
	{
		simple_cmd(path, command, env);
		ret = ft_getreturn();
	}
	else
		printf("minishell: %s:Command not found\n", command[0]);
	return (ret);
}


int	executeredirections(t_tree *tree, t_env *newenv)
{
	char	*filename;
	char	**args;

	args = ft_dealwithlist(tree->elements, newenv);
	filename = args[0];
	while (lst && lst->TYPE != SPACES)
	{
		filename = ft_strjoin(filename, lst->)
		lst = lst->next;
	}
	free(filename);
}

int	ft_execution(char **env, t_tree *tree, char position, t_execute args)
{
	pid_t pid;
	int pip[2];
	int	i;
	int fd;
	char *path;
	char **envc;

	i = 0;
	if (tree->type != 15)
		args.parrent = tree;
	if (tree->type == OR)
		i = 1;
	if (tree->left)
		i = ft_execution(env, tree->left, 'l', args);
	if (tree->type == AND && i)
			return (i);
	else if (tree->type == OR && !i)
		return (i);
	if (tree->right)
		i = ft_execution(env, tree->right, 'r', args);
	if (tree->type == RDIN || tree->type == RDHER || tree->type == RDOUT || tree->type == RDAPP)
	{
		if (i == -1)
			return(123);
		args.pipe[0] = i;
		i = 0;
	}
	else if (tree->type != PIPE && tree->type != AND
		&& tree->type != OR && tree->type != RDAPP && tree->type != RDHER
		&& tree->type != RDIN && tree->type != RDOUT)
	{
		if (position != 'p')
		{
			if (args.parrent->type == AND)
				return (ft_ANDfuction(position, tree, env));
			else if (args.parrent->type == OR)
				return (ft_ORfunction(position, tree, env));
			else if (args.parrent->type == PIPE)
				return (ft_PIPEfunction(position, tree, env, 0, pip));
			else if (args.parrent->type == RDAPP || args.parrent->type == RDHER
				|| args.parrent->type || args.parrent->type == RDOUT)
				return (ft_RDRfunction(position, tree, env, args.parrent->type, args.pipe[0]));
		}
		else
			return(execcmd(tree, env));
	}
	if (tree->type == PIPE)
	{
		puts("first");
		waitpid(-1, NULL, 0);
		puts("second");
		waitpid(-1, NULL, 0);
		puts("last");
	}
	return (i);
}