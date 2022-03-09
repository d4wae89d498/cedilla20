#!/bin/bash

function compile
{
	src=$1
	out=$2
	flags=$3
	echo "./çc ${src} tmp_compiler.c"
	./çc "${src}" "tmp_compiler.c"
	echo "cc $flags tmp_compiler.c -o tmp_compiler"
	cc "$flags" "tmp_compiler.c" "-o" "tmp_compiler"
	./tmp_compiler ${src} ${out}
	rm tmp_compiler.c
	cp ${out} ${out}.prev
	a=0
	b=1
	while [ "$a" != "$b" ]
	do
		echo "a: $a\nb: $b"
		a=$(sha1sum ${out}.prev | sed 's/ .*//g')
		./tmp_compiler ${out}.prev ${out}
		b=$(sha1sum ${out} | sed 's/ .*//g')
		cp $out $out.prev
	done;
	rm tmp_compiler
	rm ${out}.prev
}

compile spec.ç spec.c -I.
