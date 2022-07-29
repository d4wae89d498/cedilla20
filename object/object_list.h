#ifndef OBJECT_LIST_H
#define OBJECT_LIST_H
# include "list.h"
# include "object.h"
#define get(LIST, KEY, TYPE) ({                                         \
    object *obj;                                                        \
                                                                        \
    obj = object_get(LIST, STR(KEY));                                   \
    if (!obj)                                                           \
    {                                                                   \
        printf("ERROR: ACCESSING VALUE ON A NOT FOUND OBJECT\n");       \
        exit (0);                                                       \
    }                                                                   \
    if (strcmp(STR(TYPE), obj->type))                                   \
    {                                                                   \
        printf("ERROR: ACCESSING VALUE OF WRONG TYPE");                 \
        exit(0);                                                        \
    }                                                                   \
    (TYPE) obj->value;                                                  \
})
# define set(LIST, KEY, OBJ) object_set(LIST, STR(KEY), OBJ)

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
object_list *olist_clone(object_list *l);
void olist_free(object_list *l);


object      *object_get(object_list *l, char *key);

object_list *object_set(object_list **l, char *key, object *v);

#endif