#ifndef CEDILLA_OBJECT_H
# define CEDILLA_OBJECT_H
# include <libc.h>
# include <stdlib.h>
typedef enum 
{
    LIST,
    STR,
    INT   	
}   object_type;
typedef struct s_object 
{
    object_type       	type;   
	char				*name;
    void                *data; 
    struct s_object    
						*next;
}   object;
long long				*new_int(long long);
char					*new_str(char *);
object                  *object_new(object_type, char*, void *, void(*)());
object	                *object_push(object **,object *);
void 	                object_delone(object **, object *, void(*)(void*));
object 	                *object_find(object *, char *);
void	                object_free(object **, void(*)(void*));
void	                object_dump_level(object *, int);
void	                object_dump(object *);
#endif
