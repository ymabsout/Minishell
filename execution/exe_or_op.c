
#include "../mini_shell.h"

void execute_or_op(t_btree *exec_tree, t_listt *env, s_lol *s)
{
    if (exec_tree->pipe_write_end && exec_tree->pipe_read_end)
    {
        exec_tree->left->pipe_write_end = exec_tree->pipe_write_end;
        exec_tree->left->pipe_read_end = exec_tree->pipe_read_end;
    }
    exec_tree->left->stdin = exec_tree->stdin;
    exec_tree->left->stdout = exec_tree->stdout;
    executing(exec_tree->left, env, s);
    if (waitpid(s->pids, &s->status_code, 0) != -1)
        s->status_code = WEXITSTATUS(s->status_code);
    while (waitpid(-1, 0, 0) != -1);
    if (s->status_code != 0)
    {
        if (exec_tree->pipe_write_end && exec_tree->pipe_read_end)
        {
            exec_tree->right->pipe_write_end = exec_tree->pipe_write_end;
            exec_tree->right->pipe_read_end = exec_tree->pipe_read_end;
        }
        exec_tree->right->stdin = exec_tree->stdin;
        exec_tree->right->stdout = exec_tree->stdout;
        executing(exec_tree->right, env, s);
    }
}
