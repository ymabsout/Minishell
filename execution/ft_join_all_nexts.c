
#include "../mini_shell.h"

static int ft_size(t_btree *tree)
{
    int i;

    i = 0;
    while (tree)
    {
        i++;
        tree = tree->next;
    }
    return (i);
}

static void free_nexts(t_btree *exec_tree)
{
    t_btree *next;

    while (exec_tree)
    {
        next = exec_tree->next;
        free(exec_tree->item);
        free(exec_tree);
        exec_tree = next;
    }
}

char **ft_join_all_nexts(t_btree *exec_tree, int status_code, t_listt *env)
{
    t_btree *curr;
    char **cmd;
    int next_size;
    int i;

    handle_wild(exec_tree, status_code, env);
    next_size = ft_size(exec_tree);
    cmd = (char **)malloc((sizeof(char *) * (next_size + 1)));
    if (!cmd)
        return (NULL);
    curr = exec_tree;
    i = -1;
    while (++i < next_size)
    {
        cmd[i] = malloc(ft_strlen(curr->item) + 1);
        if (!cmd[i])
            return (free_double(cmd), NULL);
        cmd[i] = ft_strdup(curr->item);
        curr = curr->next;
    }
    // free_nexts(exec_tree->next);
    cmd[i] = NULL;
    return (cmd);
}
