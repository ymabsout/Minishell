#include "../mini_shell.h"

void handle_ctrl_c(int c)
{
    (void)c;
    if (g_received_signal != -1)
        printf("\n");
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
    if (!g_received_signal)
        g_received_signal = 2;   
}

void handle_signal(int c)
{
    (void)c;
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, handle_ctrl_c);
}

void sig_def(int c)
{
    (void)c;
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}
void return_def(int c)
{
    (void)c;
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}

void heredoc_signal(int c)
{
    (void)c;
    write(STDOUT_FILENO, "\n", 1);
    close(STDIN_FILENO);
    g_received_signal = -1;
}

void no_nl(int c)
{
    (void)c;
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
    g_received_signal = 2;
}  