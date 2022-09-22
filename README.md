- [x] *list*        is a linked list
- [x] *object*      is a struct that associate a name, along with a type and a value, a destructor and a cloner
- [x] *object_list* is a linked *list of object*, it aims to be used within the çc 'ctx' struct for easier parsing state management
- [x] *çc*          is a program that *takes (almost) same arguments as gcc*. Only arguments order may differ to respect
                    current limitation of : $ çc [args] [file.c]. It provides a dynamic macro and syntax system.
- [x] *match*       is a macro built on top of çc for easier source file parsing
- [ ] *ç*           is a standard library built with the çc command, providing c-pre-processor implementations, along with a series of
                    features desgined as *a C super-set*. 


Academic Resources : 

- [The Nemerle programming language designed, Jetbrains, 2003](https://github.com/rsdn/nemerle/wiki/Syntax-extensions)
- [The Katahdin programming languages designed by Chris Seaton, 2007](https://github.com/chrisseaton/katahdin/blob/master/demos/factorial.kat)
- [Modern Extensible Languages, Daniel Zingaro, 2007](http://www.cas.mcmaster.ca/sqrl/papers/SQRLreport47.pdf) 
- [Extending Syntax from Within a Language, Bob Nystrom, 2011](http://journal.stuffwithstuff.com/2011/02/13/extending-syntax-from-within-a-language/)
- [The Anvil programming language, Leslie Schultz, Rich Arriaga, Todd L. Smith, Mark van Gulik, 2012](https://www.availlang.org/about-avail/introduction/index.html)
- [Honu: Syntactic Extension for Algebraic Notation through Enforestation, Jon Rafkind, 2012](https://www.cs.utah.edu/plt/publications/gpce12-rf.pdf)
