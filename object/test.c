#include "object.h"
#include "object_list.h"
#include "stdio.h"
#include "assert.h"

int main()
{
    object_list     *ol = 0;

    olist_set(&ol, object_new("int", "i", 42));
    olist_set(&ol, dobject_new("str", "s", strdup("testheap"), free, 0));


    object *k = olist_get_object(ol, "i");

    assert(k->value == 42);  
    //printf("VALUE: %lli\n--\n", k->value);

    k = olist_get_object(ol, "s");
    assert(!strcmp((char*)k->value, "testheap"));

    //printf("VALUE: %s\n--\n", (char*)k->value);

    olist_free(ol);

    object_list *om = 0;

    olist_set(&om, object_new("int", "i", 42));
    olist_set(&om, dobject_new("char*", "s", strdup("testheap2"), free, strdup));

    olist_del(&om, "i");
    assert(!strcmp((char*)om->data->value, "testheap2"));
  //  printf("%s\n", (char*)om->data->value);
    


    object_list *tst = 0;
    olist_set(&tst, dobject_new("object_list", "testOBJ", olist_clone(om), (void(*)(void*))olist_free, olist_clone));

    printf("GETTIN VALUE:\n");
    printf("%s\n", (char*)(olist_get_object((void*)olist_get_object(tst, "testOBJ")->value, "s")->value));
    printf("GETTIN VALUE W/ get(...):\n");


    printf("'%s'\n", get(tst, testOBJ.s,char*));


   set(&tst, testOBJ, new(char*, s, "HIII"));

    printf("----'%s'\n", get(tst, testOBJ.s,char*));


    printf("GETTIN VALUE:\n");
    printf("%s\n", (char*)(olist_get_object((void*)olist_get_object(tst, "testOBJ")->value, "s")->value));
    printf("GETTIN VALUE W/ get(...):\n");


    printf("'%s'\n", get(tst, testOBJ.s,char*));


   // set(&tst, testOBJ, "v");
  //  dset(&tst, testOBJ, "v");


    olist_del(&om, "s");

    olist_free(tst);
   /* 
    object_list *new;
    new = olist_clone(tst);

    olist_del(&om, "s");

    olist_free(tst);*/

//printf("%lld\n", ((object_list*)olist_get_object(om, "s"))->data->value);
   // assert(!strcmp((char*)olist_get_object((object_list*)olist_get_object(new, "testOBJ"), "s")->value, "s"));

    printf("---------------\n");
    printf("LIBOBJECT.a   TESTS OK\n\n");
    printf("---------------\n");
}