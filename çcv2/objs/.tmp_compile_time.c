#include "../cedilla.h"

#include "../spec/c99.ç"

#if IDE_COMPAT
# define compile_time
# define compile_time_include(...)
# define compile_time_run(...) (long long)0
#endif



#if TEST

int main()
{
    printf("OK\n");
    return (0);
}

#endif

