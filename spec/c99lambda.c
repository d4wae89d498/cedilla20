#include "stdio.h"

// todo::   add an intermediate cast to let cedilla compiler known that it were a lambda,
//          as '$ cpp *.ç' will occurs before '$ cedilla *.ç' \

#define test(...) 0
#define lambda(X, Y, ...) ((Y(*)()) (long long) ( { __VA_ARGS__ 0;} ))

#define _(...) test

int itest()
{
    typedef struct 
    {
        int i;
        int z;
        float f;
    } ks;
    int pp;
    int pp;

// todo:: fix structure because clang does not support return in ({ expression })
// BUTT it is an IDE-only issue, clanging the file actually work as the p pointer is initialized to 0
    ks(*p)() = lambda ((int x, int y), int, 
        return (ks) {0,0,0}; 
    );
// instead a fix would be 
    ks(*p)() = lambda ((int x, int y), int, 
        (ks) {0,0,0}; 
    );


    int(*k)() = lambda ((int x, int y), int, 
        dwadwa  // ide error : dwadwa is undefined 
        return 1; 
    );

    long long ll = lambda((int x), int, 
        return 0; 
    )();

    long l = lambda((int x), long, 
        return 0; 
    )(12, 1, 6);
    int i = lambda((int x), int, 
        return 0; 
    )();
    short s = lambda((int x), short, 
        return 0; 
    )();
    char c  = lambda((int x), short, 
        return 0; 
    )('z');

    unsigned long long ull = lambda((int x), unsigned long long, 
        return 0; 
    )('z');
    unsigned long ul = lambda((int x), unsigned long, 
        return 0; 
    )('p');
    unsigned  u = lambda((int x), unsigned , 
        return 0; 
    )('p');
    unsigned short us = lambda((int x), unsigned short, 
        return 0; 
    )('p');
    unsigned char uc = lambda((int x), unsigned char, 
        return 0; 
    )('p');

    void* v = lambda((int x),  void* , 
        return 0; 
    )('p');

    float f = lambda((int x),  float , 
        return 0; 
    )('p');
    double d = lambda((int x),  double , 
        return 0; 
    )('p');
    long double ld =  lambda((int x), long double,  
        return 0; 
    )(42);

    printf ("%d", _()());
}

int main()
{
    itest();
}