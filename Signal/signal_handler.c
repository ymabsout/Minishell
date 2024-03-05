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

// void child_ctrl()
// {
//     printf("\n");
// }

void sig_def()
{
    signal(SIGINT, SIG_IGN);
    // signal(SIGINT, child_ctrl);
    signal(SIGQUIT, SIG_IGN);
}
void return_def()
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    // signal(SIGQUIT, sig_def);
}
