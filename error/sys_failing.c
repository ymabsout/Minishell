#include "../mini_shell.h"

int sys_failing(int err, char *fn, s_lol *s)
{
    if (err != -1)
        return (0);
    if (s)
        s->status_code = errno;
    ft_putstr_fd("BNW: ", 2);
    ft_putstr_fd(fn, 2);
    ft_putstr_fd(": system call failed\n", 2);
    return(1);
}