// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   before_exec.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/03/20 13:55:00 by sakllam           #+#    #+#             */
// /*   Updated: 2022/03/31 11:58:59 by sakllam          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../mini_shell.h"


// char	*ft_expand_sq(t_list *list)
// {
// 	int		i;
// 	char	*str;

// 	str = malloc(ft_strlen(list->splited) - 1);
// 	i = 1;
// 	while (list->splited[i] != 39)
// 	{
// 		str[i - 1] = list->splited[i];
// 		i++;
// 	}
// 	str[i - 1] = '\0';
// 	return(str);
// }

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	int		i;
// 	char	*p;

// 	i = 0;
// 	if (!s)
// 		return (NULL);
// 	if (ft_strlen(s + start) < len)
// 		p = (char *) malloc((ft_strlen(s + start) + 1) * sizeof(char));
// 	else
// 		p = (char *) malloc(((int) len + 1) * sizeof(char));
// 	if (!p)
// 		return (NULL);
// 	while (i < (int) len && s[i + start] && !(start >= ft_strlen(s)))
// 	{
// 		p[i] = s[i + start];
// 		i++;
// 	}
// 	p[i] = '\0';
// 	return (p);
// }


// int	ft_spacevar(t_list *element)
// {
// 	char	*str;

// 	if (element->TYPE != VARIABLE)
// 		return (1);
// 	str = ft_strtrim(element->splited, " \t\n\v\f\r");
// 	if (!ft_strlen(str) && ft_strlen(element->splited))
// 	{
// 		free(str);
// 		return (0);
// 	}
// 	free(str);
// 	return (1);
// }

// int	ft_countwildexpantion(void)
// {
// 	char	**files;
// 	int		i;

// 	i = 0;
// 	files = ft_simplewild();
// 	while (files[i])
// 	{
// 		free(files[i]);
// 		i++;
// 	}
// 	free(files);
// 	return (i);
// }

// // void	ft_expandsimplewild(void)
// // {
// // 	char	**files;

// // 	files = ft_simplewild();
// // 	return (files);
// // }



// int	ft_variablemanup(t_list *list, char **env, t_befexec *head)
// {
// 	if (list->TYPE == VARIABLE)
// 	{

// 	}
// 	return (0);
// }

// int	ft_wildmanup(t_list **list, int *i)
// {
// 	int	count;

// 	count = 0;
// 	if (list[*i]->TYPE == WILD)
// 	{
// 		count = ft_countwildexpantion();
// 		while (list[*i] && list[*i]->TYPE == WILD)
// 			(*i)++;
// 		(*i)--;
// 	}
// 	return (count);
// }




// int	ft_spacesmanup(t_list **list, int *end, int *red, int *start)
// {
// 	int	count;
// 	int	tmp;

// 	count = 0;
// 	if (list[*end]->TYPE == SPACES || !ft_spacevar(list[*end]))
// 	{
// 		// while (*start < *end)
// 		// {
// 		// 	count += ft_variablemanup(list[*start], env);
// 		// 	(*start)++;
// 		// }
// 		ft_variablesrep(list, *start, *end);
// 		while (list[*end] && !ft_spacevar(list[*end]))
// 			(*end)++;
// 		(*end)--;
// 		count++;
// 		if (red)
// 			*red = -1;
// 	}
// 	*start = *end;
// 	return (count);
// }

// int	ft_isred(int *red)
// {
// 	if (*red == -1)
// 	{
// 		*red = 1;
// 		return (1);
// 	}
// 	return (0);
// }

// t_befexec	*ft_count_replace_before(t_list **list, char **env, int red)
// {
// 	int	i;
// 	int	start;
// 	t_befexec	*head;

// 	i = 0;
// 	start = 0;
// 	head = NULL;
// 	while (list[i])
// 	{
// 		ft_variablemanup(list[i], env, &head);
// 		ft_dqmanup(list[i], env);
// 		ft_sqmanup(list[i]);
// 		// count += ft_wildmanup(list, &i);
// 		ft_spacesmanup(list, &i, &red, &start);
// 		if (ft_isred(&red))
// 			break;
// 		i++;
// 	}
// 	return (head);
// }

// char	**ft_dealwithlist(t_list **list, char **env, int red)
// {
// 	int		i;
// 	int		x;
// 	int		count;
// 	char	*str;
// 	char	**args;
// 	char	**files;

// 	i = -1;
// 	count = 1;
	
// 	// while (list[++i])
// 	// {
// 	// 	// printf("%d\n", list[i]->TYPE);
// 	// 	if (list[i]->TYPE == VARIABLE)
// 	// 		count += ft_expandvariables(list[i], env);
// 	// 	if (list[i]->TYPE == WILD)
// 	// 	{
// 	// 		count += ft_countwildexpantion();
// 	// 		while (list[i] && list[i]->TYPE == WILD)
// 	// 			i++;
// 	// 		i--;
// 	// 	}
// 	// 	if (list[i]->TYPE == DQ)
// 	// 		ft_expand_dq(list[i], env);
// 	// 	if (list[i]->TYPE == SQ)
// 	// 		ft_expand_sq(list[i]);
// 	// 	if (list[i]->TYPE == SPACES || !ft_spacevar(list[i]))
// 	// 	{
// 	// 		while (list[++i] && !ft_spacevar(list[i]));
// 	// 		i--;
// 	// 		count++;
// 	// 		if (red)
// 	// 			break;
// 	// 	}
// 	// printf("checking :%d\n", count);

// 	// }
// 	puts("DONE");
// 	printf("%d\n", count);
// 	ft_count_replace_before();
// 	args = malloc(sizeof(char *) * (count + 1));
// 	i = -1;
// 	count = -1;
// 	str = ft_strdup("");
// 	while (list[++i])
// 	{
// 		if (list[i]->TYPE != VARIABLE && list[i]->TYPE != WILD && list[i]->TYPE != SPACES && ft_spacevar(list[i]))
// 			str = ft_strjoin(str, list[i]->splited);
// 		if (list[i]->TYPE == WILD)
// 		{
// 			x = -1;
// 			files = ft_simplewild();
// 			while (files[++x])
// 				args[++count] = files[x];
// 			while (list[i] && list[i]->TYPE == WILD)
// 				i++;
// 			if (!list[i])
// 				break ;
// 			i--;
// 		}
// 		if (list[i]->TYPE == VARIABLE)
// 		{
// 			x = -1;
// 			files = ft_splitvar(list[i]->splited);
// 			str = ft_strjoin(str, files[++x]);
// 			while (files[++x])
// 			{
// 				args[++count] = str;
// 				str = files[x];
// 			}
// 		}
// 		if ((i || !list[i + 1]) && (list[i]->TYPE == SPACES || !list[i + 1]
// 			|| (*str && !ft_spacevar(list[i]))))
// 		{
// 			args[++count] = str;
// 			str = ft_strdup("");
// 			if (red)
// 				break;
// 		}
// 	}
// 	free(str);	
// 	args[++count] = NULL;
// 	count = -1;
// 	while (args[++count])
// 		puts(args[count]);
// 	return (args);
// }

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// void	ft_isdoubleq(t_list *list, char **env, t_befexec **head)
// {
// 	t_befexec	*node;

// 	if (list->TYPE == DQ)
// 	{
// 		node = malloc(sizeof(t_befexec));
// 		node->value = malloc(sizeof(char *) * 2);
// 		node->value[0] = ft_expand_dq(list, env);
// 		node->value[1] = NULL;
// 		node->next = NULL;
// 		ft_bexadd_back(node, head);
// 	}
// }

// void	ft_issingleq(t_list *list, t_befexec **head)
// {
// 	t_befexec	*node;

// 	if (list->TYPE == SQ)
// 	{
// 		node = malloc(sizeof(t_befexec));
// 		node->value = malloc(sizeof(char *) * 2);
// 		node->value[0] = ft_expand_sq(list);
// 		node->value[1] = NULL;
// 		node->next = NULL;
// 		ft_bexadd_back(node, head);
// 	}
		
// }

// void ft_isavar(t_list *list, char **env, t_befexec **head)
// {
// 	t_befexec	*node;

// 	if (list->TYPE == VARIABLE)
// 	{
// 		node = malloc(sizeof(t_befexec));
// 		node->value = ft_expandvariables(list, env);
// 		node->next = NULL;
// 		ft_bexadd_back(node, head);
// 	}
// }

// t_befexec	*ft_nodeofccreation(char *str)
// {
// 	t_befexec	*node;

// 	node = malloc(sizeof(t_befexec));
// 	node->ofcvalue = str;
// 	node->next = NULL;
// 	return (node);
// }

// t_befexec	*ft_ofcdesterb(t_befexec *old)
// {
// 	t_befexec	*head;
// 	char		*str;
// 	char		*tmp;
// 	int			i;

// 	(str = ft_strdup(""), head = NULL);
// 	while (old)
// 	{
// 		if (sizeof(old->value) > (sizeof(t_befexec *) * 2))
// 		{
// 			i = 0;
// 			while (old->value[i])
// 			{
// 				tmp = str;
// 				str = ft_strjoin(str, old->value[i]);
// 				free(tmp);
// 				if (old->value[i + 1] == NULL)
// 					break;
// 				ft_ofcadd_back(&head, ft_nodeofccreation(str));
// 				str = ft_strdup("");
// 				i++;
// 			}
// 		}
// 		else
// 		{
// 			tmp = str;
// 			str = ft_strjoin(str, old->value[0]);
// 			free(tmp);
// 		}
// 		old = old->next;
// 	}
// 	ft_ofcadd_back(&head, ft_nodeofccreation(str));
// 	return (head);
// }

// char	*ft_wildfollowing(t_list **list, int *index)
// {

// }

// void	ft_freeforofc(t_befexec **head)
// {
// 	t_befexec	*tmp;
// 	int			i;

// 	while ((*head))
// 	{
// 		i = 0;
// 		tmp = (*head);
// 		while (tmp->value[i])
// 		{
// 			free(tmp->value[i]);
// 			i++;
// 		}
// 		free(tmp->value);
// 		(*head) = (*head)->next;
// 		free(tmp);
// 	}
// 	(*head) = NULL;
// }

// char	*ft_getvaluestr(t_befexec *head)
// {
// 	t_befexec	*tmp;

// 	tmp = NULL;
// 	while (head)
// 	{
// 		tmp = head;
// 		head = head->next;
// 	}
// 	if (!tmp)
// 		return(ft_strdup(""));
// 	return(ft_strdup(tmp->ofcvalue));
// }

// void	ft_iswild(t_list **list, int *index, t_befexec **head, t_befexec **ofc)
// {
// 	char		*str;
// 	char		*tmp;
// 	t_befexec	*node;
// 	int			i;
// 	ft_ofcadd_back(&ofc, ft_ofcdesterb(*head));
// 	str = ft_getvaluestr(*head);
// 	ft_freeforofc(head);
// 	tmp = str;
// 	str = ft_strjoin(str, "*");
// 	free(tmp);
// 	ft_gettherest()
// }

// t_befexec	*ft_beforeexecpartone(t_list **list, char **env, int red)
// {
// 	t_befexec	*head;
// 	t_befexec	*ofc;
// 	int			i;
// 	int			start;

// 	i = 0;
// 	start = 0;
// 	ofc = NULL;
// 	head = NULL;
// 	while (list[i])
// 	{
// 		ft_iswild(list, &i, &head, &ofc);
// 		ft_isavar(list[i], env, &head);
// 		ft_isdoubleq(list[i], env, &head);
// 		ft_issingleq(list[i], &head);
// 		ft_ispaceorvarspace(list, &i, &head, &ofc);
// 		i++;
// 	}
// 	return (head);
// }


// char	**ft_dealwithlist(t_list **list, char **env, int red)
// {
// 	t_befexec	*head;
// 	char		**args;

// 	head = ft_beforeexecpartone(list, env, red);
// 	while ()
// 	{

// 	}
// }