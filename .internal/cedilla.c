#include "cedilla.h"
#include "ini.h"
#include "file.h"

char  cwd[PATH_SIZE];

int main()
{
    char    *config_path;
    ini     k;


    getcwd(cwd, PATH_SIZE);
    asprintf(&config_path, "%s/cedilla.ini", cwd);
    k = ini_new(config_path);
    printf("k: %p\n", k);
    ini_dump(k); 
    return (0);
}