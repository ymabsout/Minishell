
#include "../mini_shell.h"


void execute_left_cmd(t_btree *exec_tree, t_listt *env)
{
    char *cmd_path;

    if (!(exec_tree->string))
        exec_tree->string =  ft_join_all_nexts(exec_tree);

    cmd_path = get_path_cmd(exec_tree->string[0], env);

    dup2(exec_tree->stdin, 0);
    dup2(exec_tree->stdout, 1);

    if (exec_tree->stdin != 0)
        close(exec_tree->stdin);
    if (exec_tree->pipe_read_end != 0)
        close(exec_tree->pipe_read_end);
    if (exec_tree->pipe_write_end != 0)
        close(exec_tree->pipe_write_end);
    execve(cmd_path, exec_tree->string, 0);
}

void execute_right_cmd(t_btree *exec_tree, t_listt *env)
{
    char *cmd_path;
    if (!(exec_tree->string))
        exec_tree->string =  ft_join_all_nexts(exec_tree);

    cmd_path = get_path_cmd(exec_tree->string[0], env);

    dup2(exec_tree->stdin, 0);
    dup2(exec_tree->stdout, 1);

    if (exec_tree->stdout != 1)
        close(exec_tree->stdout);
    close(exec_tree->pipe_read_end);
    close(exec_tree->pipe_write_end);

    execve(cmd_path, exec_tree->string, 0);
}

void execute_solo_cmd(t_btree *exec_tree, t_listt *env)
{
    char *cmd_path;
    exec_tree->string =  ft_join_all_nexts(exec_tree);

    cmd_path = get_path_cmd(exec_tree->string[0], env);
    execve(cmd_path, exec_tree->string, 0);
}

void execute_cmd(t_btree *exec_tree, t_listt *env)
{
    pid_t pid;

    if ((pid = fork()) == -1)
        return ;
    if (pid)
        return ;
    if (exec_tree->ln)
    {
        // if (exec_tree->pipe_write_end)
        //     exec_tree->stdout = exec_tree->pipe_write_end;
        execute_left_cmd(exec_tree, env);
    }
    if (exec_tree->rn)
    {
        // if (exec_tree->pipe_read_end)
        //     exec_tree->stdin = exec_tree->pipe_read_end;
        execute_right_cmd(exec_tree, env);
    }
    execute_solo_cmd(exec_tree, env);
}
