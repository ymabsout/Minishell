
#include "../mini_shell.h"

void fd_failure(char *file, int id, s_lol *s)
{
    s->status_code = 1;
    ft_putstr_fd("BNW: ", 2);
    ft_putstr_fd(file, 2);
    if (id == -1)
        ft_putstr_fd(": No such file or directory\n", 2);
    else if (id == -2)
        ft_putstr_fd(": cannot overwrite existing file\n", 2);
    else if (id == -3)
        ft_putstr_fd(": Permission denied\n", 2);
}