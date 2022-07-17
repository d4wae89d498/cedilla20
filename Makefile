all: 		templates

templates/ç_macro_cleaner.h: 		templates/ç_macro_cleaner.php
	php templates/ç_macro_cleaner.php > templates/ç_macro_cleaner.h 
templates/cpp_foreach_helper.h: 	templates/cpp_foreach_helper.php 
	php templates/cpp_foreach_helper.php > templates/cpp_foreach_helper.h

tamplates:	templates/cpp_foreach_helper.h  templates/ç_macro_cleaner.h


