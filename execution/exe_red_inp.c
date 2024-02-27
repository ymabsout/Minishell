
#include "../mini_shell.h"

static int open_input_file(t_btree *exec_tree)
{
    int fd;

    exec_tree->string = ft_join_all_nexts(exec_tree);
    if (access(exec_tree->string[0], F_OK | R_OK) == -1)
        return (-1);
    if ((fd = open(exec_tree->string[0], O_RDONLY)) == -1)
        return (-1);
    return (fd);
}

static void special_case(t_btree *exec_tree, t_listt *env)
{
    int fd;
    char *file;

    fd = open_input_file(exec_tree->right);
    if (fd < 0)
        return ;
    if (exec_tree->pipe_write_end && exec_tree->pipe_read_end)
    {
        exec_tree->right->pipe_write_end = exec_tree->pipe_write_end;
        exec_tree->right->pipe_read_end = exec_tree->pipe_read_end;
    }
    file = exec_tree->right->string[0];
    exec_tree->right->string = exec_tree->right->string + 1;
    free(file);
    exec_tree->right->stdin = fd;
    exec_tree->right->stdout = exec_tree->stdout;
    exec_tree->right->ln = 1;
    executing(exec_tree->right, env);
    close(fd);
}

static void create_string(t_btree *exec_tree, char **string)
{
    int l_s;
    int r_s;
    int i;
    char **arr;

    (l_s = 0, r_s = 0);
    while (exec_tree->string[l_s])
        l_s++;
    while (string[r_s])
        r_s++;
    arr = malloc((sizeof(char *) * (l_s + r_s)) + 1);
    if (!arr)
    {
        exec_tree->string = NULL;
        return ;
    }
    i = -1;
    while (++i < l_s + r_s)
    {
        if (i < l_s)
            arr[i] = exec_tree->string[i];
        else
            arr[i] = string[i - l_s];
    }
    (arr[i] = NULL, free(exec_tree->string), exec_tree->string = arr);
}

void execute_red_input(t_btree *exec_tree, t_listt *env)
{
    int fd;
    char *file;

    if (exec_tree->left == NULL)
        return (special_case(exec_tree, env));
    fd = open_input_file(exec_tree->right);
    if (fd < 0)
        return ;
    if (exec_tree->pipe_write_end && exec_tree->pipe_read_end)
    {
        exec_tree->left->pipe_write_end = exec_tree->pipe_write_end;
        exec_tree->left->pipe_read_end = exec_tree->pipe_read_end;
    }
    file = exec_tree->right->string[0];
    free(file);
    exec_tree->left->string = ft_join_all_nexts(exec_tree->left);
    create_string(exec_tree->left, exec_tree->right->string + 1);
    exec_tree->left->stdin = fd;
    exec_tree->left->stdout = exec_tree->stdout;
    exec_tree->left->ln = 1;
    executing(exec_tree->left, env);
    close(fd);
}