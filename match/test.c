#include "match.c"

void test(object_list **o)//token("(") 
{
    object *p = object_get(o, "plvl");
    if (p)
        rset(o, new(int, plvl, p->value + 1));
    else 
        rset(o, new(int, plvl, 1));

    if (exists(o, plvl))
        rset(o, new(int, plvl, get(o, plvl, int) + 1));
    else 
        rset(o, new(int, plvl, 1));
}

int     is_str_eq(object_list **o, char **str, va_list ap)
{
    char    *arg;

    arg = va_arg(ap, char*);

    return !(strncmp(arg, *str, strlen(arg)));
}

// returns the size of the pattern
int     is_space(object_list **o, char **str, va_list ap)
{
    (void) ap;
    (void) o;
    int i = 0;
    while(isspace(*str[i++]))
        ;
    return i;
}
// returns the size of the pattern

int     is_word(object_list **o, char **str, va_list ap)
{
    (void) ap;
    (void) o;
    return isspace(**str);
}

int     print_state(object_list **o, char **str, va_list ap)
{

}


int main()
{
    char *str = "int g(int x);";
    object_list *o = 0;

    // object_list primitives:

    /**
     *          PARSERS with tokens as key
     *          
     * 
     * */

    // difference between token and macros ??
/*
        - token alter lang state
        - token dont ret
        - token cant be longer than 1 char or max 1 word

        - macro consume lang state 
        - macro ret str
        - any size
*/
    char   *s; 
    match (&o, &str,
            oskip      is_space limit 5,    // optional skip a 5-len space, fail if longer
            skip       is_word,
            skip       is_space,
            skip       is_word limit 10,    // word len max 10
            call       print_state,
            token      "(", // or token "(" ?
            capture    &s until
                token  ")",


            capture    &s until is_space,
        0
    );

    printf("CAPTURE : %s\n", s);
/**
 * 
 *    *      RESTORE STATE IN MATCH FAIL,  AND 'MATCH LIST' aka macro fail 
 *    *      SKIP and other kw in match 
 *    *      MATCH concurencies, IE, match a parenthese outside the 'match_parenthese' macro ???   in macro only ?? create a system for a callback like is_... that dont affect output but only alter params ??
 *                  --> state macro
 * 
 * */
}