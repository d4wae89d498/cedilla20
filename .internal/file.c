#include "./file.h"
#include "./cedilla.h"

char *read_file(const char *path)
{
    int         fd;
    char        *out;
    struct stat buf;

    fd = open(path, O_RDONLY);
    if (fd < 0)
        return _ !printf("Error: unable to open '%s'\n", path);
    fstat(fd, &buf);
    out = malloc(buf.st_size + 1);
    if (!out)
    {
        close (fd);
        return _ !printf("Error: unable to allocate %lld for reading '%s'\n", buf.st_size, path);
    }
    if (read(fd, out, buf.st_size) < 0)
    {
        close (fd);
        return _ !printf("Error: unable to read '%s'\n", path);
    }
    out[buf.st_size] = 0;
    close (fd);
    return (out);
}

char *read_fd(int fd)
{
    char *out;
    struct stat buf;

    fstat(fd, &buf);
    out = malloc(buf.st_size);
    read(fd, out, buf.st_size);
    return (out);
}

void mkpath(const char *dir)
{
    char *tmp;
    char *p;
    size_t len;

    p = 0;
    asprintf(&tmp, "%s", dir);
    len = strlen(tmp);
    if (tmp[len - 1] == '/')
        tmp[len - 1] = 0;
    p = tmp + 1;
    while (*p)
    {
        if (*p == '/')
        {
            *p = 0;
            mkdir(tmp, S_IRWXU);
            *p = '/';
        }
        p += 1;
    }
    return ;
}
