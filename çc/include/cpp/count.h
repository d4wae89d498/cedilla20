#ifndef CPP_COUNT
# define CPP_COUNT
# include <stdarg.h>
/*
 * This idea is from Laurent Deniau, CERN, and is taken from a discussion in comp.lang.c.
 *
 * C99 standard : 
 * 5.2.4.1 Translation limits
 *      The implementation shall be able to translate and execute at least one
 *      program that contains at least one instance of every one of the
 *      following limits:
 *      ...
 *      — 127 parameters in one function definition
 *      — 127 arguments in one function cal
 *      ...
 *      — 127 arguments in one macro invocation
 */
# define CPP_INDEX(\
A000, A001, A002, A003, A004, A005, A006, A007, A008, A009,\
A010, A011, A012, A013, A014, A015, A016, A017, A018, A019,\
A020, A021, A022, A023, A024, A025, A026, A027, A028, A029,\
A030, A031, A032, A033, A034, A035, A036, A037, A038, A039,\
A040, A041, A042, A043, A044, A045, A046, A047, A048, A049,\
A050, A051, A052, A053, A054, A055, A056, A057, A058, A059,\
A060, A061, A062, A063, A064, A065, A066, A067, A068, A069,\
A070, A071, A072, A073, A074, A075, A076, A077, A078, A079,\
A080, A081, A082, A083, A084, A085, A086, A087, A088, A089,\
A090, A091, A092, A093, A094, A095, A096, A097, A098, A099,\
A100, A101, A102, A103, A104, A105, A106, A107, A108, A109,\
A110, A111, A112, A113, A114, A115, A116, A117, A118, A119,\
A120, A121, A122, A123, A124, A125, A126, I, ...) I
# define CPP_COUNT(...) CPP_INDEX(void, ##__VA_ARGS__,\
               126, 125, 124, 123, 122, 121, 120,\
119, 118, 117, 116, 115, 114, 113, 112, 111, 110,\
109, 108, 107, 106, 105, 104, 103, 102, 101, 100,\
 99,  98,  97,  96,  95,  94,  93,  92,  91,  90,\
 89,  88,  87,  86,  85,  84,  83,  82,  81,  80,\
 79,  78,  77,  76,  75,  74,  73,  72,  71,  70,\
 69,  68,  67,  66,  65,  64,  63,  62,  61,  60,\
 59,  58,  57,  56,  55,  54,  53,  52,  51,  50,\
 49,  48,  47,  46,  45,  44,  43,  42,  41,  40,\
 39,  38,  37,  36,  35,  34,  33,  32,  31,  30,\
 29,  28,  27,  26,  25,  24,  23,  22,  21,  20,\
 19,  18,  17,  16,  15,  14,  13,  12,  11,  10,\
  9,   8,   7,   6,   5,   4,   3,   2,   1,   0)
#endif