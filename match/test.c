#include "match.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main()
{
    const char *str = " 1 2  (4 + (9 * 8))";
    object_list *o = 0;
    match(&o, &str, 
        print_int,    10,
      
   //      print_int",  //  5,
 //       "oskip",         is_space,
 //       "oskip",        is_digit,
       skip,         is_space,  
       skip,     is_digit,
       call,     print_str,
   //     "call2", print_str,
        skip, is_space
        
        );
}
