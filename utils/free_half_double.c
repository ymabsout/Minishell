#include "../mini_shell.h"


void free_half_double(char **cmd, int i)
{
    while (i >= 0)
        free(cmd[i--]);
    free(cmd);
}