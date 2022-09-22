- [x] *list*        is a linked list
- [x] *object*      is a struct that associate a name, along with a type and a value, a destructor and a cloner
- [x] *object_list* is a linked *list of object*, it aims to be used within the çc 'ctx' struct for easier parsing state management
- [x] *çc*          is a program that *takes (almost) same arguments as gcc*. Only arguments order may differ to respect
                    current limitation of : $ çc [args] [file.c]. It provides a dynamic macro and syntax system.
- [x] *match*       is a macro built on top of çc for easier source file parsing
- [ ] *ç*           is a standard library built with the çc command, providing c-pre-processor implementations, along with a series of
                    features desgined as *a C super-set*. 


Academic resources : 

- Daniel Zingaro, 2007 - http://www.cas.mcmaster.ca/sqrl/papers/SQRLreport47.pdf 
