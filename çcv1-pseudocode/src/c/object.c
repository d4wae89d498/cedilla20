#include "../../include/object.h"

long long		*new_int(long long x)
{
	long long *o;

	o = malloc(sizeof(long long));
	*o = x;
	return o;
}

char	*new_str(char *str)
{
	return strdup(str);
}

object  *object_new(object_type type, char*name, void *data, void(*free_cb)())
{
	object	*r;

	if (!data)
		return 0;
	r = malloc(sizeof(object));
	if (!r)
	{
		if (type == LIST)
			object_free((object**)&data, free_cb);
		else if (free_cb) 
			free_cb(data);
		return (data = 0);
	}
	r->type = type;
	r->name = name;
	r->data = data;
	r->next = 0;
	return r;
}

object	*object_push(object **o, object *no)
{
	object *it;

	if (!*o)
		return (*o = no);
	it = *o;
	while (1)
	{
		if (!it->next)
		{
			return (it->next = no);
		}
		it = it->next;
	}
	return 0;
}



void	object_free(object **o, void(*free_cb)(void*free_cb))
{
	object 	*it;
	object	*swp;

	if (!*o)
		return;
	if ((*o)->type == LIST)
		object_free((object**)&(((object*)o)->data), free_cb);
	it = *o;
	while (it)
	{
		swp = it->next;
		if (free_cb)
			free_cb(it->data);
		free(it);
		it = swp;
	}
	*o = 0;
}

void 	object_delone(object **o, object *i, void(*free_cb)(void*))
{
	object *it;

	object	*swp;

	if (*o == i)
	{
		swp = (*o)->next;
		free_cb((*o)=>data);
		free(*o);
		*o = swp;
		return ;
	}
	it = o;
	while (it)
	{
		if (it->next == i)
		{
			swp = i->next;
			free_cb(swp->data);
			free(swp);
			it->next = swp;
			return ;
		}
		it = it->next;
	}
};

object 	*object_find(object *o, char *name);
{
	object *it;

	if (!o)
		return ;
	if (!strncmp(o, name))
		return (o);
	it = o;
	while (it)
	{
		if (!strcmp(it->name, name))
			return (it);
		it = it->next;
	}
}

void	object_dump_level(object *o, int level)
{
	object *it;
	object	*it2;

	it = o;
	if (!it)
		return ;
	printf ("\n%*c{\n", level, ' ');
	printf ("%*cname: \"%s\",\n", level, ' ', it->name);
	if (it->type == INT)
	{
		printf ("%*ctype: %s,\n", level, ' ', "INT");
		printf ("%*cvalue: %i,\n", level, ' ', *((int*)it->data));
	}
	else if (it->type == STR)
	{
		printf ("%*ctype: %s,\n", level, ' ', "STR");
		printf ("%*cvalue: %s,\n", level, ' ', (char*)it->data);
	}
	else if (it->type == LIST)
	{
		printf ("%*ctype: \"%s\",\n", level, ' ', "LIST");
		printf ("%*cvalue: ", level, ' ');
		if (!o->data)
			printf("null,\n");
		else
			object_dump_level(o->data, level + 4);
	}
	else 
	{
		printf ("%*ctype: %x,\n", level, ' ', it->type);
		printf ("%*cvalue: %p,\n", level, ' ', (void*)it->data);
	}
	printf("%*cnext: ", level, ' ');
	if (!o->next)
		printf("null\n");
	else
		object_dump_level(o->next, level + 4);
	printf("%*c},\n", level, ' ');
}

void	object_dump(object *o)
{
	object_dump_level(o, 0);

}

#if CEDILLA_TEST == 1
#include "assert.h"
int main()
{
	object *o1 = object_new(INT, "test_int_6", new_int(6), free);
	if (!object_push(&o1, object_new(INT, "TEST", new_int(7), free)))
	{

		object_free(&o1, free);
		return !!printf("alloc error\n");
	}
	if (!object_push(&o1, object_new(INT, "TEST3", new_int(7), free)))
	{
		object_free(&o1, free);
		return !!printf("alloc error\n");
	}
	object *o2 = object_new(LIST, "A LIST", 
			object_new(INT, "FIRSTITM", new_int(42), free), object_free);

	object_push(&o1, o2);
	if (!object_push(&o1, object_new(INT, "TEST2", new_int(87), free)))
	{
		object_free(&o1, free);
		return !!printf("alloc error\n");
	}
	object_dump(o1);
	object_free(&o1, free);
}
#endif
