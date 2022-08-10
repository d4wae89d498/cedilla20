- [x] *list*        is a linked list
- [x] *object*      is a struct that associate a name, along with a type and a value, a destructor and a cloner
- [x] *object_list* is a linked *list of object*
- [x] *va_function* is a function such as : *int(list of va_functions, void *data, va_list)* returns non-0 on success
- [x] *va_lisp*     is a function that read a va_list of va_functions. 
                    It may be used to quickly create domain-specific languages (DSL).
- [x] *match*       is a function that *use va_lisp with an object_list in the functions' void ptr* parameter,
                    this object list is parsing context. match provides primitives that allow easier 
                    parsing of string. Think aobut it as a readable, extensible, state-oriented, regex replacement. 
- [ ] *çc*          is a program that *takes (almost) same arguments as gcc*. Only arguments order may differ to respect
                    current limitation of : $ çc [args] [file.c]. It provides a dynamic macro and token system that use *libmatch* as a string pattern/state DSL to create GPL.
- [ ] *ç*           is a standard library built with the çc command, providing c-pre-processor implementations, along with a series of
                    features desgined as *a C super-set*. 


Academic resources : 

- Daniel Zingaro, 2007 - http://www.cas.mcmaster.ca/sqrl/papers/SQRLreport47.pdf 
