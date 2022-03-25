#include "../../mini_shell.h"

int	ft_checkexistence(char *line)
{
	if (access(line, X_OK))
		return (2);
	if (access(line, F_OK))
		return (1);
	return (0);
}

char *ft_alphajoin(char *line, char *path)
{
	int		i;
	int		j;
	int		x;
	char	*ret;

	ret = (char *)malloc(sizeof(char) * (ft_strlen(line) + ft_strlen(path) + 2));
	if (!ret)
		return (NULL);
	i = -1;
	while (path[++i])
		ret[i] = path[i];
	ret[i++] = '/';
	j = -1;
	while (line[++j])
		ret[i++] = line[j];
	ret[i] = '\0';
	return (ret);
}

char	*ft_match(char *splited, char *cmd)
{
	char	*path;

	path = ft_alphajoin(cmd, splited);
	if (!ft_checkexistence(path))
		return (path);
	free(path);
	return (NULL);
}

char	*ft_searchandconcat(char **splited, char *cmd)
{
	int		i;
	char	*path;

	i = -1;
	while (splited[++i])
	{
		path = ft_match(splited[i], cmd);
		if (path)
			break;
	}
	return (path);
}