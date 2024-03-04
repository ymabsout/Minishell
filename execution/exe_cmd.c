
#include "../mini_shell.h"

char **env_double_pointer(t_listt *env)
{
    int size;
    int i;
    char **arr;

    size = ft_lstsize(env);
    arr = malloc((sizeof(char *) * (size + 1)));
    if (!arr)
        return (NULL);
    i = -1;
    while (++i < size)
    {
        arr[i] = malloc(ft_strlen(env->content) + 1);
        if (!arr[i])
            return (free_double(arr), NULL);
        arr[i] = ft_strdup(env->content);
        env = env->next;
    }
    arr[i] = NULL;
    return (arr);
}

void execute_left_cmd(t_btree *exec_tree, t_listt *env)
{
    char *cmd_path;
    char **envs;

    if (!find_num_char(exec_tree->string[0], '/'))
        cmd_path = get_path_cmd(exec_tree->string[0], env);
    else
        cmd_path = exec_tree->string[0];
    if (!cmd_path)
        handle_cmd_not_found(exec_tree->string[0]);
    envs = env_double_pointer(env);
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
    if (execve(cmd_path, exec_tree->string, envs) == -1)
        handle_cmd_not_found(exec_tree->string[0]);
}

void execute_right_cmd(t_btree *exec_tree, t_listt *env)
{
    char *cmd_path;
    char **envs;

    if (!find_num_char(exec_tree->string[0], '/'))
        cmd_path = get_path_cmd(exec_tree->string[0], env);
    else
        cmd_path = exec_tree->string[0];
    if (!cmd_path)
        handle_cmd_not_found(exec_tree->string[0]);
    envs = env_double_pointer(env);
    
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
    if (execve(cmd_path, exec_tree->string, envs) == -1)
        handle_cmd_not_found(exec_tree->string[0]);
}

void execute_solo_cmd(t_btree *exec_tree, t_listt *env)
{
    char *cmd_path;
    char **envs;

    if (!find_num_char(exec_tree->string[0], '/'))
        cmd_path = get_path_cmd(exec_tree->string[0], env);
    else
        cmd_path = exec_tree->string[0];
    if (!cmd_path)
        handle_cmd_not_found(exec_tree->string[0]);
    envs = env_double_pointer(env);
    if (execve(cmd_path, exec_tree->string, envs) == -1)
        handle_cmd_not_found(exec_tree->string[0]);
}

void execute_cmd(t_btree *exec_tree, t_listt *env, s_lol *s)
{
    pid_t pid;

    if (!(exec_tree->string))
        exec_tree->string =  ft_join_all_nexts(exec_tree, s->status_code);
    if (execute_built_in(exec_tree, env, s))
        return ;
    failing_err((pid = fork()));
    if (pid)
    {
        s->pids = pid;
        return ;
    }
    if (exec_tree->ln)
        execute_left_cmd(exec_tree, env);
    if (exec_tree->rn)
        execute_right_cmd(exec_tree, env);
    execute_solo_cmd(exec_tree, env);
}
