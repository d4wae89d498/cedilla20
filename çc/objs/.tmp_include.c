#include "compiler.h"



#if TEST

#undef TEST
#define TEST 0
#include "../spec/c99.ç"
#undef TEST
#define TEST 1

int main()
{
 //   assert(__BRACES__ == 1);
}
#endif