

## ç 

The ç is a cpp (aka C-PRE-PROCESSOR) superpset.
So the `çc` command is superset of the `gcc` command.
Also,  `çc -E file` will have the same effect as `gcc -E file`, generating the final pure C file used before compilation.
`çc [...args] file` will preprocess and then compile the file, using the `$CC` env var.

## project map (project run-time)

`çc [-d=args -E] [-anyotherflags]  file` 
    The following arguments are given by default: -dide_compat=0 -dcedilla_test=0
    The compiler will read *file.c* line by line, will detect; eval or save the cpp instructions.
    If *-dCOMPILER=1* is given, main is replaced by a new main that generate code using given macros, source is printed to terminal, exit.
    These instructions will be compiled using `$çc -o file_compier -dCOMPILER=1 file_compiler.c match.o`
    Then  `file_compiler [-d=args -E] file` occurs, generating *file.expanded.c*
        If *-E* was given,  *file.expanded.c* is printed to terminal, exit.
    Then `$CC [-anyotherflags] file.expand.c` is occurs, generating the final binary.
`çc_tester` will test the default cpp features *src/cpp*, the macro language *src/macro.ç src/match.c* and the standard language *src/ç*
    The following arguments are given to çc: -dide_compat=0 -dtest=1

## About -dide-compat

By default, the `ç.h` header will set the -dide_compat=1 flag to ensure IDE retrocompatibility, along with -dtest=1.
The -ide_compat=1 flag will break the generated binary run-time. So it should only be used for ide retrocompatibility. 

## About maro engine 

A ç_ctx struct is shared among macros, the struct is eather alterd by a macro that succeed, or it get reseted on macro failure.
Macros may define new variables for that structure.

## current limitations: 
- multiple C files are not supported, and gcc flags must be written before the <file> argument, file beeing the last argument. (because it looks like impossible to handle all comiler specific arguments syntaxes, but may be usefull to fix for at least gcc and clang).

## çc
- [ ] src/çc/match.c impl/test
- [ ] src/çc/macro.ç tests 

## cpp
- [ ] src/cpp/*.c tests 

## src/ç standard library langugage

v1
- [ ] async / await keywords
- [ ] lambda
- [ ] lambda captures
v2 
- [ ] interface
- [ ] class
- [ ] parameters to array / struct (and inverse)
- [ ] try / catch / finally
- [ ] compile-time var to type (and c words other datas ???)
safety features:
- [ ] iterating w/out iterators, array bound checks 
- [ ] null ptr -> compile time warning
- [ ] async functions / threads / childs process should not get a reference to a scope variable, only copy or borrow/move, defers will follow the borrow 
- [ ] async functions / threads that access to a global variable without mutex 
- [ ] process that modifies a non-shared memory 
- [ ] alloc without defer free  
- [ ] open without defer close  
- [ ] va open without defer va close 
- [ ] use after borrow/move  
- [ ] cast to ptr 
- [ ] cast to lower type 
