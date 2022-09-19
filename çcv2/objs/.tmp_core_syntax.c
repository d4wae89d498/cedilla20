#include "../cedilla.h"

#if TEST



#if IDE_COMPAT
# define __G1__ 0
#endif


#if IDE_COMPAT
# define __G2__ 0
#endif


int main()
{
    assert(IDE_COMPAT == 0);
    assert(41 == 41);
    printf("OK\n"); 
}
#endif