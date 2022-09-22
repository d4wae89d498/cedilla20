#include "cedilla.h"






#if TEST
#undef TEST
#define TEST 0
# include "../spec/compile_time.ç"
#undef TEST
#define TEST 1
#endif
# if IDE_COMPAT
#  define __BRACKETS__ 0
#  define __PARENTHESES__ 0
#  define __BRACES__ 0
# endif


#if TEST





int main()
{
    if (1)
    {
        assert(2 == 2);
    }
    assert(1 == 1);
    assert(((3)) == 3);
    assert("1234"["1234"[2] - '0'] == '4');
    assert(1 == 1);
    assert(1 == 1);
    assert(0 == 0);
    assert(!strcmp("42", "42"));

    /*  */
    // 

    printf("OK\n");
}
#endif