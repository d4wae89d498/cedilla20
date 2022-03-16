Cédille is a preprocessor, that use C as a preprocessing language. 
This preprocessor can detect and apply any pattern replacement.
Any existing programming language can be implemented using Cédille.



## Demo

[https://github.com/MarcFaussurier/ft_cedillev2/blob/master/spec.%C3%A7](spec.ç)

[https://github.com/MarcFaussurier/ft_cedillev2/blob/master/result_a.txt](outputs with cédille)

[https://github.com/MarcFaussurier/ft_cedillev2/blob/master/result_b.txt](outputs without cédille)


Compile & run the spec file by ignoring macro
```
make nocedille
```

Compile & run the spec file with macro
```
make
```

## Macro engine steps 

```
[x]	1 - The file is read character by character to find out macros
[x]	2 - The file is read character by character to replace out macro by their match (using 1. declarative order)	
[x]	3 - Repeat 1, 2 and stop if nothing change
[ ]	4 - Macro are deleted from the generated result
```

## Todos

```
[ ] - detect brace level for macro rule parsing 
[ ] - force 'macro rule' without keywords betweem 'macro' and 'rule'
[ ] - implement a basic C parser in ç
[ ] - use macros within macro
[ ] - dep tree / or loop until macro stays the same, but what if applied macro was not ready yet?)
```


# Exo-programming language

*Définition*
```
An exo-programming language is a preprocessor, that use destination language as 
preprocessing language. 
```

*Propiété*
```
By assuming that the destination-language is turing-complete, the preprocessor
can detect and apply any pattern replacement.
```

*Conséquence*
```
Any existing programming language can now be implemented using the destination 
language and the exo programming language.
```
