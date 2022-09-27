DEPS 	=	Makefile 

all: $(DEPS)
	make -C list $@
	make -C object $@
	make -C çc $@
re: fclean all
clean: 
	make -C list $@ 
	make -C object $@
	make -C çc $@
fclean:  clean 
	make -C list $@ 
	make -C object $@
	make -C çc $@
test: $(DEPS) 
	make -C list $@ 
	make -C object $@
	make -C çc $@
run-test: $(DEPS) test
	make -C list $@ 
	make -C object $@
	make -C çc $@
