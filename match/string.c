char    *str_add(char **s, char c)
{
    char    *n;

    asprintf(&n, "%s%c", *s, c);
    free(*s);
    return *s = n;
}