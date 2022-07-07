test:		test/match.c match/match.c match/match.h
	cc test/match.c match/match.c -Imatch -o match.out && ./match.out