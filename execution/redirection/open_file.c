
#include "../../mini_shell.h"


int open_file(t_btree *exec_tree, int flag, int status_code, t_listt *env)
{
    int fd;

    exec_tree->string = ft_join_all_nexts(exec_tree, status_code, env);
    if (flag == 1)
    {
        if (access(exec_tree->string[0], F_OK) != -1)
            return (-2);
        if ((fd = open(exec_tree->string[0],\
            O_CREAT | O_WRONLY, 0644)) == -1)
            return (-1);
    }
    else if (flag == 0)
    {
        if (access(exec_tree->string[0], F_OK))
        {
            if (access(exec_tree->string[0], W_OK) == -1)
                return (-3);
        }
        if ((fd = open(exec_tree->string[0],\
            O_CREAT | O_WRONLY | O_APPEND, 0644)) == -1)
            return (-1);
    }
    // flag == 2
    if (access(exec_tree->string[0], F_OK) == -1)
        return (-1);
    if (access(exec_tree->string[0], R_OK) == -1)
        return (-3);
    if ((fd = open(exec_tree->string[0], O_RDONLY)) == -1)
        return (-1); 
    return (fd);
    // return (fd);
}
