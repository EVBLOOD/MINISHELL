
int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

void getvar(int her, int fd, char **env, char *c)
{
    int i;
    char *value;
    char str[1000000];
    i = 0;
    read(fd, c, 1);
    if (ft_isalnum(*c) || *c == '$')
    {
        while (ft_isalnum(*c))
        {
            str[i++] = *c;
            read(fd, c, 1);
        }
        str[i] = '\0';
        i = -1;
        while (env[++i])
        {
            if (!strncmp(env[i], str, strlen(str)) && env[i][strlen(str)] == '=')
            {
                value = strdup(&env[i][strlen(str) + 1]);
                write (her, value, strlen(value));
                free (value);
            }
        }
    }
    else
        write(her, "$", 1);
}



int herdoc(char *file, char **env)
{
    int fd;
    int her;
    int ret;
    char c;
    
    (void)env;
    fd = open(file, O_RDONLY);
     if (fd < 0)
        perror("minishell");
    her = open(".herdoc", O_CREAT | O_WRONLY | O_TRUNC, 00644);
    if (her < 0)
        perror("");
    ret = read(fd, &c, 1);
    while (ret > 0)
    {
        if (c == '$')
            getvar(her, fd, env, &c);
        write (her, &c, 1);
        ret = read(fd, &c, 1);
    }
    unlink(file);
    return (her);
}