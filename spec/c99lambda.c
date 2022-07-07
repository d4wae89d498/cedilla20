#include "stdio.h"

// todo::   add an intermediate cast to let cedilla compiler known that it were a lambda,
//          as '$ cpp *.ç' will occurs before '$ cedilla *.ç' 

#define test(...) 0
#define lambda(X, Y, ...) ((Y(*)()) (long long) ( { __VA_ARGS__ 0;} ))

#define _(...) test

int main()
{
    int(*k)() = lambda ((int x, int y), int, 
        //dwadwa  // ide error : dwadwa is undefined 
        return 1; 
    );

    long long ll = lambda((int x), int, 
        return 0; 
    )();

    long l = _()();
    int i = _()();
    short s = _()();
    char c = _()();

    unsigned long long ull = _()();
    unsigned long ul = _()();
    unsigned int u = _()();
    unsigned short us = _()();
    unsigned char uc = _()();

    void* v = _()();

    float f = _()();
    double d = _()();
    long double ld =  lambda((int x), long double,  
        return 0; 
    )();

    printf ("%d", _()());
}