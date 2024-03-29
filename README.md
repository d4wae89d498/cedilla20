*Le C-Cédille* est un *langage de programmation extensible*, visant le C pour la génération des sources des compilateurs intermédiaires ainsi que pour la génération des sources du programme.

Partant du constat que les systèmes de macro du C et du Rust ne permettent pas d'avoir des variables pendant la phase de compilation, ils ne permettent donc pas de donner aux développeurs les outils nécessaires pour la meta-programmation et donc pour la programmation extensible. D'autres préprocesseurs plus puissants tels que le M4 ou le PHP pourraient alors remplacer le préprocesseur du C ou du Rust, mais cela reviendrait donc à utiliser un autre language qui serait donc incompatible avec les macros implémentées et cela ne comblerait pas les besoins d'extensibilité.

*Démo :*

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

*Ordre des dépendances (une dépendance peut exclusivement s'appuyer sur celles du dessus) :*

- [x] list 
- [x] object    
- [x] object_list 
- [x] çc       
- [x] match 
- [ ] include_primitive
- [ ] language_primitive
- [ ] c99
- [ ] cpp
- [ ] ç 
    - [ ] compile_time 
    - [ ] module
    - [ ] lambda
    - [ ] defer
    - [ ] async
    - [ ] meta
    - [ ] safety / iterators
    - [ ] classes / interfaces
    - [ ] sql
    - [ ] hardware


*Ressources sur le même sujet :*

- [Coq syntax extensions and notation scopes, INRIA, 1984](https://coq.inria.fr/refman/user-extensions/syntax-extensions.html)
- [Camlp4 - Tutorial, Chapter 7: Extending the syntax of OCaml, Daniel de Rauglaudre, INRIA, 2003](https://caml.inria.fr/pub/docs/tutorial-camlp4/tutorial007.html)
- [The Nemerle programming language, Jetbrains, 2003](https://github.com/rsdn/nemerle/wiki/Syntax-extensions)
- [The Katahdin programming language, Chris Seaton, 2007](https://github.com/chrisseaton/katahdin/blob/master/demos/factorial.kat)
- [Modern Extensible Languages, Daniel Zingaro, 2007](http://www.cas.mcmaster.ca/sqrl/papers/SQRLreport47.pdf) 
- [Extending Syntax from Within a Language, Bob Nystrom, 2011](http://journal.stuffwithstuff.com/2011/02/13/extending-syntax-from-within-a-language/)
- [The Anvil programming language, Leslie Schultz, Rich Arriaga, Todd L. Smith, Mark van Gulik, 2012](https://www.availlang.org/about-avail/introduction/index.html)
- [Honu: Syntactic Extension for Algebraic Notation through Enforestation, Jon Rafkind, 2012](https://www.cs.utah.edu/plt/publications/gpce12-rf.pdf)
