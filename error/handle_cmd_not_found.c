#include "../mini_shell.h"

void handle_cmd_not_found(char *cmd)
{
    ft_putstr_fd("BNW: ", 2);
    ft_putstr_fd(cmd, 2);
    ft_putstr_fd(": command not found\n", 2);
    exit(127);
}