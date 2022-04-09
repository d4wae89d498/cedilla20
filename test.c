#import "ft"

# define EXPAND(x) x
# define REVERSE_1(a) a
# define REVERSE_2(a,b) b,a
# define REVERSE_3(a,...) EXPAND(REVERSE_2(__VA_ARGS__)),a
# define REVERSE_4(a,...) EXPAND(REVERSE_3(__VA_ARGS__)),a
# define REVERSE_5(a,...) EXPAND(REVERSE_4(__VA_ARGS__)),a
# define REVERSE_6(a,...) EXPAND(REVERSE_5(__VA_ARGS__)),a
# define REVERSE_7(a,...) EXPAND(REVERSE_6(__VA_ARGS__)),a
# define REVERSE_8(a,...) EXPAND(REVERSE_7(__VA_ARGS__)),a
# define REVERSE_9(a,...) EXPAND(REVERSE_8(__VA_ARGS__)),a
# define REVERSE_10(a,...) EXPAND(REVERSE_9(__VA_ARGS__)),a
# define REVERSE1(N,...) EXPAND(REVERSE_ ## N(__VA_ARGS__))
# define REVERSE(N, ...) REVERSE1(N, __VA_ARGS__)
# define _GET_NTH_ARG(_1, _2, _3, _4, _5, _6, _7, _9, _10, N, ...) N
# define NUM_ARGS(...) EXPAND(_GET_NTH_ARG(__VA_ARGS__,9,8,7,6,5,4,3,2,1,0))
// ----
# define CONCATENATE(arg1, arg2)   CONCATENATE1(arg1, arg2)
# define CONCATENATE1(arg1, arg2)  CONCATENATE2(arg1, arg2)
# define CONCATENATE2(arg1, arg2)  arg1##arg2
# define FOR_EACH_1(what, x) what(x, 1);
# define FOR_EACH_2(what, x, ...)\
  what(x, 2);\
  FOR_EACH_1(what,  __VA_ARGS__)
# define FOR_EACH_3(what, x, ...)\
  what(x, 3);\
  FOR_EACH_2(what, __VA_ARGS__)
# define FOR_EACH_4(what, x, ...)\
  what(x, 4);\
  FOR_EACH_3(what,  __VA_ARGS__)
# define FOR_EACH_5(what, x, ...)\
  what(x, 5);\
 FOR_EACH_4(what,  __VA_ARGS__)
# define FOR_EACH_6(what, x, ...)\
  what(x, 6);\
  FOR_EACH_5(what,  __VA_ARGS__)
# define FOR_EACH_7(what, x, ...)\
  what(x, 7);\
  FOR_EACH_6(what,  __VA_ARGS__)
# define FOR_EACH_8(what, x, ...)\
  what(x, 8);\
  FOR_EACH_7(what,  __VA_ARGS__)
# define FOR_EACH_NARG(...) FOR_EACH_NARG_(__VA_ARGS__, FOR_EACH_RSEQ_N())
# define FOR_EACH_NARG_(...) FOR_EACH_ARG_N(__VA_ARGS__) 
# define FOR_EACH_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N 
# define FOR_EACH_RSEQ_N() 8, 7, 6, 5, 4, 3, 2, 1, 0
# define FOR_EACH_(N, what, ...) CONCATENATE(FOR_EACH_, N)(what, __VA_ARGS__)
# define FOR_EACH(what, ...) FOR_EACH_(FOR_EACH_NARG(__VA_ARGS__), what, __VA_ARGS__)
# define token_paste(a, b) a##b
# define STRING_MEMBERS(x, i) typeof(x) token_paste(e, i)
# define _INTERNAL(...) (struct { FOR_EACH(STRING_MEMBERS, __VA_ARGS__)}) { __VA_ARGS__ }
# define _(...) EXPAND(_INTERNAL(REVERSE(NUM_ARGS(__VA_ARGS__), __VA_ARGS__)))


#define cast(X) *(X*)&
#define structure(X) _(X)
struct test{int e1; int e2;};

struct test f()
{
	return  cast(struct test) structure(0);
}

// auto is c++ alike
// _(...) 	is a shortcut for casting to struct
// __(...)	is a shortcut for ml strings

int main()
{

	/*
	struct
	{
		int	e2;
		int	e2;
	} pp= _(0,0);
*/
	f();
	auto p = _(0, 4, "HI!");

	printf("e1=%i e2=%i e3=%s\n", p.e1, p.e2, p.e3);

	printf("%i %i\n", REVERSE(2, 0, 4));

	printf(__(

			This 			text
			will be trimmed !!! 





			%i
	), 42);
}

