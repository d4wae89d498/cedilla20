- [x] *list*        is a linked list
- [x] *object*      is a struct that associate a name, along with a type and a value, a destructor and a cloner
- [x] *object_list* is a linked *list of object*
- [x] *va_function* is a function such as : *long long(list of va_functions, void *data, va_list)* 
- [x] *va_lisp*     is a function that read a va_list of string using a *list of va_functions*. 
                It may be used to quickly create DSL languages.
- [ ] *match*       is a function that *use va_lisp with an object_list in the functions' void ptr* parameter,
                this object list is parsing context. match provides primitives that allow easier 
                parsing of string; think aobut it as a readable, extensible, state-oriented, regex replacement.
- [ ] *çc*          is a program that *takes (almost) same arguments as gcc*. Only arguments order may differ to respect
                current limitation of : $ çc [args] [file.c]. It provides a dynamic macro and token system.
                You may use it with libmatch, or you may implement an other string parser.
- [ ] *ç*           is the standard library for the çc command, providing c-pre-processor implementations, along with a series of
                features desgined as *a C super-set*. 
