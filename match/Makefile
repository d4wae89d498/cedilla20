CFLAGS 	= -Wall -Werror -Wextra -I../va_lisp -I../object -I../list -g
CLIBS  	= -L../va_lisp -lvalisp -L../object -lobject -L../list -llist
DEPS	= Makefile ../list/liblist.a
NAME   	= libmatch.a


all: 	$(NAME)
re:		fclean all

match.o: $(DEPS) match.h match.c
	cc $(CFLAGS) -c match.c -o match.o

$(NAME): $(DEPS) match.o
	ar -rcs $(NAME) match.o

test: $(DEPS) test.c $(NAME)
	cc $(CFLAGS) $(CLIBS) test.c $(NAME) -o test

run-test:  test
	./test

clean: $(DEPS)
	rm -rf ./test test.dSYM

fclean:	$(DEPS) clean 
	rm -rf object.o


