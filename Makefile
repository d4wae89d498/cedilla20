DEPS 	=	Makefile list/liblist.a object/libobject.a

all: $(DEPS)
	make -C list $@
	make -C object $@

re: fclean all

clean: $(DEPS) 
	make -C list $@ 
	make -C object $@

flcean: $(DEPS) clean 
	make -C list $@ 
	make -C object $@

test: $(DEPS) 
	make -C list $@ 
	make -C object $@

run-test: $(DEPS) test
	make -C list $@ 
	make -C object $@