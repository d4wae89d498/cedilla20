## Macro engine steps 

```
	1 - The file is read character by character to find out macros
	2 - The file is read character by character to replace out macro by their match (using 1. declarative order)	
	3 - Repeat 1, 2 and stop if nothing change
	4 - Macro are deleted from the generated result
```
