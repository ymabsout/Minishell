#include "m1.h"

int main ()
{
    char *s = " cat makefile | grep e | wc -l ";
    char **cmd = ft_split(s, '|');
    int i = -1;
    while (cmd[++i])
        printf("%s\n", cmd[i]);
}