#include "../mini_shell.h"

void *get_file(t_btree *ex_t)
{
    int *index;
    char *indexfile;
    char *file_to_open;

    index = malloc(sizeof(int) * 1);
    if (!index)
        return (NULL);
    indexfile = ft_itoa((unsigned long)index);
    free(index);
    file_to_open = ft_strjoin("/tmp/", ft_strjoin(ex_t->right->item, indexfile));
    return (file_to_open);
}

void routine_heredoc(int fd, char *delimiter)
{
    char *str;
    char *line;

    while (!received_signal && isatty(STDIN_FILENO))
    {
        signal(SIGINT, heredoc_signal);
        line = readline(">_heredoc:");
        if (!line || !ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
            break ;
        str = ft_strjoin(line, "\n");
        free(line);
        write(fd, str, ft_strlen(str));
        free(str);
    } 
}

void read_stdin(t_btree *exec_tree, int status_code, t_listt *env)
{
    char *delimiter;
    int fd;
    char *filetoconvert;
    int fd1_copy_0;

    (void)status_code;
    (void)env;
    fd1_copy_0 = dup(STDIN_FILENO);
    filetoconvert = (char *)get_file(exec_tree);
    unlink(filetoconvert);
    fd = open(filetoconvert, O_CREAT | O_WRONLY, 0644);
    if (fd < 0)
        return ;
    delimiter = exec_tree->right->item;
    routine_heredoc(fd, delimiter);
    close(fd);
    free(exec_tree->right->item);
    exec_tree->right->item = ft_strdup (filetoconvert);
    dup2(fd1_copy_0, STDIN_FILENO);
    close(fd1_copy_0);
    free(filetoconvert);
}
