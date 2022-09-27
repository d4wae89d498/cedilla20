re: clean all

headers=compiler.h

all: compiler test

compiler: çc.c 
	cc -g çc.c -o çc 

test: core_syntax

core_syntax: spec/core_syntax.ç $(headers) compiler
	./çc $< > objs/.tmp_$@.c
	cc -DIDE_COMPAT=0 -DTEST=1 -I. objs/.tmp_$@.c -o objs/$@

c99: spec/c99.ç $(headers) compiler
	./çc $< > objs/.tmp_$@.c
	cc -DIDE_COMPAT=0 -DTEST=1 -I. objs/.tmp_$@.c -o objs/$@ 

compile_time: spec/compile_time.ç $(headers) compiler
	./çc $< > objs/.tmp_$@.c
	cc -DIDE_COMPAT=0 -DTEST=1 -I. objs/.tmp_$@.c -o objs/$@   

match: spec/match.ç $(headers) compiler
	./çc $< > objs/.tmp_$@.c
	cc -DIDE_COMPAT=0 -DTEST=1 -I. objs/.tmp_$@.c -o objs/$@   

run-test: test 
	./objs/core_syntax

re: fclean all

clean:
	rm -rf ./objs/* *.o *.so *.a *.out *.dSYM

fclean: clean
	rm -rf çc
