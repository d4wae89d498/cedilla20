*Le C-Cédille* est un langage de programmation extensible, visant le C pour la génération des compilateurs intermédiaire ainsi que pour la génération du code source du programme.

Partant du constat que les systèmes de macro du C et du Rust ne permettent pas d'avoir des variables pendant la phase de compilation, ils ne permettent donc pas de donner aux développeurs les outils nécessaires pour la meta-programmation et donc pour la programmation extensible. D'autres préprocesseurs plus puissants tels que le M4 ou le PHP pourraient alors remplacer le préprocesseur du C ou du Rust, mais cela reviendrait donc à utiliser un autre language qui serait donc incompatible avec les macros implémentées et cela ne comblerait pas les besoins d'extensibilité.

Démo:

```C
macro
{
    if (!strncmp(*src, "__G1__", 6) && !ctx->is.str)
    {
        *src += 6;
        return "41";     
    }
    return 0;
}

macro
{
    if (!strncmp(*src, "__G2__", 6) && !ctx->is.str)
    {
        *src += 6;
        return strdup((char[7]) {'_', '_', 'G', '1', '_', '_', 0});     
    }
    return 0;
}

int main()
{
    assert(__G2__ == 41);
}
````

Objectifs:

- [x] *list*        is a linked list
- [x] *object*      is a struct that associate a name, along with a type and a value, a destructor and a cloner
- [x] *object_list* is a linked *list of object*, it aims to be used within the çc 'ctx' struct for easier parsing state management
- [x] *çc*          is a program that *takes (almost) same arguments as gcc*. Only arguments order may differ to respect
                    current limitation of : $ çc [args] [file.c]. It provides a dynamic macro and syntax system.
- [x] *match*       is a macro built on top of çc for easier source file parsing
- [ ] *ç*           is a standard library built with the çc command, providing c-pre-processor implementations, along with a series of
                    features desgined as *a C super-set*. 


Ressources académiques: 

- [Coq, INRIA, 1984](https://coq.inria.fr/refman/user-extensions/syntax-extensions.html)
- [OCaml, INRIA, 1996](https://caml.inria.fr/pub/docs/tutorial-camlp4/tutorial007.html)
- [The Nemerle programming language, Jetbrains, 2003](https://github.com/rsdn/nemerle/wiki/Syntax-extensions)
- [The Katahdin programming language, Chris Seaton, 2007](https://github.com/chrisseaton/katahdin/blob/master/demos/factorial.kat)
- [Modern Extensible Languages, Daniel Zingaro, 2007](http://www.cas.mcmaster.ca/sqrl/papers/SQRLreport47.pdf) 
- [Extending Syntax from Within a Language, Bob Nystrom, 2011](http://journal.stuffwithstuff.com/2011/02/13/extending-syntax-from-within-a-language/)
- [The Anvil programming language, Leslie Schultz, Rich Arriaga, Todd L. Smith, Mark van Gulik, 2012](https://www.availlang.org/about-avail/introduction/index.html)
- [Honu: Syntactic Extension for Algebraic Notation through Enforestation, Jon Rafkind, 2012](https://www.cs.utah.edu/plt/publications/gpce12-rf.pdf)



