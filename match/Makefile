CFLAGS 	= -Wall -Werror -Wextra -I../va_lisp -I../object -I../list -g
CLIBS  	= -L../va_lisp -lvalisp -L../object -lobject -L../list -llist
DEPS	= Makefile ../list/liblist.a ../va_lisp/libvalisp.a
NAME   	= libmatch.a


all: 	$(NAME)
re:		fclean all

primitives.o: $(DEPS) match.h primitives.c
	cc $(CFLAGS) -c primitives.c -o primitives.o

match.o: $(DEPS) match.h match.c
	cc $(CFLAGS) -c match.c -o match.o

$(NAME): $(DEPS) match.o primitives.o
	ar -rcs $(NAME) match.o primitives.o

test: $(DEPS) test.c $(NAME)
	cc $(CFLAGS) $(CLIBS) test.c $(NAME) -o test

run-test:  test
	./test

clean: 
	rm -rf match.o primitives.o ./test test.dSYM

fclean:	clean 
	rm -rf $(NAME)


