#include "./../match/match.h"
#include "assert.h"

int main()
{
    ç_ctx   ctx;
    int     r;

    printf("testing match...\n");  
    ctx.str = "HELLO WORLD";
    r = match(&ctx, "HELLO", " ", "WORLD", 0);
    assert(r == 1);
    r = match(&ctx, "HELLO", 0);
    assert(r == 1); // todo: fix me
}