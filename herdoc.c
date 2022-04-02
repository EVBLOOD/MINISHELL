char *create_filename (int *nb)
{
    char *val;
    char *ret;

    val = ft_itoa(++(*nb));
    ret = ft_strjoin(".file", val);
    free(val);
    return (ret);
}

char    *ft_herdoc (char *limiter, int *nb)
{
    char *file;
    char *line;
    int fd;

    file = create_filename(nb);
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 00644);
    while (1)
    {
        line = readline ("herdoc> ");
        if (!ft_strncmp(line, limiter, ft_strlen(limiter)))
            break;
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
    }
    close(fd);
    return (file);
}
