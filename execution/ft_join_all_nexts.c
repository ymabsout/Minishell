
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
static char *ft_joinAllDowns(t_btree *exec_tree)
{
    char *str;
    char *old_str;
    t_btree *down;

    str = exec_tree->item;
    exec_tree = exec_tree->down;
    while (exec_tree)
    {
        old_str = str;
        // if (exec_tree->typeofcontent & token_single_q)
        //     exec_tree->item = ft_strtrim(exec_tree->item, "\'");
        // if (exec_tree->typeofcontent & token_double_q)
        //     exec_tree->item = ft_strtrim(exec_tree->item, "\"");
        str = ft_strjoin(str, exec_tree->item);
        if (!str)
            return (free(old_str), NULL);
        free(old_str);
        down = exec_tree->down;
        free(exec_tree->item);
        free(exec_tree);
        exec_tree = down;
    }
    return (str);
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

char **ft_join_all_nexts(t_btree *exec_tree)
{
    char **cmd;
    int next_size;
    t_btree *next;
    t_btree *curr;
    int i;

    next_size = ft_size(exec_tree);
    cmd = (char **)malloc((sizeof(char *) * next_size) + 1);
    if (!cmd)
        return (NULL);
    curr = exec_tree;
    i = -1;
    while (++i < next_size)
    {
        cmd[i] = malloc(ft_strlen(curr->item) + 1);
        if (!cmd[i])
            return (free_double(cmd), NULL);
        cmd[i] = ft_strdup(ft_joinAllDowns(curr));
        curr = curr->next;
    }
    free_nexts(exec_tree->next);
    cmd[i] = NULL;
    return (cmd);
}