#include "./ini.h"
#include "./file.h"
#include "./cedilla.h"
#include "./string.h"
#include "./list.h"

#include <ctype.h>

ini ini_new(const char *path)
{
    char *src;
    int i;
    char *section;
    char *key;
    char *val;
    ini o;

    o = 0;
    section = 0;
    key = 0;
    val = 0;
    src = read_file(path);
    if (!src)
        return (0);
    i = 0;
    while (1)
    {
        while (isspace(src[i]))
            i += 1;
        if (src[i] == ';')
            while (src[i] && src[i] != '\n')
                i += 1;
        else if (src[i] == '[')
        {
            free(section);
            section = 0;
            i += 1;
            while (src[i] && src[i] != ']')
                str_append(&section, src[i++]);
        }
        else
        {
            while (src[i] && src[i] != '=')
                str_append(&key, src[i++]);
            if (src[i] == '=')
                i += 1;
            while (src[i] && src[i] != '\n' && src[i] != ';')
                str_append(&val, src[i++]);
            if (src[i] == ';')
                i -= 1;
            ini_add(&o, section, key, val);
            key = 0;
            val = 0;
        }
        if (!src[i])
            break;
        i += 1;
    }
    free(src);
    return (o);
}

void *is_name(const section *s, const char *str)
{
    if (!strcmp(s->name, str))
    {
        return ((void *)s);
    }
    return (0);
}

item *ini_add(ini *f, const char *n, const char *k, const char *v)
{
    section *s;
    item    *i;

    if (!(i = malloc(1 * sizeof(item))))
        return (0);
    i->name = strdup(k);
    i->data = strdup(v);
    if ((!i->name) || (!i->data))
    {
        free(i->name);
        free(i->data);
        free(i);
        return (0);
    }
    else if (!(s = list_find(*f, (void *)is_name, (void *)n)))
    {
        if (!(s = malloc(1 * sizeof(section))))
        {
            free(i);
            return (0);
        }
        else if (!(s->name = strdup(n)))
        {
            free(i);
            free(s);
            return (0);
        }
        else 
        {
            s->variables = 0;
            if (!list_add_data(f, s) || !list_add_data(&(s->variables), i))
            {
                free(i);
                if (s)
                    free(s->name);
                free(s);
                return (0);
            }
        }
    }
    else if (!list_add_data(&(s->variables), i))
    {
        free(i);
        return (0);
    }
    return (i);
}

void *is_key(const item *i, const char *str)
{
    if (!strcmp(i->name, str))
    {
        return ((void *)i);
    }
    return (0);
}

const char *ini_get(ini i, const char *s, const char *k)
{
    section *section;
    item *item;

    if ((section = list_find(i, (void *)is_name, (void *)s)))
    {
        item = list_find(section->variables, (void *)is_key, (void *)k);
        if (item)
            return (item->data);
    }
    return (0);
}

void ini_delete(ini *k)
{
    list *i;
    list *y;
    section *section;
    item *item;

    i = *k;
    while (i)
    {
        section = i->data;
        y = section->variables;
        while (y)
        {
            y = y->next;
        }
        i = i->next;
    }
    (void)item;
    *k = 0;
}

void ini_dump(ini k)
{
    list *i;
    list *y;

    section *s;
    item *it;

    i = k;
    while (i)
    {
        s = i->data;
        printf("section -- %s\n", s->name);
        y = s->variables;
        while (y)
        {
            it = y->data;
            printf("var -- %s = %s\n", it->name, it->data);
            y = y->next;
        }
        i = i->next;
    }
}