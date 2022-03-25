#include "../minishell.h"

int get_lenenv(t_env *env)
{
	t_env *temp;
	int i;

	temp = env;
	i = 0;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

char **ft_clone2(t_env *env)
{
	t_env *temp;
	char **cloned;
	int		i;
	int		len;

	temp = env;
	i = 0;
	len = get_lenenv(env);
	cloned = malloc(sizeof(char *) * (len + 1));
	if (!cloned)
		return (NULL);
	while(temp)
	{
		cloned[i++] = ft_strdup(temp->value);
		temp = temp->next;
	}
	cloned[i] = NULL;
	return(cloned);
}