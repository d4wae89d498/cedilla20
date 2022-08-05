CFLAGS 	= -Wall -Werror -Wextra -I../list  -g
CLIBS  	= -L../list -llist
DEPS	= Makefile ../list/liblist.a
NAME   	= libvalisp.a


all: 	$(NAME)
re:		fclean all

va_lisp.o: $(DEPS) va_lisp.h va_lisp.c
	cc $(CFLAGS) -c va_lisp.c -o va_lisp.o

$(NAME): $(DEPS) va_lisp.o
	ar -rcs $(NAME) va_lisp.o

test: $(DEPS) test.c $(NAME)
	cc $(CFLAGS) $(CLIBS) test.c $(NAME) -o test

run-test:  test
	valgrind ./test

clean: 
	rm -rf ./test test.dSYM

fclean:	clean 
	rm -rf object.o


