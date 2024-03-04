#include "../mini_shell.h"

void execute_sub_shell(t_btree *exec_tree, t_listt *env, s_lol *s)
{
    pid_t pid;

    exec_tree->flag_subshell = 0;
    pid = fork();
    if (pid > 0)
    {
        s->pids = pid;
        return ;
    }
    executing(exec_tree, env, s);
    close(exec_tree->pipe_read_end);
    close(exec_tree->pipe_write_end);
    if (waitpid(s->pids, &s->status_code, 0) != -1)
        s->status_code = WEXITSTATUS(s->status_code);
    while (waitpid(-1, 0, 0) != -1);
    exit(s->status_code);
}