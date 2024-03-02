#include "../mini_shell.h"

void execute_heredoc(t_btree *exec_tree, t_listt *env, s_lol *s)
{
    char *line;
    char *str;
    char *delimiter;
    int fd[2];

    if (exec_tree->pipe_write_end)
        exec_tree->stdout = exec_tree->pipe_write_end;
    delimiter = exec_tree->right->item;
    pipe(fd);
    while (1)
    {
        line = readline("> ");
        if (!ft_strncmp(line, delimiter, ft_strlen(delimiter)))
            break ;
        str = ft_strjoin(line, "\n");
        free(line);
        write(fd[1], str, ft_strlen(str));
    }
    if (!exec_tree->left)
        return ;
    exec_tree->left->pipe_read_end = fd[0];
    exec_tree->left->pipe_write_end = fd[1];
    exec_tree->left->stdin = fd[0];
    exec_tree->left->stdout = exec_tree->stdout;
    exec_tree->left->rn = 1;
    executing(exec_tree->left, env, s);
    close(fd[0]);
    close(fd[1]);
}
