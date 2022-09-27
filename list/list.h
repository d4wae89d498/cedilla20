#ifndef LIST_H
# define LIST_H
# include <stdlib.h>
typedef struct s_list
{
    void            *data;
    struct s_list   *next; 
}   list;
list                *list_last(list *l);
list                *list_new(void *data);
list                *list_add(list **l, void *data);
void                list_del(list **l, list *k, void(*value_destructor)(void*));
void                list_free(list *l, void(*value_destructor)(void*));
#endif