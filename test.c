#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main ()
{
    char *s = readline("test");
    printf("%s\n", s);
}