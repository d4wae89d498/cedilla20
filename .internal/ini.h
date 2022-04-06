#ifndef CEDILLA_INI_H
# define CEDILLA_INI_H
# include "list.h"

typedef struct 
{
    char        *name;
    char        *data;
}   item;

typedef struct
{
    char        *name;
    list        *variables;
}   section;

typedef list    *ini; // list of section

ini             ini_new(const char *);  
item            *ini_add(ini *ini, const char *, const char *, const char*);
const char      *ini_get(ini, const char *, const char *);
void            ini_dump(ini k);
void            ini_delete(ini *k);

#endif