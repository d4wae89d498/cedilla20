re: clean all

headers=cedilla.h

all: core_syntax c99

compiler: çc.c 
	cc -g çc.c -o çc 

core_syntax: spec/core_syntax.ç $(headers) compiler
	./çc $< > objs/.tmp_$@.c
	cc -DIDE_COMPAT=0 -DTEST=1 -I. objs/.tmp_$@.c -o objs/$@

c99: spec/c99.ç $(headers) compiler
	./çc $< > objs/.tmp_$@.c
	cc -DIDE_COMPAT=0 -DTEST=1 -I. objs/.tmp_$@.c -o objs/$@  

test: all 
	./objs/core_syntax
	./objs/c99

re: fclean all

clean:
	rm -rf ./objs/* *.o *.so *.a *.out *.dSYM

fclean: clean
	rm -rf çc