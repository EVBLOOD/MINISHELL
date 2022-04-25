#include "../mini_shell.h"

void free_list(t_list *list)
{
	t_list *temp;

	while (list)
	{
		temp = list;
		list = list->next;
		if (temp->splited)
			free(temp->splited);
		free(temp);
	}
}

void ft_free(char **element)
{
	int i;

	i = -1;
	while(element[++i])
		free(element[i]);
	free(element);
	element = NULL;
}

void ft_freelist(t_list **element)
{
	int i;

	i = -1;
	while (element[i])
		free_list(element[i]);
	free(element);
}

// void free_tree(t_tree *tree)
// {
// 	int i;

// 	i = 0;
// 	if(tree->left)
// 		free_tree(tree->left);
// 	if(tree->right)
// 		free_tree(tree->right);
// 	if (tree->element)
// 		ft_free(tree->element);
// 	free(tree);
// }