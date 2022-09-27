CFLAGS 	= -Wall -Werror -Wextra -I../list -I../object -g
CLIBS  	= -L../list -llist -L../object -lobject
DEPS	= Makefile ../list/liblist.a ../object/libobject.a compiler.h
NAME   	= çc

.SUFFIXES:

all: $(NAME)

$(NAME): çc.c $(DEPS) compiler.o
	cc $(CFLAGS) $(CLIBS) -g çc.c -o $@ compiler.o

%.o: %.c 
	cc $(CFLAGS) -c $< -o $@

re: fclean all

clean:
	rm -rf compiler.o çc.dSYM

fclean: clean
	rm -rf $(NAME) 
