#include "object.h"
#include "object_list.h"
#include "stdio.h"
#include "assert.h"

int main()
{
    object_list     *ol = 0;

    olist_set(&ol, object_new("int", "i", 42));
    olist_set(&ol, dobject_new("str", "s", strdup("testheap"), free));


    object *k = olist_get_object(ol, "i");

    assert(k->value == 42);  
    //printf("VALUE: %lli\n--\n", k->value);

    k = olist_get_object(ol, "s");
    assert(!strcmp((char*)k->value, "testheap"));

    //printf("VALUE: %s\n--\n", (char*)k->value);

    olist_free(&ol);


    object_list *om = 0;

    olist_set(&om, object_new("int", "i", 42));
    olist_set(&om, dobject_new("str", "s", strdup("testheap2"), free));

    olist_del(&om, "i");
    assert(!strcmp((char*)om->data->value, "testheap2"));
  //  printf("%s\n", (char*)om->data->value);
    olist_del(&om, "s");


    printf("---------------\n");
    printf("LIBOBJECT.a   TESTS OK\n\n");
    printf("---------------\n");
}