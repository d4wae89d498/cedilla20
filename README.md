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
