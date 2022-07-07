#include "stdio.h"

#define test(...) 0
#define lambda(X, ...) ((void*) (unsigned long long) ({__VA_ARGS__}))

#define _(...) test

int main()
{
    int(*k)() = lambda ((int x, int y) -> int, 
        //dwadwa  // ide error : dwadwa is undefined 
        1;
    );

    long long ll = lambda((int x) -> int, 0;)();
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
    long double ld = _()();

    printf ("%d", _()());
}