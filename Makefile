DEPS 	=	Makefile 

all: $(DEPS)
	make -C list $@
	make -C object $@
	make -C va_lisp $@
	make -C match $@
re: fclean all
clean: 
	make -C list $@ 
	make -C object $@
	make -C va_lisp $@
	make -C match $@
fclean:  clean 
	make -C list $@ 
	make -C object $@
	make -C va_lisp $@
	make -C match $@
test: $(DEPS) 
	make -C list $@ 
	make -C object $@
	make -C va_lisp $@
	make -C match $@
run-test: $(DEPS) test
	make -C list $@ 
	make -C object $@
	make -C va_lisp $@
	make -C match $@