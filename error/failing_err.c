#include "../mini_shell.h"

void failing_err(int failed)
{
    if (failed != -1)
        return ;
    perror("BNW");
    printf("%d\n", errno);
    exit(EXIT_FAILURE);
}