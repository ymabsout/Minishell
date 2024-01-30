#include <stdio.h>
#include <readline/readline.h>

int main ()
{
    char *s = readline("test");
    printf("%s\n", s);
}