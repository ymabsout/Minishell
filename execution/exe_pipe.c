
#include "../mini_shell.h"

void execute_pipe(t_btree *exec_tree, t_listt *env, s_lol *s)
{
    int fd[2];

    if (pipe(fd) == -1)
        return ;
    if (exec_tree->pipe_write_end)
        exec_tree->stdout = exec_tree->pipe_write_end;

    exec_tree->left->pipe_read_end = fd[0];
    exec_tree->left->pipe_write_end = fd[1];
    exec_tree->left->stdout = fd[1]; 
    exec_tree->left->ln = 1;

    int pid1;
    pid1 = fork();
    if (!pid1)
    {
        if (exec_tree->pipe_write_end)
            close(exec_tree->pipe_write_end);
        close(fd[0]);
        executing(exec_tree->left, env, s);
        while (wait(0) != -1);
        exit(s->status_code);
    }
    else
    {
        s->pids = pid1;
    }
    int pid2;
    exec_tree->right->pipe_read_end = fd[0];
    exec_tree->right->pipe_write_end = fd[1];
    exec_tree->right->stdin = fd[0];
    exec_tree->right->stdout = exec_tree->stdout;
    exec_tree->right->rn = 1;
    pid2 = fork();
    if (!pid2)
    {
        executing(exec_tree->right, env, s);
        while (wait(0) != -1);
        exit(s->status_code);
    }   
    else
    {
        s->pids = pid2;
    }
    if (exec_tree->pipe_read_end)
        close(exec_tree->pipe_read_end);
    if (exec_tree->pipe_write_end)
        close(exec_tree->pipe_write_end);
    close(fd[0]);
    close(fd[1]);
}