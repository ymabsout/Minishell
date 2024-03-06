#include "../mini_shell.h"

static int read_stdin(t_btree *exec_tree, int status_code, t_listt *env)
{
    char *line;
    char *str;
    char *delimiter;
    int fd;

    unlink("/tmp/heredoc_file");
    fd = open("/tmp/heredoc_file", O_CREAT | O_WRONLY, 0644);
    if (fd < 0)
        return (fd);
    exec_tree->string = ft_join_all_nexts(exec_tree, status_code, env);
    delimiter = exec_tree->string[0];
    while (1)
    {
        line = readline("> ");
        if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
            break ;
        str = ft_strjoin(line, "\n"); 
        free(line);
        write(fd, str, ft_strlen(str));
    }
    close(fd);
    fd = open("/tmp/heredoc_file", O_RDONLY);
    if (fd < 0)
        return (fd);
    return (fd);
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
    arr = malloc((sizeof(char *) * (l_s + r_s + 1)));
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

static void special_case(t_btree *exec_tree, t_listt *env, s_lol *s)
{
    int fd;
    char *file;

    fd = read_stdin(exec_tree->right, s->status_code, env);
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
    if (exec_tree->stdin != 0)
        exec_tree->right->stdin = exec_tree->stdin;
    else
        exec_tree->right->stdin = fd;
    exec_tree->right->stdout = exec_tree->stdout;
    exec_tree->right->ln = 1;
    executing(exec_tree->right, env, s);
    close(fd);
    unlink("/tmp/heredoc_file");
}

void execute_heredoc(t_btree *exec_tree, t_listt *env, s_lol *s)
{
    char *file;
    int fd;

    if (exec_tree->left == NULL)
        return (special_case(exec_tree, env, s));
    fd = read_stdin(exec_tree->right, s->status_code, env);
    if (fd < 0)
        return ;
    if (exec_tree->pipe_write_end && exec_tree->pipe_read_end)
    {
        exec_tree->right->pipe_write_end = exec_tree->pipe_write_end;
        exec_tree->right->pipe_read_end = exec_tree->pipe_read_end;
    }
    file = exec_tree->right->string[0];
    free(file);
    exec_tree->left->string = ft_join_all_nexts(exec_tree->left, s->status_code, env);
    create_string(exec_tree->left, exec_tree->right->string + 1);
    if (exec_tree->stdin != 0)
        exec_tree->left->stdin = exec_tree->stdin;
    else
        exec_tree->left->stdin = fd;
    exec_tree->left->stdout = exec_tree->stdout;
    exec_tree->left->ln = 1;
    executing(exec_tree->left, env, s);
    close(fd);
    unlink("/tmp/heredoc_file");
}
