#ifndef OBJECT_LIST_H
#define OBJECT_LIST_H
# include "list.h"
# include "object.h"

typedef struct s_object_list
{
    object *data;
    struct s_object_list
        *next;
} object_list;
object_list *olist_last(object_list *l);
object_list *olist_new(object *data);
object_list *olist_get(object_list *, char *key);
object *olist_get_object(object_list *l, char *key);
object_list *olist_set(object_list **l, object *data);
void olist_del(object_list **l, char *key);
void olist_free(object_list **l);
#endif