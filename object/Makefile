CFLAGS 	= -Wall -Werror -Wextra -I../list  -g
CLIBS  	= -L../list -llist -g
DEPS	= Makefile ../list/liblist.a
NAME   	= libobject.a


all: 	$(NAME)
re:		fclean all

object.o: $(DEPS) object.h object.c
	cc $(CFLAGS) -c object.c -o object.o

object_list.o: $(DEPS) Makefile object.o object_list.h object_list.c
	cc $(CFLAGS) -c object_list.c -o object_list.o

$(NAME): $(DEPS) object.o object_list.o
	ar -rcs $(NAME) object.o object_list.o

test: $(DEPS) test.c $(NAME)
	cc $(CFLAGS) $(CLIBS) test.c $(NAME) -o test

run-test:  test
	valgrind ./test

clean: 
	rm -rf ./test test.dSYM

fclean:	clean 
	rm -rf object.o


