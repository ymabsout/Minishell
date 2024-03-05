#include "../mini_shell.h"

void handle_ctrl_c()
{
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    received_signal = 2;
}

void handle_signal()
{
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, handle_ctrl_c);
}

void return_def()
{
    signal(SIGQUIT, SIG_DFL);
}
