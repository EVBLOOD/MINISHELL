/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakllam <sakllam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 13:55:00 by sakllam           #+#    #+#             */
/*   Updated: 2022/04/18 05:59:46 by sakllam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

char	*ft_expand_sq(t_list *list)
{
	int		i;
	char	*str;

	str = malloc(ft_strlen(list->splited) - 1);
	i = 1;
	while (list->splited[i] != 39)
	{
		str[i - 1] = list->splited[i];
		i++;
	}
	str[i - 1] = '\0';
	return(str);
}

char	*ft_substrlist(t_list **list, int start, int end)
{
	int		i;
	int		extra_i;
	char	*str;
	char	*tmp;

	i = start;
	str = ft_strdup("");
	while (i <= end)
	{

		if (list[i]->TYPE == VARIABLE)
		{
			extra_i = 1;
			if (i == start)
			{
				while (list[i]->expanded[extra_i])
				{
					tmp = str;
					str = ft_strjoin(str, list[i]->expanded[extra_i]);
					free(tmp);
					extra_i++;
				}
			}
			if (i == end)
			{
				tmp = str;
				str = ft_strjoin(str, list[i]->expanded[0]);
				free(tmp);
			}
		}
		if (list[i]->TYPE == SQ)
		{
			tmp = str;
			str = ft_strjoin(str, list[i]->splited);
			free(tmp);
		}
		if (list[i]->TYPE == DQ)
		{
			tmp = str;
			str = ft_strjoin(str, list[i]->splited);
			free(tmp);
		}
		if (list[i]->TYPE == WORD)
		{
			tmp = str;
			str = ft_strjoin(str, list[i]->splited);
			free(tmp);
		}
		if (list[i]->TYPE == WILD)
		{
			tmp = str;
			str = ft_strjoin(str, "*");
			free(tmp);
			while (list[i] && list[i]->TYPE == WILD)
				i++;
			i--;
		}
		i++;
	}
	return (str);
}

t_befexec	*ft_createnode(char *str)
{
	t_befexec	*node;

	node = malloc(sizeof(t_befexec));
	node->ofcvalue = str;
	node->next = NULL;
	return (node);
}

void	ft_normalnodeslist(t_list **list, int start, int end, t_befexec **all)
{
	int	i;
	int	extra_i;
	char	*str;
	char	*tmp;

	i = start;
	str = ft_strdup("");
	while (i <= end)
	{
		if (list[i]->TYPE == VARIABLE)
		{
			extra_i = 0;
			if (i == end)
			{
				tmp = str;
				str = ft_strjoin(str, list[i]->expanded[0]);
				free (tmp);
				ft_ofcadd_back(all, ft_createnode(str)); // check for null;
			}
			if (i == start)
			{
				extra_i++;
				while (list[i]->expanded[extra_i])
				{
					ft_ofcadd_back(all, ft_createnode(list[i]->expanded[extra_i]));
					extra_i++;
				}			
			}

		}
		else if (list[i]->TYPE == DQ)
		{
			tmp = str;
			str = ft_strjoin(str, list[i]->splited);
			free (tmp);
		}
		else if (list[i]->TYPE == SQ)
		{
			tmp = str;
			str = ft_strjoin(str, list[i]->splited);
			free (tmp);
		}
		else if (list[i]->TYPE == WORD)
		{
			tmp = str;
			str = ft_strjoin(str, list[i]->splited);
			free (tmp);
		}
		else if (list[i]->TYPE == SPACES || !list[i + 1])
		{
			ft_ofcadd_back(all, ft_createnode(str));
		}
		i++;
	}
}

t_befexec	*ft_expandingwildcard(t_list **list, char **env, int red)
{
	int			i;
	int			j;
	int			laststart;
	int			wild;
	t_befexec	*head;
	char		**_wild;

	i = 0;
	laststart = 0;
	wild = 0;
	head = NULL;
	while (list[i])
	{
		if (list[i]->TYPE == WILD)
			wild = 1;
		if (list[i]->TYPE == VARIABLE)
		{
			if ((!list[i]->expanded[0] || list[i]->expanded[1]) && wild)
			{
				_wild = ft_wildcard_(ft_substrlist(list, laststart, i));
				j = 0;
				while (_wild[j])
				{
					ft_ofcadd_back(&head, ft_createnode(_wild[j]));
					j++;
				}
				// ft_substrlist(list, laststart, i);
				wild = 0;
			}
			else if ((!list[i]->expanded[0] || list[i]->expanded[1]) && !wild)
			{
				// ewa check this asidi 
				ft_normalnodeslist(list, laststart, i, &head);
			}
			if (!list[i]->expanded[0] || list[i]->expanded[1])
				laststart = i;
		}
		else if (list[i]->TYPE == SPACES || !list[i + 1])
		{
			if (wild)
			{
				_wild = ft_wildcard_(ft_substrlist(list, laststart, i));
				j = 0;
				while (_wild[j])
				{
					ft_ofcadd_back(&head, ft_createnode(_wild[j]));
					j++;
				}
				wild = 0;
			}
			else
			{
				ft_normalnodeslist(list, laststart, i, &head);
			}
			laststart = i;
			if (list[i]->TYPE == SPACES && red)
				break;
		}
		i++;
	}
	return (head);
}

void	ft_replaceall(t_list **list, char **env, int red)
{
	int		i;
	char	*str;

	i = 0;
	while (list[i])
	{
		if (list[i]->TYPE == VARIABLE)
		{
			list[i]->expanded = ft_expandvariables(list[i], env);
			if (list[0]->expanded[0] && list[0]->expanded[0][0] == ' ' && red)
				break;
		}
		if (list[i]->TYPE == SQ)
		{
			str = ft_expand_sq(list[i]);
			free(list[i]->splited);
			list[i]->splited = str;
		}
		if (list[i]->TYPE == DQ)
		{
			str = ft_expand_dq(list[i], env);
			free(list[i]->splited);
			list[i]->splited = str;	
		}
		if (list[i]->TYPE == WORD)
		{
			str = ft_strdup(list[i]->splited);
			free(list[i]->splited);
			list[i]->splited = str;	
		}
		if (list[i]->TYPE == SPACES && red)
			break;
		i++;
	}
}


char **ft_convertfromlisttochar(t_befexec *list)
{
	int		i;
	char	**cnv;

	i = ft_ofclengh(list);
	cnv = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (list)
	{
		cnv[i] = list->ofcvalue;
		i++;
		list = list->next;
	}
	cnv[i] = NULL;
	return (cnv);
}

char	*ft_replaceandjoin(char **str, char *tojoin)
{
	char	*tmp;

	tmp = *str;
	*str = ft_strjoin(*str, tojoin);
	free(tmp);
	return (*str);
}


void	ft_wildmergin(char **str, t_befexec **head)
{
	char **names;
	int	i;

	names = ft_wildcard_(*str);
	i = 0;
	while (names[i])
	{
		ft_ofcadd_back(head, ft_createnode(names[i]));
		i++;
	}
}

int	ft_countstars(char *str, int wild)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '*')
			count++;
		i++;
	}
	return (count + wild);
}

void ft_varmerging(t_list *list, char **str, int *red, int *wild, t_befexec **head)
{
	int	i;

	i = 0;
	while (list->expanded[i])
	{
		if (list->expanded[i][0] == ' ' && ft_strlen(*str) > 0)
		{
			if (ft_countstars("", *wild) > 0)
				ft_wildmergin(str, head);
			ft_ofcadd_back(head, ft_createnode(*str));
			*str = ft_strdup("");
			if (*red)
				*red = -1;
		}
		if (list->expanded[i][0] != ' ')
		{
			*str = ft_replaceandjoin(str, list->expanded[i]);
		}
		i++;
	}
}

char	*ft_wildmerging(t_list **list, char **str, int *wild, int *i)
{
	*str = ft_replaceandjoin(str, "*");
	(*wild)++;
	while (list[*i] && list[*i]->TYPE == WILD)
		(*i)++;
	(*i)--;
	return (*str);
}

char	*ft_dq_sq_wrdmerging(t_list *list, char **str, int *wild)
{
	int	i;

	i = 0;
	*str = ft_replaceandjoin(str, list->splited);
	while (list->splited[i])
	{
		if (list->splited[i] == '*')
			(*wild)--;
		i++;
	}
	return (*str);
}

t_befexec	*ft_merging(t_list **list, char **env, int red)
{
	t_befexec	*head;
	int			wild;
	int			i;
	char		*str;

	wild = 0;
	i = 0;
	head = NULL;
	str = ft_strdup("");
	if (list[i]->TYPE == SPACES)
		i++;
	while (list[i])
	{
		if (list[i]->TYPE == VARIABLE)
			ft_varmerging(list[i], &str, &red, &wild, &head);
		if (red == -1)
			break ;
		if (list[i]->TYPE == DQ || list[i]->TYPE == SQ || list[i]->TYPE == WORD)
			str = ft_dq_sq_wrdmerging(list[i], &str, &wild);
		if (list[i]->TYPE == WILD)
			str = ft_wildmerging(list, &str, &wild, &i);
		if (list[i]->TYPE == SPACES || !list[i + 1])
		{
			if (wild > 0)
				ft_wildmergin(&str, &head);
			else
				ft_ofcadd_back(&head, ft_createnode(str));
			if (red)
				break;
			str = ft_strdup("");
			wild = 0;
		}
		i++;
	}
	return (head);
}

char	**ft_dealwithlist(t_list **list, char **env, int red)
{
	char		**converted;
	t_befexec	*ret;
	int			i;

	ft_replaceall(list, env, red);
	ret = ft_merging(list, env, red);
	converted = ft_convertfromlisttochar(ret);
	return (converted);
}