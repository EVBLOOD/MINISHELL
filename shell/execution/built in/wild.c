#include "../../mini_shell.h"

// int getlen(t_list **str)
// {
// 	int i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }

int	ft_nbfiles(void)
{
	struct dirent	*ret;
	DIR				*dir;
	int				i;

	i = 1;
	dir = opendir(".");
	if (!dir)
		return (0);
	while((ret = readdir(dir)) != NULL)
	{
		if ((ret->d_type == DT_DIR || ret->d_type == DT_REG) && ret->d_name[0] != '.')
			i++;
	}
	closedir(dir);
	return (i);
}

// char **ft_wild(void)
// {
// 	DIR *dir;
// 	struct dirent *ret;
// 	char **list;

// 	dir = opendir(".");
// 	if (!dir)
// 		return(NULL);
// 	while((ret = readdir(dir)) != NULL)
// 	{
// 		if (ft_strncmp(ret->d_name, ".", ft_strlen(ret->d_name)) 
// 			&& ft_strncmp(ret->d_name, "..", ft_strlen(ret->d_name)))
// 		{
// 			currnt = malloc(sizeof(t_list));
// 			if (!ret)
// 				return (0);
// 			currnt->splited = ft_strdup(ret->d_name);
// 			currnt->next = NULL;
// 			ft_lstadd_back(node, currnt);
// 		}
// 	}
// 	closedir(dir);
// 	return(*node);
// }

char	**ft_simplewild(void)
{
	struct dirent	*ret;
	DIR				*dir;
	int				i;
	char			**names;

	i = -1;
	names = malloc(sizeof(char *) * ft_nbfiles());
	dir = opendir(".");
	if (!dir)
		return(NULL);
	while((ret = readdir(dir)) != NULL)
		if ((ret->d_type == DT_DIR || ret->d_type == DT_REG) && ret->d_name[0] != '.')
			names[++i] = ft_strdup(ret->d_name);
	names[++i] = NULL;
	closedir(dir);
	return (names);
}


// t_list **replace_wild_value(t_list **command, int i)
// {
// 	t_list *list;
// 	t_list  *templst;
// 	int y;
// 	t_list **temp;
// 	int len;
// 	y = -1;
// 	temp = command;

// 	len = getlen(command);
// 	list = ft_wild();
// 	templst = list;
// 	command = malloc(sizeof(t_list *) * (len + (2 * ft_lstlen(list))));
// 	if (!command)
// 		return(NULL);
// 	while(++y < i)
// 	{
// 		command[y] = malloc(sizeof(t_list));
// 		if (!command[y])
// 			return (NULL);
// 		if (temp[y]->TYPE != SPACES)
// 			command[y]->splited = ft_strdup(temp[y]->splited);
// 		else
// 			command[y]->splited = NULL;
// 		command[y]->TYPE = temp[y]->TYPE;
// 	}
	
// 	while (list)
// 	{
// 		command[y] = malloc(sizeof(t_list));
// 		if (!command[y])
// 			return (NULL);
// 		command[y]->splited = ft_strdup(list->splited);
// 		command[y]->TYPE = WORD;
// 		y++;
// 		if (list->next)
// 		{
// 			command[y] = malloc(sizeof(t_list));
// 			if (!command[y])
// 				return (NULL);
// 			command[y]->splited = NULL;
// 			command[y]->TYPE = SPACES;
// 			y++;
// 		}
// 		list = list->next;
// 	}

// 	while(temp[++i])
// 	{
// 		command[y] = malloc(sizeof(t_list));
// 		if (!command[y])
// 			return (NULL);
// 		command[y]->splited = ft_strdup(temp[i]->splited);
// 		command[y]->TYPE = temp[i]->TYPE;
// 		y++;
// 	}
// 	command[y] = NULL;
// 	return (command);
// }

// t_list **check_wild(t_list **command)
// {
// 	int i;
// 	i = -1;
// 	while (command[++i])
// 		if (command[i]->TYPE == SPACES)
// 			command[i]->splited = NULL;
// 	i = 0;
// 	while (command[i])
// 	{
// 		if(command[i]->TYPE != SPACES && !ft_strncmp(command[i]->splited, "*", ft_strlen(command[i]->splited)))
// 			command = replace_wild_value(command, i);
// 		i++;
// 	}
// 	return (command);
// }