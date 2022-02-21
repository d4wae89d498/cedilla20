all:
	cc -I. compiler.c -o çc
	./çc spec.ç spec_compiler.c
	cc -I. spec_compiler.c -o spec_compiler
	./spec_compiler spec.ç spec.c
	cc -I. spec.c && ./a.out
nocedille:
	cp spec.ç spec.c && cc -I. spec.c && ./a.out
diff:
	make > a.txt
	make nocedille > b.txt
	diff a.txt b.txt
clean:
	rm -rf spec_compiler
	rm -rf a.txt
	rm -rf b.txt
	rm -rf spec.c
	rm -rf spec_compiler.c
	rm -rf a.out
fclean:	clean
	rm -rf çc
