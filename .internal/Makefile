NAME=cedilla
SRCS=$(shell ls *.c)
OBJS=$(SRCS:.c=.o)

all:		$(NAME)
%.o:	%.c $(shell ls *.h) Makefile
	cc -g -Wall -Werror -Wextra -o $@ -c $<
$(NAME):	$(OBJS) 
	cc -g -Wall -Werror -Wextra -o $(NAME) $(OBJS)
clean:
	rm -rf $(OBJS)
fclean:		clean
	rm -rf $(NAME)
re:			fclean all