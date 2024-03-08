
#include "../mini_shell.h"

static int open_input_file(t_btree *exec_tree, int status_code, t_listt *env)
{
    int fd;

    exec_tree->string = ft_join_all_nexts(exec_tree, status_code, env);
    if (access(exec_tree->string[0], F_OK | R_OK) == -1)
        return (-1);
    if ((fd = open(exec_tree->string[0], O_RDONLY)) == -1)
        return (-1);
    return (fd);
}

static void dbl_setter(t_btree *exec_tree, char **string)
{
    int i;
    char **arr;

    i = -1;
    while (string[++i]) ;

    arr = malloc(sizeof(char *) * (i));
    if (!arr)
        return ;
    
    i = -1;
    while (string[(++i) + 1])
    {
        arr[i] = ft_strdup(string[i + 1]);
        if (!arr[i])
            return (free_half_double(arr, i));
    }
    arr[i] = NULL;
    exec_tree->string = arr;
    free_double(string);
}

static void cmd_on_right(t_btree *exec_tree, t_listt *env, s_lol *s)
{
    int fd;
    char *file;

    fd = open_input_file(exec_tree->right, s->status_code, env);
    if (fd < 0)
    {
        s->status_code = 1;
        return ;
    }
    if (exec_tree->pipe_write_end && exec_tree->pipe_read_end)
    {
        exec_tree->right->pipe_write_end = exec_tree->pipe_write_end;
        exec_tree->right->pipe_read_end = exec_tree->pipe_read_end;
    }
    dbl_setter(exec_tree->right, exec_tree->right->string);
    if (exec_tree->stdin != 0)
        exec_tree->right->stdin = exec_tree->stdin;
    else
        exec_tree->right->stdin = fd;
    exec_tree->right->stdout = exec_tree->stdout;
    executing(exec_tree->right, env, s);
    close(fd);
}

// static void create_string(t_btree *exec_tree, char **string)
// {
//     int l_s;
//     int r_s;
//     int i;
//     char **arr;

//     (l_s = 0, r_s = 0);
//     while (exec_tree->string[l_s])
//         l_s++;
//     while (string[r_s])
//         r_s++;
//     arr = malloc((sizeof(char *) * (l_s + r_s + 1)));
//     if (!arr)
//         return ;
//     i = -1;
//     while (++i < l_s + r_s)
//     {
//         if (i < l_s)
//             arr[i] = exec_tree->string[i];
//         else
//             arr[i] = string[i - l_s];
//     }
//     (arr[i] = NULL, free(exec_tree->string), exec_tree->string = arr);
// }

static void setting_streams(t_btree *exec_tree, int above_st , int target_st, int fd)
{
    exec_tree->stdout = above_st;
    if (target_st != 0)
        exec_tree->stdin = target_st;
    else
        exec_tree->stdin = fd;
}

void execute_red_input(t_btree *exec_tree, t_listt *env, s_lol *s)
{
    int fd;
    char *file;

    if (exec_tree->left == NULL)
        return (cmd_on_right(exec_tree, env, s));
    fd = open_input_file(exec_tree->right, s->status_code, env);
    if (fd < 0)
    {
        s->status_code = 1;
        return ;
    }
    if (exec_tree->pipe_write_end && exec_tree->pipe_read_end)
    {
        exec_tree->left->pipe_write_end = exec_tree->pipe_write_end;
        exec_tree->left->pipe_read_end = exec_tree->pipe_read_end;
    }
    file = exec_tree->right->string[0];
    free(file);
    exec_tree->left->string = ft_join_all_nexts(exec_tree->left, \
        s->status_code, env);
    create_string(exec_tree->left, exec_tree->right->string + 1);
    (free(exec_tree->right->string), exec_tree->right->string = NULL);
    setting_streams(exec_tree->left, exec_tree->stdout, \
        exec_tree->stdin, fd);
    executing(exec_tree->left, env, s);
    close(fd);
}
