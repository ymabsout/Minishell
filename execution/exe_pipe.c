
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
    executing(exec_tree->left, env, s);

    exec_tree->right->pipe_read_end = fd[0];
    exec_tree->right->pipe_write_end = fd[1];
    exec_tree->right->stdin = fd[0];
    exec_tree->right->stdout = exec_tree->stdout;
    exec_tree->right->rn = 1;
    executing(exec_tree->right, env, s);
    close(fd[0]);
    close(fd[1]);
}