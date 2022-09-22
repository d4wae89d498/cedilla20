DEPS 	=	Makefile 

all: $(DEPS)
	make -C list $@
	make -C object $@
	make -C çcv2 $@
re: fclean all
clean: 
	make -C list $@ 
	make -C object $@
	make -C çcv2 $@
fclean:  clean 
	make -C list $@ 
	make -C object $@
	make -C çcv2 $@
test: $(DEPS) 
	make -C list $@ 
	make -C object $@
	make -C çcv2 $@
run-test: $(DEPS) test
	make -C list $@ 
	make -C object $@
	make -C çcv2 $@
