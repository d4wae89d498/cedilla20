re: clean all
all:
	cc -g compiler.c -o compiler 
	./compiler spec/core_syntax.ç > objs/.tmp_core_syntax.c
	cc -I. objs/.tmp_core_syntax.c -o core_syntax 
clean:
	rm -rf ./objs/.tmp* *.o *.so *.a *.out *.dSYM