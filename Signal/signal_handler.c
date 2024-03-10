#include "../mini_shell.h"

void handle_ctrl_c() {
    if (received_signal != -1)
        printf("\n");
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
    if (!received_signal)
        received_signal = 2;   
}

void handle_signal()
{
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, handle_ctrl_c);
}

void sig_def()
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}
void return_def()
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}

void heredoc_signal()
{
    write(STDOUT_FILENO, "\n", 1);
    close(STDIN_FILENO);
    received_signal = -1;
}

void no_nl()
{
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
    received_signal = 2;
}  