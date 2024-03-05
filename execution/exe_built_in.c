#include "../mini_shell.h"

static int fn(char **str, t_listt *env, int status_code, int flag)
{
    if (flag == 0)
        return (echo_built_in(str));
    else if (flag == 1)
        return (cd_built_in(str, &env));
    else if (flag == 2)
        return (pwd_built_in(str));
    else if (flag == 3)
        return (export_built_in(str, &env));
    else if (flag == 4)
        return (unset_built_in(str, &env));
    else if (flag == 5)
        return (env_built_in(str, env));
    return (exit_built_in(str, status_code));
}
static void exe_in_child(t_btree *exec_tree, t_listt *env, s_lol *s, int flag)
{
    int in;
    int out;
    int e;
    pid_t pid;

    pid = fork();
    if (pid > 0)
    {
        printf("PID: %d\n", pid);
        s->pids = pid;
        return ;
    }
    in = dup(0);
    out = dup(1);
    dup2(exec_tree->stdin, 0);
    dup2(exec_tree->stdout, 1);

    if (exec_tree->stdin != 0)
        close(exec_tree->stdin);
    if (exec_tree->stdout != 1)
        close(exec_tree->stdout);
    if (exec_tree->pipe_read_end != 0)
        close(exec_tree->pipe_read_end);
    if (exec_tree->pipe_write_end != 0)
        close(exec_tree->pipe_write_end);
    e = fn(exec_tree->string, env, s->status_code, flag);
    printf("=%d=\n", e);
    dup2(in, 0);
    dup2(out, 1);
    exit(e);
}

static void execute(t_btree *exec_tree, t_listt *env, s_lol *s, int flag)
{
    int in;
    int out;
    int e;

    // if (exec_tree->pipe_read_end && exec_tree->pipe_write_end)
    //     return (exe_in_child(exec_tree, env, s, flag));
    // if (!(exec_tree->string))
    //     exec_tree->string =  ft_join_all_nexts(exec_tree, s->status_code);
    in = dup(0);
    out = dup(1);
    dup2(exec_tree->stdin, 0);
    dup2(exec_tree->stdout, 1);

    if (exec_tree->stdin != 0)
        close(exec_tree->stdout);
    if (exec_tree->stdout != 1)
        close(exec_tree->stdout);
    if (exec_tree->pipe_read_end != 0)
        close(exec_tree->pipe_read_end);
    if (exec_tree->pipe_write_end != 0)
        close(exec_tree->pipe_write_end);
    e = fn(exec_tree->string, env, s->status_code, flag);
    s->status_code = e;
    dup2(in, 0);
    dup2(out, 1);
}

int execute_built_in(t_btree *exec_tree, t_listt *env, s_lol *s)
{
    if (!ft_strncmp(exec_tree->string[0], "echo", 5))
        return (execute(exec_tree, env, s, 0), 1);
    else if (!ft_strncmp(exec_tree->string[0], "cd", 3))
        return (execute(exec_tree, env, s, 1), 1);
    else if (!ft_strncmp(exec_tree->string[0], "pwd", 4))
        return (execute(exec_tree, env, s, 2), 1);
    else if (!ft_strncmp(exec_tree->string[0], "export", 7))
        return (execute(exec_tree, env, s, 3), 1);
    else if (!ft_strncmp(exec_tree->string[0], "unset", 6))
        return (execute(exec_tree, env, s, 4), 1);
    else if (!ft_strncmp(exec_tree->string[0], "env", 4))
        return (execute(exec_tree, env, s, 5), 1);
    else if (!ft_strncmp(exec_tree->string[0], "exit", 5))
        return (execute(exec_tree, env, s, 6), 1);
    return (0);
}